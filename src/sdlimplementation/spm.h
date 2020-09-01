#ifndef SPM_H
#define SPM_H

#define SPM_PI 3.141592653589793238462643383279502884
#define RADS_MULTIPLIER -180 / SPM_PI

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <functional>
#include <src/sdlimplementation/effects/visualeffect.h>


class SPM {
public:
    static Uint32 ColorRGB(Uint8 R, Uint8 G, Uint8 B);

    static void FillPixel(SDL_Surface *surface, int x, int y, Uint32 color);
    static Uint32 GetPixel(SDL_Surface *surface, int x, int y);

    static inline SDL_Surface *CreateARGB32Surface(int width, int height);
    static inline SDL_Surface *CreateRGBA32Surface(int x, int y);
    static inline SDL_Surface *CreateABGR32Surface(int x, int y);

    static void ApplyEffect(VisualEffect *effect);
    static void LockEffect(VisualEffect *effect);
    static void UnlockEffect();

    static void Line(SDL_Surface *surface, int point1_x, int point1_y, int point2_x, int point2_y, Uint32 color);
    static void VerticalLine(SDL_Surface *surface, int point_x, int point_y, int l, Uint32 color);
    static void HorizontalLine(SDL_Surface *surface, int point_x, int point_y, int l, Uint32 color);
    static void Square(SDL_Surface *surface, int point_x, int point_y, int l, Uint32 color);
    static void FillSquare(SDL_Surface *surface, int point_x, int point_y, int l, Uint32 color);
    static void Rect(SDL_Surface *surface, int point1_x, int point1_y, int point2_x, int point2_y, Uint32 color);
    static void FillArea(SDL_Surface *surface, int point1_x, int point1_y, int point2_x, int point2_y, Uint32 color);
    static void Circle(SDL_Surface *surface, int point1_x, int point1_y, int radius, Uint32 color);
    static void Grid(SDL_Surface *surface, int point1_x, int point1_y, int point2_x, int point2_y, int interval, Uint32 color);
    static void DiagonalGrid(SDL_Surface *surface, int point1_x, int point1_y, int point2_x, int point2_y, int interval, Uint32 color);


    static void BlitRotatedSurface(SDL_Surface *surface, SDL_Surface *screen_surface, int x, int y, double angle, double zoom, int smooth, VisualEffect *effect = nullptr);

    static void BlendedText(SDL_Surface *surface, std::string text_line, TTF_Font *text_font, int text_x, int text_y, SDL_Color text_color, VisualEffect *effect = nullptr);
    static void BlendedText(SDL_Surface *surface, std::string text_line, TTF_Font *text_font, int text_x, int text_y, Uint32 color, Uint32 wrap = 1024, VisualEffect *effect = nullptr);

    static SDL_Surface *CutOutSurface(const SDL_Surface *surface, int x, int y, int w, int h);
    static SDL_Surface *Flip(SDL_Surface *surface, bool xFlip, bool yFlip);
};


#endif
