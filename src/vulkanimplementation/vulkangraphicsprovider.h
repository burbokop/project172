#ifndef VULKANGRAPHICSPROVIDER_H
#define VULKANGRAPHICSPROVIDER_H

#include <src/graphics/abstractgraphicsprovider.h>

#include "vulkanrenderer.h"

class VulkanGraphicsProvider : public e172::AbstractGraphicsProvider {
    VulkanRenderer *m_renderer = nullptr;
public:
    VulkanGraphicsProvider(const std::vector<std::string> &args);
    ~VulkanGraphicsProvider();

    // AbstractGraphicsProvider interface
public:
    virtual e172::AbstractRenderer *renderer() const override;
    virtual bool isValid() const override;
    virtual e172::Image loadImage(const std::string &path) const override;
    virtual e172::Image createImage(int width, int height) const override;
    virtual void loadFont(const std::string &name, const std::string &path) override;

};

#endif // VULKANGRAPHICSPROVIDER_H
