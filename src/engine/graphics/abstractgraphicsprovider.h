#ifndef ABSTRACTRENDERENGINE_H
#define ABSTRACTRENDERENGINE_H

#include "abstractrenderer.h"
#include "image.h"
#include <string>


namespace e172 {


class AbstractGraphicsProvider {


protected:
    static Image __createImage(Image::data_ptr data,
            Image::ptr id,
            int width,
            int height,
            Image::destructor_t destructor,
            Image::bitmap_getter_t bitmap_getter,
            Image::fragment_t fragment = Image::fragment_t(),
            Image::transformer_t transformer = Image::transformer_t()
            );
    void installParentToRenderer(AbstractRenderer *renderer);
public:
    virtual AbstractRenderer *renderer() const = 0;
    virtual Image loadImage(const std::string &path) const = 0;
    virtual Image createImage(int width, int height) const = 0;
    virtual void loadFont(const std::string &name, const std::string &path) = 0;
    virtual ~AbstractGraphicsProvider();
};

}

#endif // ABSTRACTRENDERENGINE_H
