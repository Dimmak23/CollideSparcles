#include "WheelGameApplication.hpp"

#include <cmath>
#include <iostream>

WheelGameApplication::WheelGameApplication(int argc, char* argv[])
{
	// take optional arguments with window size
	// proceed optional arguments

	// update destination window rectangle
	_gRect.x = _appXPos;
	_gRect.y = _appYPos;
	_gRect.w = _appWidth;
	_gRect.h = _appHeight;

	// Create the main window
	_gWindow = SDL_CreateWindow(							//
		"Sparcles game. Dimmak productions, june 2023.",	//
		_gRect.x, _gRect.y, _gRect.w, _gRect.h,				//
		SDL_WINDOW_SHOWN									//
	);

	// Check if window creation were succsessfull
	if (_gWindow == nullptr)
	{
		std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
	}

	// Create a renderer for the window
	_gRenderer = SDL_CreateRenderer(_gWindow, -1, SDL_RENDERER_ACCELERATED);

	// Check if renderer creation were succsessfull
	if (_gRenderer == nullptr)
	{
		std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
	}

	// Set 'nullptr' texture as a rendering target
	_callingStatus = SDL_SetRenderTarget(_gRenderer, nullptr);

	// initialize game objects

	// build background texture according to the window size
	_background = new Background(_gRenderer, _appWidth, _appHeight);

	// build arena lines with initial sizes
	_arena = new Arena(_gRenderer, _appWidth, _appHeight);

	// build wheel with initial size
	_wheel = new Wheel(_gRenderer, WUtils::_wheel._width, WUtils::_wheel._height);

	//
	_bubble = new Bubble(_gRenderer, WUtils::_bubbleRadius, std::move(WUtils::Size(200, 200)));

	// build fps screen text
	_fpsScreen = new TextWidget(_gRenderer);
	// build fps screen text
	_legend = new TextWidget(_gRenderer);
}

WheelGameApplication::~WheelGameApplication()
{
	// destroy resources
	SDL_DestroyRenderer(_gRenderer);
	SDL_DestroyWindow(_gWindow);

	// deallocate heap memory
	delete _legend;
	delete _fpsScreen;
	delete _bubble;
	delete _wheel;
	delete _arena;
	delete _background;

	//
	SDL_Quit();
	//
	IMG_Quit();
	// Quit SDL_ttf library
	TTF_Quit();
}

void WheelGameApplication::initializeSDL()
{
	// use parsed window size if any

	// Initialize SDL2 libraries
	_callingStatus = SDL_Init(SDL_INIT_VIDEO);
	if (_callingStatus != 0)
	{
		std::cout << "Couldn't initalize SDL2 libraries...\n";
		return;
	}

	// Loading SDL_Image dynamic libraries
	_callingStatus = IMG_Init(IMG_INIT_PNG);
	if (_callingStatus == 0)
	{
		std::cout << "Couldn't load SDL_Image dynamic libraries...\n";
		return;
	}

	// Initialize SDL_ttf library
	_callingStatus = TTF_Init();
	if (_callingStatus != 0)
	{
		std::cout << "Couldn't load SDL_ttf dynamic libraries...\n";
		return;
	}
}

void WheelGameApplication::clampObjects(Arena* pArena, Wheel* pWheel)
{
	if (pWheel->rightSide() > pArena->rightSide())
	{
		pWheel->bounce(pArena->rightSide(), RIGHT);
		pWheel->setMoveDelta(DOWN);
	}
	else if (pWheel->downSide() > pArena->downSide())
	{
		pWheel->bounce(pArena->downSide(), DOWN);
		pWheel->setMoveDelta(LEFT);
		_firstTimeEnter = true;
	}
	else if (pWheel->leftSide() < pArena->leftSide())
	{
		pWheel->bounce(pArena->leftSide(), LEFT);
		pWheel->setMoveDelta(UP);
	}
	else if (pWheel->upSide() < pArena->upSide())
	{
		if (_firstTimeEnter)
		{
			pWheel->adjustPosition(1, 1);

			if (pArena->moveWheelCW(20))
				pWheel->setThick(4);
			else
				pWheel->setThick(-4);

			_firstTimeEnter = false;
		}
		pWheel->bounce(pArena->upSide(), UP);
		pWheel->setMoveDelta(RIGHT);

		_wheel->debug_data();
	}
}

void WheelGameApplication::clampObjects(Arena* pArena, Bubble* pBubble)
{
	if (pBubble->rightSide() > pArena->rightSide())
	{
		pBubble->bounce(pArena->rightSide(), RIGHT);
		// pBubble->setMoveDelta(DOWN);
	}
	else if (pBubble->downSide() > pArena->downSide())
	{
		pBubble->bounce(pArena->downSide(), DOWN);
		// pBubble->setMoveDelta(LEFT);
		// _firstTimeEnter = true;
	}
	else if (pBubble->leftSide() < pArena->leftSide())
	{
		pBubble->bounce(pArena->leftSide(), LEFT);
		// pBubble->setMoveDelta(UP);
	}
	else if (pBubble->upSide() < pArena->upSide())
	{
		// if (_firstTimeEnter)
		// {
		// 	pBubble->adjustPosition(1, 1);

		// 	if (pArena->moveWheelCW(20))
		// 		pBubble->setThick(1);
		// 	else
		// 		pBubble->setThick(-1);

		// 	_firstTimeEnter = false;
		// }
		pBubble->bounce(pArena->upSide(), UP);
		// pBubble->setMoveDelta(RIGHT);
	}
}

