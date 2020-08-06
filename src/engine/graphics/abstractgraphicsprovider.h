#ifndef ABSTRACTRENDERENGINE_H
#define ABSTRACTRENDERENGINE_H

#include "abstractrenderer.h"
#include "image.h"
#include <string>



namespace e172 {


class AbstractGraphicsProvider {


protected:
    static Image __createImage(
            Image::ptr data,
            Image::ptr id,
            int width,
            int height,
            Image::destructor_t destructor,
            Image::bitmap_getter_t bitmap_getter,
            Image::nub_t nub = Image::nub_t(),
            Image::transformer_t transformer = Image::transformer_t()
            );
    void installParentToRenderer(AbstractRenderer *renderer);
public:
    virtual AbstractRenderer *renderer() const = 0;
    virtual Image loadImage(const std::string &path) const = 0;
    virtual Image createImage(void* bitmap, int format) const = 0;

};

}

#endif // ABSTRACTRENDERENGINE_H
