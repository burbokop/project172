#include "abstractrenderer.h"

using namespace e172;



Image::ptr AbstractRenderer::imageId(const Image &image) {
    return image.id();
}

AbstractGraphicsProvider *AbstractRenderer::provider() const {
    return m_provider;
}

AbstractRenderer::~AbstractRenderer() {}

Vector AbstractRenderer::offset() const {
    return resolution() / 2 - cameraPosition();
}

AbstractRenderer::Camera AbstractRenderer::detachCamera() {
    if(!m_cameraLocked) {
        Camera c = Camera::newSharedContainer<Camera>(new Camera::void_handle, this, [this](Camera::data_ptr d) {
                m_cameraLocked = false;
                delete Camera::handle_cast<void*>(d);
        });
        c.m_setter = [this](const Vector &vector){ m_position = vector; };
        c.m_getter = [this](){ return m_position; };
        c.m_renderer = this;
        m_cameraLocked = true;
        return c;
    }
    return Camera();
}

Vector AbstractRenderer::cameraPosition() const {
    return m_position;
}

bool AbstractRenderer::isActive() const {
    return m_isActive;
}

AbstractRenderer * AbstractRenderer::Camera::renderer() const {
    return m_renderer;
}

void AbstractRenderer::Camera::setPosition(const Vector &position) {
    if(m_setter)
        m_setter(position);
}

Vector AbstractRenderer::Camera::position() const {
    if(m_getter)
        return m_getter();
    return Vector();
}
