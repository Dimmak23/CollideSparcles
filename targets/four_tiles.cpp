#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <iostream>

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* background = NULL;
SDL_Texture* image = NULL;
SDL_Surface* surface = NULL;

SDL_Rect dst = { 0, 0, 400, 400 };

#define SOLID 255
#define HALF_TRANSPARENT 128
#define TRANSPARENT 0

SDL_Texture* renderImageInATexture(SDL_Texture* image, Uint8 transparency)
{
	// Create an intermediate texture
	SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 400, 400);
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

int main(/*char* argc, char** argv*/)
{
	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow("Win", 10, 10, 1600, 400, SDL_WINDOW_SHOWN);

	// So we can save into pngs to check the value
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderTarget(renderer, NULL);

	// Fill the window with a texture to see if semi transparent intermediate texture is OK.
	surface = IMG_Load("assets/carbon-background.png");
	background = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	// draw background in main display
	// SDL_Rect srcRect{ 0, 0, 1600, 400 };
	// SDL_Rect backRect{ 0, 0, 1600, 400 };
	// SDL_RenderCopy(renderer, background, &srcRect, &backRect);
	SDL_RenderCopy(renderer, background, nullptr, nullptr);
	// std::cout << "rendering background is: " << SDL_RenderCopy(renderer, background, nullptr, &backRect) <<
	// std::endl;

	surface = IMG_Load("assets/light-no-back.png");
	image = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	// draw image in main display as reference to compare with further renderings
	SDL_RenderCopy(renderer, image, NULL, &dst);

	// Secondly, the image is rendered in a fully opaque intermediate texture.
	SDL_Texture* texture = renderImageInATexture(image, SOLID);
	std::cout << "blend texture: " << SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND) << std::endl;
	// render intermediate texture in main display
	SDL_Rect dstTexture = { 400, 0, 400, 400 };
	SDL_RenderCopy(renderer, texture, NULL, &dstTexture);

	// Third, the image is rendered in a half transparent texture.
	SDL_Texture* texture2 = renderImageInATexture(image, HALF_TRANSPARENT);
	std::cout << "blend texture2: " << SDL_SetTextureBlendMode(texture2, SDL_BLENDMODE_BLEND) << std::endl;
	// render intermediate texture2 in main display
	SDL_Rect dstTexture2 = { 800, 0, 400, 400 };
	SDL_RenderCopy(renderer, texture2, NULL, &dstTexture2);

	// Fourth, the image is rendered in a fully trasnparent texture, expecting the
	// exact same result as first rendering.
	SDL_Texture* texture3 = renderImageInATexture(image, TRANSPARENT);
	std::cout << "blend texture3: " << SDL_SetTextureBlendMode(texture3, SDL_BLENDMODE_BLEND) << std::endl;
	// render intermediate texture3 in main display
	SDL_Rect dstTexture3 = { 1200, 0, 400, 400 };
	SDL_RenderCopy(renderer, texture3, NULL, &dstTexture3);

	SDL_RenderPresent(renderer);

	SDL_Event e;
	int wait = 1;
	while (wait)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				wait = 0;
			}
			SDL_Delay(33);
		}
	}

	SDL_DestroyTexture(image);
	SDL_DestroyTexture(background);	   // only if you use a background
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
