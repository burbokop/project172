#include "abstractrenderengine.h"

using namespace e172;


Image AbstractGraphicsProvider::__createImage(
        Image::ptr data,
        Image::ptr id,
        int width,
        int height,
        Image::destructor_t destructor,
        Image::nub_t nub,
        Image::transformer_t transformer) {
    return Image::newImage(data, id, width, height, destructor, nub, transformer);
}

void AbstractGraphicsProvider::installParentToRenderer(AbstractRenderer *renderer) {
    renderer->m_provider = this;
    renderer->m_isActive = true;
}
