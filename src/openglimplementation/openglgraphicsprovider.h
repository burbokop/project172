#ifndef OPENGLGRAPHICSPROVIDER_H
#define OPENGLGRAPHICSPROVIDER_H

#include <engine/graphics/abstractgraphicsprovider.h>



class OpenGLGraphicsProvider : public e172::AbstractGraphicsProvider {
public:
    OpenGLGraphicsProvider();

    // AbstractGraphicsProvider interface
public:
    virtual e172::AbstractRenderer *renderer() const override;
    virtual e172::Image loadImage(const std::string &path) const override;
    virtual e172::Image createImage(void *bitmap, int format) const override;
    virtual e172::Font loadFont(const std::string &font) override;
};

#endif // OPENGLGRAPHICSPROVIDER_H
