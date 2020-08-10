#ifndef SDLGRAPHICSPROVIDER_H
#define SDLGRAPHICSPROVIDER_H

#include "sdlrenderer.h"

#include <engine/graphics/abstractgraphicsprovider.h>




class SDLGraphicsProvider : public e172::AbstractGraphicsProvider {
    const char *m_title;
    int m_x;
    int m_y;
    std::string m_fontPath;
    SDLRenderer *m_renderer = nullptr;
    std::map<int, TTF_Font*> m_fonts;
public:
    SDLGraphicsProvider(const char *title, int x, int y, std::string fontPath);
    ~SDLGraphicsProvider();

    // AbstractGraphicsProvider interface
public:
    virtual e172::AbstractRenderer *renderer() const override;
    virtual e172::Image loadImage(const std::string &path) const override;
    virtual e172::Image createImage(void *bitmap, int format) const override;
    virtual e172::Font loadFont(const std::string &font) override;
};



#endif // SDLGRAPHICSPROVIDER_H
