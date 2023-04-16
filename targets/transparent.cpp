#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>

int main()
{
	// Initialize SDL and create a window and renderer
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window = SDL_CreateWindow("SDL2 Transparency", 10, 10, 640, 480, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	// Load an SDL_Surface from a PNG file using SDL2_image
	// SDL_Surface* image_surface = IMG_Load("assets/character.png");
	SDL_Surface* image_surface = SDL_LoadBMP("assets/background.bmp");

	// Create an SDL2 image mask surface with an alpha channel
	// SDL_Surface* mask_surface =
	// SDL_CreateRGBSurfaceWithFormat(0, image_surface->w, image_surface->h, 32, SDL_PIXELFORMAT_RGBA32);

	// Set the alpha values of the mask surface pixels based on the RGB values of the image surface pixels
	// Uint32 white_pixel = SDL_MapRGB(image_surface->format, 255, 255, 255);
	// for (int y = 0; y < image_surface->h; y++)
	// {
	// 	for (int x = 0; x < image_surface->w; x++)
	// 	{
	// 		Uint32 pixel = *((Uint32*)image_surface->pixels + y * image_surface->pitch / 4 + x);
	// 		if (pixel == white_pixel)
	// 		{
	// 			*((Uint32*)mask_surface->pixels + y * mask_surface->pitch / 4 + x) = 0x00000000;	// set alpha to 0
	// 		}
	// 		else
	// 		{
	// 			*((Uint32*)mask_surface->pixels + y * mask_surface->pitch / 4 + x) = 0xFFFFFFFF;	// set alpha to 255
	// 		}
	// 	}
	// }

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

	SDL_SetColorKey(image_surface, SDL_TRUE, SDL_MapRGB(image_surface->format, 255, 255, 255));

	// Create an SDL2 texture from the image surface
	SDL_Texture* image_texture = SDL_CreateTextureFromSurface(renderer, image_surface);
	SDL_FreeSurface(image_surface);

	std::cout << "blend: " << SDL_SetTextureBlendMode(image_texture, SDL_BLENDMODE_BLEND) << std::endl;

	SDL_Rect charRect;
	charRect.x = 10;
	charRect.y = 10;
	charRect.w = 400;	 // desired width
	charRect.h = 400;	 // desired height

	// SDL_SetTextureBlendMode(image_texture, SDL_BLENDMODE_BLEND);

	// Render the texture to the window
	// SDL_RenderCopy(renderer, image_texture, NULL, NULL);
	// SDL_RenderPresent(renderer);

	// Wait for a key press to exit
	bool running = true;
	while (running)
	{
		// canvas
		SDL_SetRenderDrawColor(renderer, 0xff, 0, 0x21, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);

		// Render the texture to the window
		SDL_RenderCopy(renderer, image_texture, nullptr, &charRect);

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