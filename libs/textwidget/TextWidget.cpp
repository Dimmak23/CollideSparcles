#include "TextWidget.hpp"

#include <iostream>

TextWidget::TextWidget(SDL_Renderer* parent)
{
	// catch renderer
	_parent = parent;
}

// Destroy allocated resources
TextWidget::~TextWidget()
{
	//
	SDL_DestroyTexture(_text);
	// Close the font
	TTF_CloseFont(_font);
	//
	_parent = nullptr;
}

int TextWidget::draw()
{
	if (_font == nullptr)
	{
		// std::cout << "We didn't succeed with loading font...\n";
		return -2;
	}
	// Render text to an SDL_Surface
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(_font, _message.c_str(), _color);

	// Create an SDL_Texture from the SDL_Surface
	_text = SDL_CreateTextureFromSurface(_parent, surfaceMessage);

	// Get the dimensions of the rendered text
	_textWidth = surfaceMessage->w;
	_textHeight = surfaceMessage->h;

	// Free the SDL_Surface as it is no longer needed
	SDL_FreeSurface(surfaceMessage);

	//
	SDL_Rect textRect;
	textRect.x = _posX;
	textRect.y = _posY;
	textRect.w = _textWidth;
	textRect.h = _textHeight;

	// Render the text texture onto the screen
	int temp = SDL_RenderCopy(_parent, _text, NULL, &textRect);

	// Clean up the message texture
	SDL_DestroyTexture(_text);

	return temp;
}

void TextWidget::setFont(std::string fontPath, unsigned int&& size)
{
	//
	_fontPath = fontPath;	 //! can only pass by value from static std::string
	//
	_size = std::move(size);
	// Load the font
	_font = TTF_OpenFont(_fontPath.c_str(), _size);
	if (!_font)
	{
		std::cout << "No font loaded\n";
		std::cout << "_fontPath: " << _fontPath << '\n';
		std::cout << "_size: " << _size << '\n';
	}
}

void TextWidget::setSize(unsigned int&& size) { _size = std::move(size); }

void TextWidget::setColor(SDL_Color&& color) { _color = std::move(color); }

void TextWidget::setPostion(const unsigned int& posX, const unsigned int& posY)
{
	_posX = posX;
	_posY = posY;
}

void TextWidget::setMessage(std::string&& message) { _message = std::move(message); }
