#include "openglrenderer.h"

OpenGLRenderer::OpenGLRenderer() {

}


void OpenGLRenderer::fill(uint32_t color)
{
}

void OpenGLRenderer::drawPixel(const e172::Vector &point, uint32_t color)
{
}

void OpenGLRenderer::drawLine(const e172::Vector &point1, const e172::Vector &point2, uint32_t color)
{
}

void OpenGLRenderer::drawRect(const e172::Vector &point1, const e172::Vector &point2, uint32_t color)
{
}

void OpenGLRenderer::drawSquare(const e172::Vector &point, int radius, uint32_t color)
{
}

void OpenGLRenderer::drawCircle(const e172::Vector &point, int radius, uint32_t color)
{
}

void OpenGLRenderer::drawDiagonalGrid(const e172::Vector &point1, const e172::Vector &point2, int interval, uint32_t color)
{
}

void OpenGLRenderer::drawImage(const e172::Image &image, const e172::Vector &pos, double angle, double zoom)
{
}

e172::Vector OpenGLRenderer::drawString(const std::string &string, const e172::Vector &pos, uint32_t color, const e172::TextFormat &format)
{
}

void OpenGLRenderer::applySmooth(const e172::Vector &point0, const e172::Vector &point1, double coefficient)
{
}

e172::Vector OpenGLRenderer::resolution() const
{
}

void OpenGLRenderer::enableEffect(uint64_t effect)
{
}

void OpenGLRenderer::disableEffect(uint64_t effect)
{
}

void OpenGLRenderer::update()
{
}

void OpenGLRenderer::setFullscreen()
{
}

void OpenGLRenderer::setResolution(e172::Vector value)
{
}

void OpenGLRenderer::setResolutionCallback(old::Variant value) {
}

