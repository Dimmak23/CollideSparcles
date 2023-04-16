// There are two problems:

//     Disable blending. Use SDL_SetTextureBlendMode(source, SDL_BLENDMODE_NONE); before RenderCopy, otherwise you'll
//     get wrong colour (blended with default black - result would be darker than it shound be). Blending tied to
//     texture so if you want to use this texture later you probably should reset blending mode right away. See
//     SDL_SetTextureBlendMode doc for formulas used in different blend modes.

//     Your resulting surface don't have alpha channel so there is nowhere to copy result. Check documentation for
//     SDL_CreateRGBSurface: while it allows to use 0 for colour masks to deduce default values, it explicitly don't
//     allow it for alpha channel, so 0 in place of amask results in "I don't want alpha channel, just RGB". Your
//     resulting format is RGB888 packed to 32bit. You want alpha, so you should use correct colour masks - get one from
//     docs, in your case you don't even need to check for endianess, but it never hurts.

// To sum it up:

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

void save_texture(const char* file_name, SDL_Renderer* renderer, SDL_Texture* texture);
SDL_Texture* clipTexture(SDL_Rect rect, SDL_Renderer* renderer, SDL_Texture* source);

int main(/*int argc, const char* argv[]*/)
{
	SDL_Init(SDL_INIT_VIDEO);

	IMG_Init(IMG_INIT_PNG);

	// SDL_Renderer* renderer = SDL_CreateSoftwareRenderer(surface);

	// SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	// SDL_Rect frame_rect = { 0, 0, 450, 300 };
	// SDL_Texture* tex_clip = clipTexture(frame_rect, renderer, texture);

	// save_texture("assets/character_test.png", renderer, tex_clip);

	// SDL_FreeSurface(surface);

	SDL_Window* window = SDL_CreateWindow("Testing png cut parse...",	 //
										  10,							 //
										  10,							 //
										  1200, 600,					 //
										  SDL_WINDOW_SHOWN				 //
	);

	SDL_Renderer* wrenderer = SDL_CreateRenderer(
		window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);

	SDL_Surface* character = IMG_Load("assets/character_02.png");

	// Uint32 colorkey = SDL_MapRGB(character->format, 0, 0, 0);
	// SDL_SetColorKey(character, SDL_TRUE, colorkey);

	// Create texture from image
	SDL_Texture* characterTexture = SDL_CreateTextureFromSurface(wrenderer, character);
	SDL_FreeSurface(character);

	SDL_Rect charRect;
	charRect.x = 10;
	charRect.y = 10;
	charRect.w = 400;	 // desired width
	charRect.h = 400;	 // desired height

	// Game loop
	bool quitStatus{ false };
	while (!quitStatus)
	{
		// Event handling
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_QUIT:
					quitStatus = true;
					break;
			}
		}

		// Updates

		// Clear and draw the screen
		SDL_SetRenderDrawColor(wrenderer, 0, 0, 0xFF, SDL_ALPHA_OPAQUE);

		// Character
		SDL_RenderCopy(wrenderer, characterTexture, nullptr, &charRect);

		// Show
		SDL_RenderPresent(wrenderer);
		SDL_RenderClear(wrenderer);
	}

	SDL_DestroyTexture(characterTexture);
	characterTexture = nullptr;

	SDL_DestroyRenderer(wrenderer);
	wrenderer = nullptr;

	// Destroy window
	SDL_DestroyWindow(window);
	window = nullptr;

	SDL_Quit();
}

// return a new texture that is a part of the original texture.

SDL_Texture* clipTexture(SDL_Rect rect, SDL_Renderer* renderer, SDL_Texture* source)
{
	SDL_Texture* result =
		SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, rect.w, rect.h);
	SDL_SetRenderTarget(renderer, result);
	SDL_SetTextureBlendMode(source, SDL_BLENDMODE_NONE);
	SDL_RenderCopy(renderer, source, &rect, NULL);

	return result;
}

// save png to disk
void save_texture(const char* file_name, SDL_Renderer* renderer, SDL_Texture* texture)
{
	int width, height;
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);

	Uint32 rmask, gmask, bmask, amask;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	rmask = 0xff000000;
	gmask = 0x00ff0000;
	bmask = 0x0000ff00;
	amask = 0x000000ff;
#else
	rmask = 0x000000ff;
	gmask = 0x0000ff00;
	bmask = 0x00ff0000;
	amask = 0xff000000;
#endif

	SDL_Surface* surface = SDL_CreateRGBSurface(0, width, height, 32, rmask, gmask, bmask, amask);

	SDL_RenderReadPixels(renderer, NULL, surface->format->format, surface->pixels, surface->pitch);
	IMG_SavePNG(surface, file_name);
	SDL_FreeSurface(surface);
}