bool WheelGameApplication::IsColliding(Wheel* pWheel, Bubble* pBubble) const
{
	//
	float distance = std::sqrt((pWheel->collisionCenter().x - pBubble->collisionCenter().x) *
								   (pWheel->collisionCenter().x - pBubble->collisionCenter().x) +
							   (pWheel->collisionCenter().y - pBubble->collisionCenter().y) *
								   (pWheel->collisionCenter().y - pBubble->collisionCenter().y));
	//
	// std::cout << "pWheel->collisionCenter().x: " << pWheel->collisionCenter().x << '\n';
	// std::cout << "pWheel->collisionCenter().y: " << pWheel->collisionCenter().y << '\n';
	// std::cout << "pBubble->collisionCenter().x: " << pBubble->collisionCenter().x << '\n';
	// std::cout << "pBubble->collisionCenter().y: " << pBubble->collisionCenter().y << '\n';

	return ((pWheel->collideRadius() + pBubble->collideRadius()) > distance);
}

void WheelGameApplication::collideObjects(Wheel* pWheel, Bubble* pBubble)
{
	if (this->IsColliding(pWheel, pBubble))
	{
		//
		int deltaCX = pWheel->collisionCenter().x - pBubble->collisionCenter().x;
		int deltaCY = pWheel->collisionCenter().y - pBubble->collisionCenter().y;
		float alpha = atanf((float)(deltaCY) / (float)(deltaCX));
		int deltaRX = (pWheel->collideRadius() + pBubble->collideRadius()) * cosf(alpha);
		int deltaRY = (pWheel->collideRadius() + pBubble->collideRadius()) * sinf(alpha);

		SDL_Point newBubbleCenter{ pWheel->collisionCenter().x - deltaRX, pWheel->collisionCenter().y - deltaRY };
		//
		pBubble->bounce(newBubbleCenter);
	}
}

void WheelGameApplication::gamePlay()
{
	_fpsScreen->setFont(WUtils::_FPSfont_pixel, 14);
	_fpsScreen->setColor(std::move(SDL_Color{ 255, 12, 145 }));
	_fpsScreen->setPostion(10, 10);

	_legend->setFont(WUtils::_FPSfont_small, 18);
	_legend->setColor(std::move(SDL_Color{ 52, 63, 255 }));
	_legend->setPostion(10, _appHeight - 20);
	_legend->setMessage(std::move(std::string("DimmaK productions, june 2023.")));

	// Event handling
	SDL_Event eventIns;

	// start game loop
	while (_running)
	{
		// clear background from the last frame
		SDL_RenderClear(_gRenderer);

		// draw background
		_background->draw();

		// set wheel texture alpha mod
		_wheel->setTextureAlphaMod();
		// change wheel opacity value
		_wheel->changeOpacity();
		// clamp wheel opacity
		_wheel->clampOpacity();

		// change wheel position
		_wheel->implementMovement();
		// clamp wheel movement direction
		this->clampObjects(_arena, _wheel);

		// change wheel rotation angle
		_wheel->changeRotation(4.0);
		// clamp wheel rotation angle
		_wheel->clampRotation();

		// draw wheel
		_wheel->draw();

		// draw arena
		_arena->draw();

		//!>>>>BUBLE>>>>

		// set bubble texture alpha mod
		_bubble->setTextureAlphaMod();
		// clamp bubble movement direction
		this->clampObjects(_arena, _bubble);
		//
		this->collideObjects(_wheel, _bubble);
		// change bubble position
		_bubble->implementMovement();
		// draw bubble
		_bubble->draw();

		//!<<<<BUBLE<<<<

		// draw fps screen
		_fpsScreen->draw();

		// draw legend
		_legend->draw();

		// Show everything that was rendered
		SDL_RenderPresent(_gRenderer);

		while (SDL_PollEvent(&eventIns))
		{
			switch (eventIns.type)
			{
				case SDL_QUIT:
					_running = false;
					break;
				case SDL_KEYDOWN:
					switch (eventIns.key.keysym.sym)
					{
						case SDLK_ESCAPE:
							_running = false;
							break;
							// cases for other keypresses
					}
			}
		}

		if (_running) SDL_Delay(4);

		// Update and print FPS
		static Uint32 previousTime = SDL_GetTicks64();
		Uint32 currentTime = SDL_GetTicks64();

		float deltaTime = (currentTime - previousTime) / 1000.0f;
		previousTime = currentTime;

		float fps = 1.0f / deltaTime;
		// std::cout << "FPS: " << fps << '\n';
		_fpsScreen->setMessage(std::move("FPS: " + std::to_string((int)fps)));
	}
}
