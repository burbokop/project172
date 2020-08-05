#ifndef ABSTRACTRENDERER_H
#define ABSTRACTRENDERER_H

#include "image.h"
#include "textformat.h"
#include "math/vector.h"

#include <inttypes.h>

#include <additional/effects/visualeffect.h>

#include <additional/variant.h>

class Camera;

namespace e172 {
class AbstractGraphicsProvider;
class AbstractRenderer {
    friend AbstractGraphicsProvider;
    bool m_isActive = false;

    AbstractGraphicsProvider *m_provider = nullptr;
protected:
    static Image::ptr imageData(const Image &image);
    static Image::ptr imageId(const Image &image);
    AbstractGraphicsProvider *provider() const;
public:
    virtual ~AbstractRenderer();

    virtual void fill(uint32_t color) = 0;
    virtual void drawPixel(Vector point, uint32_t color) = 0;
    virtual void drawLine(Vector point1, Vector point2, uint32_t color) = 0;
    virtual void drawRect(Vector point1, Vector point2, uint32_t color) = 0;
    virtual void drawSquare(Vector point, int radius, uint32_t color) = 0;
    virtual void drawCircle(Vector point, int radius, uint32_t color) = 0;
    virtual void drawDiagonalGrid(Vector point1, Vector point2, int interval, uint32_t color) = 0;

    virtual void drawImage(const Image &image, Vector pos, double angle, double zoom) = 0;
    virtual void drawString(std::string string, Vector pos, uint32_t color, const TextFormat &format = TextFormat()) = 0;


    virtual Vector resolution() const = 0;
    virtual Vector offset() const = 0;

    /**
     * deprecated functionns;
     */

    [[deprecated]]
    virtual Image cutOuImaget(const Image &image) const = 0;
    [[deprecated]]
    virtual void update() = 0;
    [[deprecated]]
    virtual void quit() = 0;
    [[deprecated]]
    virtual void effect(VisualEffect *applied_effect, bool lock = false) = 0;
    [[deprecated]]
    virtual void setFullscreen() = 0;
    [[deprecated]]
    virtual void setResolution(Vector value) = 0;
    [[deprecated]]
    virtual void setResolutionCallback(Variant value) = 0;
    [[deprecated]]
    virtual void setCamera(Camera *value) = 0;
    [[deprecated]]
    virtual Camera *getCamera() const = 0;
    [[deprecated]]
    virtual e172::Vector getStringSize(std::string string, int size) = 0;

    bool isActive() const;
};

}
#endif // ABSTRACTRENDERER_H
