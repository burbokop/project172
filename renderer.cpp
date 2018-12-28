#include "renderer.h"

const int Renderer::DEFAULT_FONT_SIZE = 16;


Renderer::Renderer(SDL_Window *window, SDL_Surface *surface, TTF_Font *font) {
    this->window = window;
    this->surface = surface;
    this->font = font;
}

Renderer *Renderer::create(const char *title, int w, int h, std::string fontPath) {
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    SDL_Window *window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, 0);
    SDL_Surface *surface = SDL_GetWindowSurface(window);
    return new Renderer(window, surface, TTF_OpenFont(fontPath.c_str(), DEFAULT_FONT_SIZE));
}

Renderer *Renderer::create(const char *title, Vector resolution, std::string fontPath) {
    return create(title, resolution.getIntX(), resolution.getIntY(), fontPath);
}

void Renderer::fill(Uint32 color) {
    SDL_FillRect(surface, nullptr, color);
}

void Renderer::pixel(Vector point, Uint32 color) {
    SPM::FillPixel(surface, point.getIntX(), point.getIntY(), color);
}

void Renderer::line(Vector point1, Vector point2, Uint32 color) {
    SDL_LockSurface(surface);
    SPM::Line(surface, point1.getIntX(), point1.getIntY(), point2.getIntX(), point2.getIntY(), color);
    SDL_UnlockSurface(surface);
}

void Renderer::rect(Vector point1, Vector point2, Uint32 color) {
    SDL_LockSurface(surface);
    SPM::Rect(surface, point1.getIntX(), point1.getIntY(), point2.getIntX(), point2.getIntY(), color);
    SDL_UnlockSurface(surface);
}

void Renderer::image(SDL_Surface *image, Vector pos, double angle, double zoom) {
    SPM::BlitRotatedSurface(image, surface, pos.getIntX(), pos.getIntY(), angle, zoom, 1);
}

void Renderer::string(std::string string, Vector pos, Uint32 color) {
    if(font) {
        SPM::BlendedText(surface, string, font, pos.getIntX(), pos.getIntY(), color);
    }
}

void Renderer::update()
{
    SDL_UpdateWindowSurface(window);
}

void Renderer::quit()
{
    SDL_FreeSurface(surface);
    TTF_Quit();
    SDL_Quit();
}
