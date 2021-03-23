#include "TextTexture.h"
TextTexture::TextTexture(SDL_Renderer* renderer, TTF_Font* font) {
	m_renderer = renderer;
	m_font = font;
	m_text = "no text";

	SDL_Surface *temp = TTF_RenderText_Solid(font, m_text.c_str(), SDL_Color{ 255,255,255,255 });
	m_texture = SDL_CreateTextureFromSurface(renderer, temp);
	SDL_QueryTexture(m_texture, NULL, NULL, &m_rect.w, &m_rect.h);
}
TextTexture::TextTexture(SDL_Renderer* renderer, std::string text, TTF_Font* font) {
	m_renderer = renderer;
	m_font = font;
	m_text = text;

	SDL_Surface* temp = TTF_RenderText_Solid(font, m_text.c_str(), SDL_Color{ 255,255,255,255 });
	m_texture = SDL_CreateTextureFromSurface(renderer, temp);
	SDL_QueryTexture(m_texture, NULL, NULL, &m_rect.w, &m_rect.h);
}

void TextTexture::setPosition(const SDL_Point& point, bool centered) {
	if (centered) {
		m_rect.x = point.x - m_rect.w / 2;
		m_rect.y = point.y - m_rect.h / 2;
	}
	else {
		m_rect.x = point.x;
		m_rect.y = point.y;
	}
}
SDL_Point* TextTexture::getPosition() {
	return new SDL_Point{ m_rect.x, m_rect.y };
}
void TextTexture::setText(std::string text, bool centered) {
	m_text = text;
	m_texture = SDL_CreateTextureFromSurface(m_renderer,
		TTF_RenderText_Solid(m_font, text.c_str(), SDL_Color{ 255,255,255,255 }));
	SDL_QueryTexture(m_texture, NULL, NULL, &m_rect.w, &m_rect.h);
	setPosition(SDL_Point{ m_rect.x, m_rect.y });
}

SDL_Rect* TextTexture::getRect() {
	return &m_rect;
}
SDL_Texture* TextTexture::getTexture() {
	return m_texture;
}

void TextTexture::setColor(const SDL_Color& color) {
	m_texture = SDL_CreateTextureFromSurface(m_renderer,
		TTF_RenderText_Solid(m_font, m_text.c_str(), color));
}

bool operator==(TextTexture textTexture1, TextTexture textTexture2) {
	return textTexture1.m_text == textTexture2.m_text ? true : false;
}