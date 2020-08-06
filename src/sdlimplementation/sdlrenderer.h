#ifndef SDLRENDERER_H
#define SDLRENDERER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <engine/graphics/abstractrenderer.h>
#include <map>


#include "additional/effects/visualeffect.h"
#include <src/engine/math/vector.h>
#include "additional/e_variant.h"





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
    bool anaglyphEnabled = false;
    bool anaglyphEnabled2 = false;
    SDLRenderer(const char *title, int x, int y, std::string fontPath);
public:

    void fill(uint32_t color) override;
    void drawPixel(const e172::Vector &point, uint32_t color) override;
    void drawLine(const e172::Vector &point1, const e172::Vector &point2, uint32_t color) override;
    void drawRect(const e172::Vector &point1, const e172::Vector &point2, uint32_t color) override;
    void drawSquare(const e172::Vector &point, int radius, uint32_t color) override;
    void drawCircle(const e172::Vector &point, int radius, uint32_t color) override;
    void drawDiagonalGrid(const e172::Vector &point1, const e172::Vector &point2, int interval, uint32_t color) override;

    void drawImage(const e172::Image &image, const e172::Vector &pos, double angle, double zoom) override;

    e172::Vector drawString(const std::string &string, const e172::Vector &pos, uint32_t color, const e172::TextFormat &format = e172::TextFormat()) override;


    e172::Vector resolution() const override;
    e172::Vector offset() const override;

    void enableEffect(uint64_t effect) override;
    void disableEffect(uint64_t effect) override;


    ~SDLRenderer();

    /**
     * deprecated functionns;
     */
    [[deprecated]]
    void update() override;
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

};


#endif // SDLRENDERER_H
