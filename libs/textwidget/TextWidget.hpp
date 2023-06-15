#pragma once

#ifdef _WIN32

#include <SDL.h>
// #include <SDL_image.h>
#include <SDL_ttf.h>

#else

#include <SDL2/SDL.h>
// #include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#endif

// #include <string>

class TextWidget
{
public:
	TextWidget(												   //
		SDL_Renderer* parent,								   //
		const char* message,								   //
		const char* fontPath,								   //
		const unsigned int& size,							   //
		const unsigned int& posX, const unsigned int& posY,	   //
		const SDL_Color& foregroundColor					   //
	);
	~TextWidget();

	int draw();

private:
	// let's deprecate copying text object
	TextWidget(const TextWidget&) = delete;
	TextWidget operator=(const TextWidget&) = delete;

	SDL_Renderer* _parent{ nullptr };

	SDL_Texture* _text{ nullptr };
	TTF_Font* _font{ nullptr };

	unsigned int _size;

	unsigned int _textWidth{};
	unsigned int _textHeight{};

	unsigned int _posX{};
	unsigned int _posY{};

	// struct TextRectangle
	// {
	// public:
	// 	// setters
	// 	void set(const int& x, const int& y, const int& w, const int& h);
	// 	void setX(const int& value);
	// 	void setY(const int& value);

	// 	// getters
	// 	SDL_Point getOriginPoint() const;
	// 	int X() const;
	// 	int Y() const;
	// 	int width() const;
	// 	int height() const;

	// private:
	// 	// capsule
	// 	SDL_Rect _rect;
	// };

	// // We need destination rectangle
	// TextRectangle _rectangle;
};
