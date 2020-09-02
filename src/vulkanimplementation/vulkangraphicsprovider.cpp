#include "vulkangraphicsprovider.h"

VulkanGraphicsProvider::VulkanGraphicsProvider(const std::vector<std::string> &args) : e172::AbstractGraphicsProvider(args) {
    m_renderer = new VulkanRenderer(args);
    installParentToRenderer(m_renderer);
}

VulkanGraphicsProvider::~VulkanGraphicsProvider() {
    delete m_renderer;
}

e172::AbstractRenderer *VulkanGraphicsProvider::renderer() const {
    return m_renderer;
}

bool VulkanGraphicsProvider::isValid() const {
    return m_renderer->isValid();
}

e172::Image VulkanGraphicsProvider::loadImage(const std::string &path) const {
    return e172::Image();
}

e172::Image VulkanGraphicsProvider::createImage(int width, int height) const {
    return e172::Image();
}

void VulkanGraphicsProvider::loadFont(const std::string &name, const std::string &path) {

}
