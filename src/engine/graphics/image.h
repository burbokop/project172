#ifndef IMAGE_H
#define IMAGE_H


#include <functional>

#include <engine/sharedcontainer.h>

namespace e172 {
class Image : public SharedContainer {
    friend class AbstractGraphicsProvider;
    friend class AbstractRenderer;
private:
    int m_width;
    int m_height;

    typedef std::function<data_ptr(data_ptr, int, int, int&, int&)> fragment_t;
    typedef std::function<data_ptr(data_ptr, uint64_t)> transformer_t;
    typedef std::function<ptr(data_ptr)> bitmap_getter_t;

    transformer_t m_transformer;
    fragment_t m_fragment;
    bitmap_getter_t m_bitmap_getter;

    static Image newImage(data_ptr data,
            ptr id,
            int width,
            int height,
            destructor_t destructor,
            bitmap_getter_t bitmap_getter,
            fragment_t fragment = fragment_t(),
            transformer_t transformer = transformer_t()
            );

    void __detach();
public:
    Image();
    Image transformed(uint64_t transformation) const;
    Image fragment(int x, int y, int w, int h) const;

    ptr bitmap();

    int width() const;
    int height() const;
};


}


#endif // IMAGE_H
