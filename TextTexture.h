#pragma once
#include "SDL_ttf.h"
#include "SDL.h"
#include "SDL_image.h"
#include <string>
class TextTexture {
public:
	TextTexture(SDL_Renderer* renderer, TTF_Font* font);
	TextTexture(SDL_Renderer* renderer, std::string text, TTF_Font* font);
	void setPosition(const SDL_Point& point, bool centered = true);
	void setColor(const SDL_Color& color);
	void setText(std::string text, bool centered = true);
	SDL_Point* getPosition();
	SDL_Rect* getRect();
	SDL_Texture* getTexture();
private:
	SDL_Rect m_rect{ 0,0,0,0 };
	SDL_Renderer* m_renderer = nullptr;
	TTF_Font* m_font = nullptr;
	std::string m_text;
	SDL_Texture* m_texture = nullptr;
	friend bool operator==(TextTexture textTexture1, TextTexture textTexture2);
};