#ifndef SDLGRAPHICSPROVIDER_H
#define SDLGRAPHICSPROVIDER_H

#include "sdlrenderer.h"

#include <src/engine/graphics/abstractgraphicsprovider.h>




class SDLGraphicsProvider : public e172::AbstractGraphicsProvider {
    SDLRenderer *m_renderer = nullptr;

public:
    SDLGraphicsProvider(const char *title, int x, int y);
    ~SDLGraphicsProvider() override;

    // AbstractGraphicsProvider interface
public:
    virtual e172::AbstractRenderer *renderer() const override;
    virtual e172::Image loadImage(const std::string &path) const override;
    virtual e172::Image createImage(int width, int height) const override;
    virtual void loadFont(const std::string &name, const std::string &path) override;
};



#endif // SDLGRAPHICSPROVIDER_H
