#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "additional/spm.h"
#include "../additional/vector.h"

class Renderer : public Object
{
private:
    SDL_Window *window;
    SDL_Surface *surface;
public:
    Renderer(SDL_Window *window, SDL_Surface *surface);
    static Renderer *create(const char *title, int w, int h);
    static Renderer *create(const char *title, Vector resolution);

    void fill(Uint32 color);
    void pixel(Vector point, Uint32 color);
    void line(Vector point1, Vector point2, Uint32 color);
    void rect(Vector point1, Vector point2, Uint32 color);
    void image(SDL_Surface *image, Vector pos, double angle, double zoom);
    void update();
    void quit();
};

#endif // RENDERER_H
