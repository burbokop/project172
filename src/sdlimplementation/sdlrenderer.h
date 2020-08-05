#ifndef SDLRENDERER_H
#define SDLRENDERER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <engine/abstractrenderer.h>
#include <map>


#include "additional/effects/visualeffect.h"
#include <src/engine/math/vector.h>
#include "additional/variant.h"





class SDLRenderer : public e172::AbstractRenderer {
    friend class SDLGraphicsProvider;
public:
    static const int DEFAULT_FONT_SIZE;
private:
    Camera *camera = nullptr;
    e172::Vector m_offset;

    SDL_Window *window = nullptr;
    SDL_Surface *surface = nullptr;
    std::map<int, TTF_Font *> fonts;
    std::string fontPath;

    bool fullscreen = false;
    e172::Vector m_resolution;
    SDLRenderer(const char *title, int x, int y, std::string fontPath);
public:

    void fill(uint32_t color) override;
    void drawPixel(e172::Vector point, uint32_t color) override;
    void drawLine(e172::Vector point1, e172::Vector point2, uint32_t color) override;
    void drawRect(e172::Vector point1, e172::Vector point2, uint32_t color) override;
    void drawSquare(e172::Vector point, int radius, uint32_t color) override;
    void drawCircle(e172::Vector point, int radius, uint32_t color) override;
    void drawDiagonalGrid(e172::Vector point1, e172::Vector point2, int interval, uint32_t color) override;

    void drawImage(const e172::Image &image, e172::Vector pos, double angle, double zoom) override;

    void drawString(std::string string, e172::Vector pos, uint32_t color, const e172::TextFormat &format = e172::TextFormat()) override;


    e172::Vector resolution() const override;
    e172::Vector offset() const override;


    /**
     * deprecated functionns;
     */
    [[deprecated]]
    e172::Image cutOuImaget(const e172::Image &image) const override;
    [[deprecated]]
    void update() override;
    [[deprecated]]
    void quit() override;
    [[deprecated]]
    void effect(VisualEffect *applied_effect, bool lock = false) override;
    [[deprecated]]
    void setFullscreen() override;
    [[deprecated]]
    void setResolution(e172::Vector value) override;
    [[deprecated]]
    void setResolutionCallback(Variant value) override;
    [[deprecated]]
    void setCamera(Camera *value) override;
    [[deprecated]]
    Camera *getCamera() const override;
    [[deprecated]]
    e172::Vector getStringSize(std::string string, int size) override;
};


#endif // SDLRENDERER_H
