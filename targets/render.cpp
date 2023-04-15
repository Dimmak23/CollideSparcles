#include <SDL2/SDL.h>
// #include <SDL2/SDL_image.h>

#include <iostream>

#include "MainWindow.hpp"
#include "Utils.hpp"
// #include <limits>
// #include <sstream>

// We have to use WinMain(...) for GUI application in the Windows OS
#ifdef _WIN32
#include <windows.h>
// Declaring main here because we want to call it from the WinMain(...)
int main(int argc, char* argv[]);
// int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char*, int nShowCmd)
int CALLBACK WinMain(
	/*
	a handle to the current instance of the application.
	This is a unique identifier for the application
	that Windows uses to differentiate
	it from other running applications.
	*/
	HINSTANCE hInstance,
	/*
	a handle to the previous instance of the application.
	This parameter is not used in modern Windows
	programming and is always set to NULL.
	*/
	HINSTANCE hPrevInstance,
	/*
	a pointer to a null-terminated string containing the command-line arguments passed
	to the application. You can parse this string to extract any relevant information.
	*/
	LPSTR pCmdLine,
	/*
	an integer value indicating how the window should be shown.
	You can set this to one of the SW_* constants defined in
	the Windows API to specify the window's initial state.
	*/
	int nCmdShow)
{
	// std::cout << hInstance << '\n';
	// std::cout << hPrevInstance << '\n';
	// std::cout << pCmdLine << '\n';
	// std::cout << nCmdShow << '\n';

	// Now we call the main function
	return main(__argc, __argv);
}
#else
// You are lucky if you run this on the Unix or MacOS,
//  because GUI application can be created in the main(...) there
#endif

//?! Why this don't work?
// We have to wrap up 'int main()' to use SDL_main on the Windows,
// instead of 'int CALLBACK WinMain()'
// #ifdef __cplusplus
// extern "C" {
// #endif

int main(int argc, char* argv[])
{
	// Get from command line window size
	Utils::parseWindowSize(argc, argv);

	// Create main window
	MainWindow* application = new MainWindow(Utils::_width, Utils::_height);

	if (!application->getCreationStatus()) return 1;

	// application->renderBackground();

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

		// Game logic and rendering...
		application->renderScreen();
	}

	delete application;

	SDL_Quit();

	return 0;
};

// #ifdef __cplusplus
// }
// #endif