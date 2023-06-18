#pragma once

#include <vector>

#include "Arena.hpp"
#include "Background.hpp"
#include "Bubble.hpp"
#include "TextWidget.hpp"
#include "Wheel.hpp"

class WheelGameApplication
{
public:
	WheelGameApplication(int argc, char* argv[]);
	~WheelGameApplication();

	// How we fork SDL framework
	void initializeSDL();

	// Need to keep wheel inside arena
	void clampObjects(Arena* pArena, Wheel* pWheel);
	//
	void clampObjects(Arena* pArena, Bubble* pBubble);
	//
	bool IsColliding(Wheel* pWheel, Bubble* pBubble) const;
	//
	void collideObjects(Wheel* pWheel, Bubble* pBubble);

	// Actual game behavior
	void gamePlay();

private:
	// let's deprecate copying application
	WheelGameApplication(const WheelGameApplication&) = delete;
	WheelGameApplication operator=(const WheelGameApplication&) = delete;

	// Dimensions
	unsigned int _appXPos{ 100 };
	unsigned int _appYPos{ 100 };
	unsigned int _appWidth{ 1600 };
	unsigned int _appHeight{ 800 };

	// Graphics
	SDL_Window* _gWindow{ nullptr };
	SDL_Renderer* _gRenderer{ nullptr };

	// Body
	SDL_Rect _gRect;

	// Projectiles
	Background* _background{ nullptr };
	Arena* _arena{ nullptr };
	Wheel* _wheel{ nullptr };
	Bubble* _bubble{ nullptr };
	std::vector<Bubble*> _sparcles;

	//
	TextWidget* _fpsScreen{ nullptr };
	//
	TextWidget* _legend{ nullptr };

	// keeping track on the status of the creation
	bool _callingStatus{ false };

	// check maybe user whant to exit
	bool _running{ true };

	// check if we already have shrink arena and adjust wheel position
	bool _firstTimeEnter{ true };
};
