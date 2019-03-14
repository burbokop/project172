#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <map>


#include "additional/effects/visualeffect.h"
#include "additional/vector.h"
#include "additional/variant.h"


class Camera;

class Renderer : public Object {
public:
    static const int DEFAULT_FONT_SIZE;
private:
    Camera *camera = nullptr;
    Vector offset;

    SDL_Window *window = nullptr;
    SDL_Surface *surface = nullptr;
    std::map<int, TTF_Font *> fonts;
    std::string fontPath;

    bool fullscreen = false;
    Vector resolution;
public:
    Renderer(const char *title, int x, int y, std::string fontPath);

    void effect(VisualEffect *applied_effect, bool lock = false);
    void fill(Uint32 color);
    void setFullscreen();
    void pixel(Vector point, Uint32 color);
    void line(Vector point1, Vector point2, Uint32 color);
    void rect(Vector point1, Vector point2, Uint32 color);
    void square(Vector point, int radius, Uint32 color);
    void circle(Vector point, int radius, Uint32 color);
    void diagonalGrid(Vector point1, Vector point2, int interval, Uint32 color);

    void image(SDL_Surface *image, Vector pos, double angle, double zoom);
    void string(std::string string, Vector pos, Uint32 color);
    void string(std::string string, Vector pos, Uint32 color, int size);
    void stringCentered(std::string string, Vector pos, Uint32 color, int size);
    Vector getStringSize(std::string string, int size);


    void update();
    void quit();

    Vector getResolution();
    Vector getOffset();


    void setResolution(Vector value);
    void setResolutionCallback(Variant value);
    void setCamera(Camera *value);
    Camera *getCamera() const;
};

#endif // RENDERER_H
