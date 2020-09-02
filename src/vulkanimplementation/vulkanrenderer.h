#ifndef VULKANRENDERER_H
#define VULKANRENDERER_H

#include "../engine/graphics/abstractrenderer.h"

#include <list>

namespace e172vp {
    class PresentationObject;
    class Mesh;
    class VertexObject;
}

class VulkanRenderer : public e172::AbstractRenderer {
    e172vp::PresentationObject *m_presentationObject = nullptr;
    e172vp::Mesh *m_mesh0 = nullptr;
    e172vp::Mesh *m_mesh1 = nullptr;

    struct ImageReciept {
        e172::Vector position;
        float rotation;
    };

    const e172::Vector m_resolution = e172::Vector(800, 600);
    double divider = 1080;

    std::list<ImageReciept> m_reciepts;
    std::list<e172vp::VertexObject*> m_objectsPool;
public:
    VulkanRenderer(const std::vector<std::string> &args);
    ~VulkanRenderer();
    // AbstractRenderer interface
protected:
    virtual bool update() override;

public:
    bool isValid() const;

    virtual void fill(uint32_t color) override;
    virtual void drawPixel(const e172::Vector &point, uint32_t color) override;
    virtual void drawLine(const e172::Vector &point0, const e172::Vector &point1, uint32_t color) override;
    virtual void drawRect(const e172::Vector &point0, const e172::Vector &point1, uint32_t color) override;
    virtual void drawSquare(const e172::Vector &point, int radius, uint32_t color) override;
    virtual void drawCircle(const e172::Vector &point, int radius, uint32_t color) override;
    virtual void drawDiagonalGrid(const e172::Vector &point0, const e172::Vector &point1, int interval, uint32_t color) override;
    virtual void drawImage(const e172::Image &image, const e172::Vector &position, double angle, double zoom) override;
    virtual e172::Vector drawString(const std::string &string, const e172::Vector &positions, uint32_t color, const e172::TextFormat &format) override;
    virtual void applyLensEffect(const e172::Vector &point0, const e172::Vector &point1, double coefficient) override;
    virtual void applySmooth(const e172::Vector &point0, const e172::Vector &point1, double coefficient) override;
    virtual void enableEffect(uint64_t effect) override;
    virtual void disableEffect(uint64_t effect) override;
    virtual void setFullscreen(bool value) override;
    virtual void setResolution(e172::Vector value) override;
    virtual e172::Vector resolution() const override;
    virtual e172::Vector screenSize() const override;
};

#endif // VULKANRENDERER_H
