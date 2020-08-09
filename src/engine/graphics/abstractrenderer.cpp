#include "abstractrenderer.h"

using namespace e172;




Image::ptr AbstractRenderer::imageId(const Image &image) {
    return image.id();
}

AbstractGraphicsProvider *AbstractRenderer::provider() const {
    return m_provider;
}

AbstractRenderer::~AbstractRenderer() {}

bool AbstractRenderer::isActive() const {
    return m_isActive;
}
