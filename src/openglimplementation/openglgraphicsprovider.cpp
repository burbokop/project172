#include "openglgraphicsprovider.h"

OpenGLGraphicsProvider::OpenGLGraphicsProvider() {}

e172::AbstractRenderer *OpenGLGraphicsProvider::renderer() const {
    return nullptr;
}

e172::Image OpenGLGraphicsProvider::loadImage(const std::string &path) const {
    (void)path;
    return e172::Image();
}

e172::Image OpenGLGraphicsProvider::createImage(int width, int height) const {
    (void)width;
    (void)height;
    return e172::Image();
}

