#ifndef OPENGLRENDERER_H
#define OPENGLRENDERER_H

#include <engine/graphics/abstractrenderer.h>



class OpenGLRenderer : public e172::AbstractRenderer {
public:
    OpenGLRenderer();

    // AbstractRenderer interface
public:
    virtual void fill(uint32_t color) override;
    virtual void drawPixel(const e172::Vector &point, uint32_t color) override;
    virtual void drawLine(const e172::Vector &point1, const e172::Vector &point2, uint32_t color) override;
    virtual void drawRect(const e172::Vector &point1, const e172::Vector &point2, uint32_t color) override;
    virtual void drawSquare(const e172::Vector &point, int radius, uint32_t color) override;
    virtual void drawCircle(const e172::Vector &point, int radius, uint32_t color) override;
    virtual void drawDiagonalGrid(const e172::Vector &point1, const e172::Vector &point2, int interval, uint32_t color) override;
    virtual void drawImage(const e172::Image &image, const e172::Vector &pos, double angle, double zoom) override;
    virtual e172::Vector drawString(const std::string &string, const e172::Vector &pos, uint32_t color, const e172::TextFormat &format) override;
    virtual void applySmooth(const e172::Vector &point0, const e172::Vector &point1, double coefficient) override;
    virtual e172::Vector resolution() const override;
    virtual void enableEffect(uint64_t effect) override;
    virtual void disableEffect(uint64_t effect) override;

    virtual void update() override;
    virtual void setFullscreen() override;
    virtual void setResolution(e172::Vector value) override;
    virtual void setResolutionCallback(Variant value) override;
};

#endif // OPENGLRENDERER_H
