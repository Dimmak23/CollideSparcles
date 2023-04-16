#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>

int main(/*int argc, char const *argv[]*/)
{
	int callingStatus{};

	// Initialize SDL2 libraries
	callingStatus = SDL_Init(SDL_INIT_VIDEO);
	if (callingStatus != 0)
	{
		std::cout << "Couldn't initalize SDL2 libraries...\n";
		return 1;
	}

	// Loading SDL_Image dynamic libraries
	callingStatus = IMG_Init(IMG_INIT_PNG);
	if (callingStatus == 0)
	{
		std::cout << "Couldn't load SDL_Image dynamic libraries...\n";
		return 1;
	}

	// Window parameters
	SDL_Rect windowR;
	windowR.x = 10;
	windowR.y = 10;
	windowR.w = 1200;
	windowR.h = 600;

	// Create the main window
	SDL_Window* window = nullptr;
	window = SDL_CreateWindow(						   //
		"Sparkling joy...",							   //
		windowR.x, windowR.y, windowR.w, windowR.h,	   //
		SDL_WINDOW_SHOWN							   //
	);

	// Check if window creation were succsessfull
	if (window == nullptr)
	{
		std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	// Create a renderer for the window
	SDL_Renderer* renderer = nullptr;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	// Check if renderer creation were succsessfull
	if (renderer == nullptr)
	{
		std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	// Set 'nullptr' texture as a rendering target
	callingStatus = SDL_SetRenderTarget(renderer, nullptr);

	// Create a background surface from the '<?>.png'
	SDL_Surface* backgroundS = nullptr;
	backgroundS = IMG_Load("assets/carbon-background.png");

	if (backgroundS == nullptr)
	{
		std::cout << "Background surface could not be created! SDL Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	// Create a texture from the surface
	SDL_Texture* backgroundT = nullptr;
	backgroundT = SDL_CreateTextureFromSurface(renderer, backgroundS);
	SDL_FreeSurface(backgroundS);

	// Window parameters
	SDL_Rect backgroundCrop;
	backgroundCrop.x = 0;
	backgroundCrop.y = 0;
	backgroundCrop.w = windowR.w;
	backgroundCrop.h = windowR.h;

	// Draw background in the main window
	callingStatus = SDL_RenderCopy(renderer, backgroundT, &backgroundCrop, nullptr);

	// Create a lighter surface from the '<?>.png'
	SDL_Surface* lighterS = nullptr;
	lighterS = IMG_Load("assets/light-no-back.png");

	if (lighterS == nullptr)
	{
		std::cout << "Lighter surface could not be created! SDL Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	// SDL_SetColorKey(lighterS, SDL_TRUE, SDL_MapRGB(surface->format, 255, 255, 255));

	// Create a texture from the surface
	SDL_Texture* lighterT = nullptr;
	lighterT = SDL_CreateTextureFromSurface(renderer, lighterS);
	SDL_FreeSurface(lighterS);

	// Lighter parameters
	SDL_Rect lighterR;
	lighterR.x = 10;
	lighterR.y = 10;
	lighterR.w = 400;
	lighterR.h = 353;

	unsigned char opacity{ 255 };
	int sign{ -1 };

	std::cout << "change alpha mode: " << SDL_SetTextureAlphaMod(lighterT, opacity) << std::endl;
	// draw image in main display as reference to compare with further renderings
	callingStatus = SDL_RenderCopy(renderer, lighterT, nullptr, &lighterR);

	// Show everything that was rendered
	SDL_RenderPresent(renderer);

	// Event handling
	SDL_Event eventIns;

	bool running{ true };

	while (running)
	{
		SDL_RenderClear(renderer);

		callingStatus = SDL_RenderCopy(renderer, backgroundT, &backgroundCrop, nullptr);

		if (opacity < 20)
		{
			sign *= -1;
			opacity = 19;
		}
		else if (opacity > 254)
		{
			sign *= -1;
			opacity = 255;
		}

		std::cout << "change alpha mode: " << SDL_SetTextureAlphaMod(lighterT, opacity) << std::endl;

		opacity = static_cast<unsigned char>(opacity + sign);

		std::cout << "opacity: " << (int)opacity << ", sign: " << sign << std::endl;
		// draw image in main display as reference to compare with further renderings
		callingStatus = SDL_RenderCopy(renderer, lighterT, nullptr, &lighterR);

		// Show everything that was rendered
		SDL_RenderPresent(renderer);

		while (SDL_PollEvent(&eventIns))
		{
			switch (eventIns.type)
			{
				case SDL_QUIT:
					running = false;
					break;
				case SDL_KEYDOWN:
					switch (eventIns.key.keysym.sym)
					{
						case SDLK_ESCAPE:
							running = false;
							break;
							// cases for other keypresses
					}
			}
		}

		if (running) SDL_Delay(2);
	}

	SDL_DestroyTexture(backgroundT);	// only if you use a background
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
