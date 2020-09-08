#ifndef SDLRENDERER_H
#define SDLRENDERER_H

#include <src/engine/graphics/abstractrenderer.h>
#include <map>

#include <src/engine/math/vector.h>
#include <queue>

struct SDL_Window;
struct SDL_Surface;
struct _TTF_Font;
typedef _TTF_Font TTF_Font;
class SDLRenderer : public e172::AbstractRenderer {
    friend class SDLGraphicsProvider;

    static inline auto sdl_initialized = false;
public:
    static const int DefaultFontSize;
private:
    Camera *camera = nullptr;

    SDL_Window *window = nullptr;
    SDL_Surface *surface = nullptr;


    struct Font {
        typedef std::map<int, TTF_Font*> sizes_t;
        std::string path;
        sizes_t sizes;
    };
    std::map<std::string, Font> m_fonts;


    bool m_lastFullscreen = false;
    e172::Vector m_resolution;
    bool anaglyphEnabled = false;
    bool anaglyphEnabled2 = false;
    SDLRenderer(const char *title, int x, int y);


    struct LensReciept {
        e172::Vector point0;
        e172::Vector point1;
        double coeficient;
    };
    std::queue<LensReciept> m_lensQueue;
    static void __applyLensEffect(SDL_Surface * surface, const e172::Vector point0, const e172::Vector point1, double coef);
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

    void enableEffect(uint64_t effect) override;
    void disableEffect(uint64_t effect) override;

    e172::Vector resolution() const override;
    void setResolution(e172::Vector value) override;
    virtual void setFullscreen(bool value) override;
    virtual e172::Vector screenSize() const override;

    ~SDLRenderer() override;

    // AbstractRenderer interface
public:
    virtual void applyLensEffect(const e172::Vector &point0, const e172::Vector &point1, double coefficient) override;
    virtual void applySmooth(const e172::Vector &point0, const e172::Vector &point1, double coefficient) override;

    // AbstractRenderer interface
protected:
    virtual bool update() override;
};


#endif // SDLRENDERER_H
