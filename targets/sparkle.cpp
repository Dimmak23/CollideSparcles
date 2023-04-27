#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>

enum CORNER
{
	LEFT_UP = 0,
	RIGHT_UP,
	LEFT_BOTTOM,
	RIGHT_BOTTOM
};

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
	windowR.w = 900;
	windowR.h = 900;

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

	SDL_Rect lighterTrajectory;	   // trajectory of the center of the lighter
	lighterTrajectory.x = 60;
	lighterTrajectory.y = 54;
	lighterTrajectory.w = windowR.w - 2 * lighterTrajectory.x;
	lighterTrajectory.h = windowR.h - 2 * lighterTrajectory.y;

	SDL_Rect lighterR;
	lighterR.w = 100;
	lighterR.h = 88;
	lighterR.x = lighterTrajectory.x - lighterR.w / 2;
	lighterR.y = lighterTrajectory.y - lighterR.h / 2;

	SDL_Rect arenaBorder;	 // border of the arena
	arenaBorder.x = lighterR.x;
	arenaBorder.y = lighterR.y;
	arenaBorder.w = lighterTrajectory.w + lighterR.w;
	arenaBorder.h = lighterTrajectory.h + lighterR.h;

	unsigned char opacity{ 255 };
	int sign{ -1 };

	// std::cout << "change alpha mode: " << SDL_SetTextureAlphaMod(lighterT, opacity) << std::endl;
	// draw image in main display as reference to compare with further renderings
	callingStatus = SDL_RenderCopy(renderer, lighterT, nullptr, &lighterR);

	// Show everything that was rendered
	SDL_RenderPresent(renderer);

	// Event handling
	SDL_Event eventIns;

	bool running{ true };

	short deltaX{ 1 };
	short deltaY{};

	double rotationAngle{ 0.0 };

	bool firstTimeEnter{ true };

	SDL_Point lighterC = { lighterR.w / 2, lighterR.h / 2 };

	while (running)
	{
		SDL_RenderClear(renderer);

		// draw background
		callingStatus = SDL_RenderCopy(renderer, backgroundT, &backgroundCrop, nullptr);

		// draw arena
		callingStatus = SDL_SetRenderDrawColor(renderer, 34, 124, 200, SDL_ALPHA_OPAQUE);
		callingStatus = SDL_RenderDrawRect(renderer,	   //
										   &arenaBorder	   //
		);

		// Changing opacity
		if (opacity < 2)
		{
			sign *= -1;
			opacity = 1;
		}
		else if (opacity > 254)
		{
			sign *= -1;
			opacity = 255;
		}
		std::cout << "change alpha mode: " << SDL_SetTextureAlphaMod(lighterT, opacity) << std::endl;

		// Changing position
		lighterR.x += deltaX;
		lighterR.y += deltaY;

		if ((lighterR.x + lighterR.w / 2) > (lighterTrajectory.x + lighterTrajectory.w))
		{
			lighterR.x = lighterTrajectory.x + lighterTrajectory.w - lighterR.w / 2;
			deltaX = 0;
			deltaY = 1;

			firstTimeEnter = true;
		}
		else if ((lighterR.y + lighterR.h / 2) > (lighterTrajectory.y + lighterTrajectory.h))
		{
			lighterR.y = lighterTrajectory.y + lighterTrajectory.h - lighterR.h / 2;
			deltaX = -1;
			deltaY = 0;
		}
		else if ((lighterR.x + lighterR.w / 2) < lighterTrajectory.x)
		{
			lighterR.x = lighterTrajectory.x - lighterR.w / 2;
			deltaX = 0;
			deltaY = -1;
		}
		else if ((lighterR.y + lighterR.h / 2) < lighterTrajectory.y)
		{
			lighterR.y = lighterTrajectory.y - lighterR.h / 2;
			deltaX = 1;
			deltaY = 0;

			if (firstTimeEnter)
			{
				lighterTrajectory.x += 10;
				lighterTrajectory.y += 10;
				lighterTrajectory.w = lighterTrajectory.w - 20;
				lighterTrajectory.h = lighterTrajectory.h - 20;

				arenaBorder.x += 10;
				arenaBorder.y += 10;
				arenaBorder.w = arenaBorder.w - 20;
				arenaBorder.h = arenaBorder.h - 20;

				firstTimeEnter = false;
			}
		}

		opacity = static_cast<unsigned char>(opacity + sign);

		std::cout << "opacity: " << (int)opacity << ", sign: " << sign << std::endl;

		std::cout << "position x: " << lighterR.x + lighterR.w / 2 << std::endl;
		std::cout << "position y: " << lighterR.y + lighterR.h / 2 << std::endl;

		// draw image in main display as reference to compare with further renderings
		// callingStatus = SDL_RenderCopy(renderer, lighterT, nullptr, &lighterR);
		// rotate texture
		// lighterC.x = lighterR.x + lighterR.w / 2;
		// lighterC.y = lighterR.y + lighterR.h / 2;

		callingStatus = SDL_RenderCopyEx(renderer,				//
										 lighterT,				//
										 nullptr, &lighterR,	//
										 rotationAngle,			//
										 &lighterC,				//
										 SDL_FLIP_NONE			//
		);

		rotationAngle += 2;
		if (rotationAngle > 360.0) rotationAngle = 0.0;

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
