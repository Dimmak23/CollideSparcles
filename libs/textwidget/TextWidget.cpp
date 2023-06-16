#include "TextWidget.hpp"

TextWidget::TextWidget(SDL_Renderer* parent, const char* message, const char* fontPath, const unsigned int& size,
					   const unsigned int& posX, const unsigned int& posY, const SDL_Color& foregroundColor)
{
	// catch renderer
	_parent = parent;

	// Do we keep all of this?
	//
	// message???
	//
	// fontPath???
	//
	// foreGroundColor???

	//
	_size = size;
	_posX = posX;
	_posY = posY;

	// // Load the font
	// _font = TTF_OpenFont("assets/fonts/cheese.ttf", _size);

	// // Render text to an SDL_Surface
	// SDL_Surface* surfaceMessage = TTF_RenderText_Solid(_font, "HIIIIIIIII", foregroundColor);

	// // Create an SDL_Texture from the SDL_Surface
	// _text = SDL_CreateTextureFromSurface(_parent, surfaceMessage);

	// // Get the dimensions of the rendered text
	// _textWidth = surfaceMessage->w;
	// _textHeight = surfaceMessage->h;

	// // Free the SDL_Surface as it is no longer needed
	// SDL_FreeSurface(surfaceMessage);
}

TextWidget::~TextWidget()
{
	// Close the font
	TTF_CloseFont(_font);

	// Quit SDL_ttf library
	TTF_Quit();
}

int TextWidget::draw()
{
	// Load the font
	_font = TTF_OpenFont("assets/fonts/cheese.ttf", _size);

	// Render text to an SDL_Surface
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(_font, "HIIIIIIIII", SDL_Color(255, 50, 125));

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
