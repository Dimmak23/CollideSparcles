#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>

enum TRCY
{
	SOLID = 255,
	HALF_TRANSPARENT = 128,
	TRANSPARENT = 0
};

SDL_Texture* renderImageInATexture(SDL_Renderer* renderer,		//
								   SDL_Texture* image,			//
								   const SDL_Rect& destRect,	//
								   Uint8 transparency			//
)
{
	// Create an intermediate texture
	SDL_Texture* texture =
		SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, destRect.w, destRect.h);
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
	SDL_SetRenderTarget(renderer, texture);

	// Paint it black with a given transparency value.
	SDL_SetRenderDrawColor(renderer, (Uint8)0, (Uint8)0, (Uint8)0, (Uint8)transparency);
	SDL_RenderClear(renderer);

	// Render the image in intermediate texture
	SDL_SetRenderTarget(renderer, texture);
	SDL_RenderCopy(renderer, image, NULL, NULL);

	// The result will be rendered in the background
	SDL_SetRenderTarget(renderer, NULL);
	return texture;
}

int main()
{
	// Initialize SDL and create a window and renderer
	SDL_Init(SDL_INIT_VIDEO);
	//
	SDL_Window* window = SDL_CreateWindow("SDL2 Transparency", 10, 10, 640, 480, SDL_WINDOW_SHOWN);
	//
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	// Load an SDL_Surface from a PNG file using SDL2_image
	SDL_Surface* image_surface = IMG_Load("assets/light-no-back.png");
	// SDL_Surface* image_surface = SDL_LoadBMP("assets/light-no-back.bmp");
	{
		// // Create an SDL2 image mask surface with an alpha channel
		// SDL_Surface* mask_surface =
		// 	SDL_CreateRGBSurfaceWithFormat(0, image_surface->w, image_surface->h, 32, SDL_PIXELFORMAT_RGBA32);

		// // Set the alpha values of the mask surface pixels based on the RGB values of the image surface pixels
		// // Uint32 white_pixel = SDL_MapRGB(image_surface->format, 255, 255, 255);
		// // for (int y = 0; y < image_surface->h; y++)
		// // {
		// // 	for (int x = 0; x < image_surface->w; x++)
		// // 	{
		// // 		Uint32 pixel = *((Uint32*)image_surface->pixels + y * image_surface->pitch / 4 + x);
		// // 		if (pixel == white_pixel)
		// // 		{
		// // 			*((Uint32*)mask_surface->pixels + y * mask_surface->pitch / 4 + x) = 0x00000000;	// set alpha
		// to
		// 0
		// // 		}
		// // 		else
		// // 		{
		// // 			*((Uint32*)mask_surface->pixels + y * mask_surface->pitch / 4 + x) = 0xFFFFFFFF;	// set alpha
		// to 255
		// // 		}
		// // 	}
		// // }

		// SDL_SetSurfaceAlphaMod(image_surface, SDL_ALPHA_OPAQUE);
		// SDL_SetSurfaceBlendMode(image_surface, SDL_BLENDMODE_BLEND);
		// SDL_SetSurfaceAlphaMod(mask_surface, SDL_ALPHA_OPAQUE);
		// SDL_SetSurfaceBlendMode(mask_surface, SDL_BLENDMODE_NONE);

		// SDL_SetSurfaceAlphaMod(image_surface, SDL_ALPHA_TRANSPARENT);
		// SDL_SetSurfaceBlendMode(image_surface, SDL_BLENDMODE_BLEND);
		// SDL_SetSurfaceColorMod(image_surface, 255, 255, 255);
		// SDL_SetColorKey(image_surface, SDL_TRUE, SDL_MapRGB(image_surface->format, 255, 255, 255));

		// SDL_SetSurfaceAlphaMod(mask_surface, SDL_ALPHA_TRANSPARENT);
		// SDL_SetSurfaceBlendMode(mask_surface, SDL_BLENDMODE_NONE);
		// SDL_SetSurfaceColorMod(mask_surface, 0, 0, 0);

		// SDL_SetSurfaceAlphaMod(image_surface, SDL_ALPHA_OPAQUE);
		// SDL_SetSurfaceBlendMode(image_surface, SDL_BLENDMODE_BLEND);

		// SDL_SetSurfaceAlphaMod(mask_surface, SDL_ALPHA_OPAQUE);
		// SDL_SetSurfaceBlendMode(mask_surface, SDL_BLENDMODE_NONE);

		// SDL_SetSurfaceAlphaMod(image_surface, SDL_ALPHA_OPAQUE);
		// SDL_SetSurfaceBlendMode(image_surface, SDL_BLENDMODE_BLEND);

		// // Fill the mask surface with a solid color and an alpha value of 0
		// SDL_FillRect(mask_surface, NULL, SDL_MapRGBA(mask_surface->format, 255, 255, 255, 0));

		// // Set the color key of the image surface to be transparent
		// SDL_SetColorKey(image_surface, SDL_TRUE, SDL_MapRGB(image_surface->format, 255, 255, 255));

		// // Set the alpha mask of the image surface to be the alpha channel of the mask surface
		// SDL_SetSurfaceAlphaMod(image_surface, 255);
		// SDL_SetSurfaceBlendMode(image_surface, SDL_BLENDMODE_BLEND);
		// SDL_SetSurfaceRLE(image_surface, 1);
		// SDL_SetSurfaceColorMod(image_surface, 255, 255, 255);
		// SDL_SetColorKey(image_surface, SDL_TRUE, SDL_MapRGB(image_surface->format, 255, 255, 255));

		// SDL_SetSurfaceBlendMode(mask_surface, SDL_BLENDMODE_NONE);
		// SDL_SetSurfaceColorMod(mask_surface, 0, 0, 0);
		// SDL_SetSurfaceAlphaMod(mask_surface, 255);
		// SDL_SetSurfaceRLE(mask_surface, 1);
		// SDL_SetSurfaceBlendMode(mask_surface, SDL_BLENDMODE_NONE);

		// SDL_SetColorKey(image_surface, SDL_TRUE, SDL_MapRGB(image_surface->format, 255, 255, 255));
		// SDL_SetSurfaceColorMod(image_surface, 255, 255, 255);

		// SDL_SetColorKey(image_surface, SDL_TRUE, SDL_MapRGB(image_surface->format, 255, 255, 255));
	}

	// Create an SDL2 texture from the image surface
	SDL_Texture* image_texture = SDL_CreateTextureFromSurface(renderer, image_surface);
	SDL_FreeSurface(image_surface);

	SDL_Rect logoRect{ 0, 0, 400, 353 };
	image_texture = renderImageInATexture(renderer, image_texture, logoRect, TRCY::SOLID);

	std::cout << "blend texture: "												//
			  << SDL_SetTextureBlendMode(image_texture, SDL_BLENDMODE_BLEND)	//
			  << std::endl;

	std::cout << "blend: " << SDL_SetTextureBlendMode(image_texture, SDL_BLENDMODE_BLEND) << std::endl;

	// Wait for a key press to exit
	bool running = true;
	while (running)
	{
		// canvas
		SDL_SetRenderDrawColor(renderer, 0x12, 0x32, 0x21, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);

		// Render the texture to the window
		SDL_RenderCopy(renderer, image_texture, nullptr, &logoRect);

		// Show
		SDL_RenderPresent(renderer);

		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT || event.type == SDL_KEYDOWN)
			{
				running = false;
			}
		}
	}

	// Clean up and exit
	SDL_DestroyTexture(image_texture);
	// SDL_FreeSurface(mask_surface);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}