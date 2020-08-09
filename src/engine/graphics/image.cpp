#include "image.h"

using namespace e172;

int Image::width() const
{
    return m_width;
}

int Image::height() const
{
    return m_height;
}

Image Image::newImage(data_ptr data, ptr id, int width, int height, destructor_t destructor, bitmap_getter_t bitmap_getter, fragment_t fragment, transformer_t transformer) {
    Image i = newSharedContainer<Image>(data, id, destructor);
    i.m_width = width;
    i.m_height = height;

    i.m_bitmap_getter = bitmap_getter;
    i.m_transformer = transformer;
    i.m_fragment = fragment;

    return i;
}

Image::Image() {}


Image Image::transformed(uint64_t transformation) const {
    Image result = *this;
    if(m_transformer) {
        result.setData(m_transformer(data(), transformation));
    }
    return result;
}

Image Image::fragment(int x, int y, int w, int h) const {
    Image result = *this;
    if(m_fragment) {
        result.setData(m_fragment(data(), x, y, w, h));
        result.m_width = w;
        result.m_height = h;
    }
    return result;
}

Image::ptr Image::bitmap() {
    return m_bitmap_getter(data());
}
