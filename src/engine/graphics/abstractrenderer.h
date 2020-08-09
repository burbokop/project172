#ifndef ABSTRACTRENDERER_H
#define ABSTRACTRENDERER_H

#include "image.h"
#include "../math/vector.h"

#include <inttypes.h>

#include <additional/e_variant.h>

#include <engine/textformat.h>

class Camera;

namespace e172 {
class AbstractGraphicsProvider;
class AbstractRenderer {
    friend AbstractGraphicsProvider;
    bool m_isActive = false;

    AbstractGraphicsProvider *m_provider = nullptr;
protected:
    template<typename T>
    static T imageData(const Image &image) { return Image::handle_cast<T>(image.m_data)->c; }
    static Image::ptr imageId(const Image &image);
    AbstractGraphicsProvider *provider() const;
public:
    typedef int Lens;
    virtual ~AbstractRenderer();

    virtual void fill(uint32_t color) = 0;
    virtual void drawPixel(const Vector &point, uint32_t color) = 0;
    virtual void drawLine(const Vector &point1, const Vector &point2, uint32_t color) = 0;
    virtual void drawRect(const Vector &point1, const Vector &point2, uint32_t color) = 0;
    virtual void drawSquare(const Vector &point, int radius, uint32_t color) = 0;
    virtual void drawCircle(const Vector &point, int radius, uint32_t color) = 0;
    virtual void drawDiagonalGrid(const Vector &point1, const Vector &point2, int interval, uint32_t color) = 0;

    virtual void drawImage(const Image &image, const Vector &pos, double angle, double zoom) = 0;
    virtual Vector drawString(const std::string &string, const Vector &pos, uint32_t color, const TextFormat &format = TextFormat()) = 0;

    virtual Lens enableLensEffect(const Vector &point1, const Vector &point2, double coefficient) = 0;
    virtual bool updateLensEffect(Lens lens, const Vector &point1, const Vector &point2, double coefficient) = 0;
    virtual bool disableLensEffect(Lens lens) = 0;

    virtual Vector resolution() const = 0;
    virtual Vector offset() const = 0;


    virtual void enableEffect(uint64_t effect) = 0;
    virtual void disableEffect(uint64_t effect) = 0;


    /**
     * deprecated functionns;
     */

    [[deprecated]]
    virtual void update() = 0;



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

    bool isActive() const;
};

}
#endif // ABSTRACTRENDERER_H
