#ifndef SPM_H
#define SPM_H

#define SPM_PI 3.141592653589793238462643383279502884
#define RADS_MULTIPLIER -180 / SPM_PI

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

#include "rotozoom.h"

namespace SPM {
    Uint32 ColorRGB(Uint8 R, Uint8 G, Uint8 B);

    void FillPixel(SDL_Surface *surface, int x, int y, Uint32 color);
    Uint32 GetPixel(SDL_Surface *surface, int x, int y);

    void Line(SDL_Surface *surface, int point1_x, int point1_y, int point2_x, int point2_y, Uint32 color);
    void VerticalLine(SDL_Surface *surface, int point_x, int point_y, int l, Uint32 color);
    void HorizontalLine(SDL_Surface *surface, int point_x, int point_y, int l, Uint32 color);
    void Square(SDL_Surface *surface, int point_x, int point_y, int l, Uint32 color);
    void FillSquare(SDL_Surface *surface, int point_x, int point_y, int l, Uint32 color);
    void Rect(SDL_Surface *surface, int point1_x, int point1_y, int point2_x, int point2_y, Uint32 color);
    void FillArea(SDL_Surface *surface, int point1_x, int point1_y, int point2_x, int point2_y, Uint32 color);
    void Circle(SDL_Surface *surface, int point1_x, int point1_y, int radius, Uint32 color);
    void Grid(SDL_Surface *surface, int point1_x, int point1_y, int point2_x, int point2_y, int interval, Uint32 color);

    void BlitRotatedSurface(SDL_Surface *surface, SDL_Surface *screen_surface, int x, int y, double angle, double zoom, int smooth);

    void BlendedText(SDL_Surface *surface, std::string text_line, TTF_Font *text_font, int text_x, int text_y, SDL_Color text_color);
    void BlendedText(SDL_Surface *surface, std::string text_line, TTF_Font *text_font, int text_x, int text_y, Uint32 color, Uint32 wrap = 1024);

    SDL_Surface *CutOutSurface(SDL_Surface *surface, int x, int y, int w, int h);
    SDL_Surface *Flip(SDL_Surface *surface, bool xFlip, bool yFlip);
}

#endif
