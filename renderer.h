#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "additional/spm.h"
#include "../additional/vector.h"

class Renderer : public Object
{
public:
    static const int DEFAULT_FONT_SIZE;

private:

    SDL_Window *window;
    SDL_Surface *surface;
    TTF_Font *font;
public:
    Renderer(SDL_Window *window, SDL_Surface *surface, TTF_Font *font);
    static Renderer *create(const char *title, int w, int h, std::string fontPath);
    static Renderer *create(const char *title, Vector resolution, std::string fontPath);

    void fill(Uint32 color);
    void pixel(Vector point, Uint32 color);
    void line(Vector point1, Vector point2, Uint32 color);
    void rect(Vector point1, Vector point2, Uint32 color);
    void image(SDL_Surface *image, Vector pos, double angle, double zoom);
    void string(std::string string, Vector pos, Uint32 color);
    void update();
    void quit();
};

#endif // RENDERER_H
