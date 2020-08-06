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

Image Image::newImage(ptr data, ptr id, int width, int height, destructor_t destructor, bitmap_getter_t bitmap_getter, nub_t nub, transformer_t transformer) {
    Image i;
    i.ref_count_ptr = new int(1);
    i.m_data = data;
    i.m_id = id;

    i.m_width = width;
    i.m_height = height;

    i.m_destructor = destructor;
    i.m_bitmap_getter = bitmap_getter;
    i.m_transformer = transformer;
    i.m_nub = nub;

    return i;
}

Image::Image() {}

void Image::__detach() {
    if(ref_count_ptr) {
        --(*ref_count_ptr);
        if(*ref_count_ptr <= 0) {
            if(!m_destructor && m_data) {
                throw std::runtime_error("[e172::Image]: destructor is not set\n");
                return;
            }

            m_destructor(m_data);
            delete ref_count_ptr;
        }
    } else if(m_data) {
        throw std::runtime_error("[e172::Image]: detaching null object\n");
    }
}

Image::Image(const Image &obj) {
    operator=(obj);
}

void Image::operator=(const Image &obj) {
    __detach();

    m_destructor = obj.m_destructor;
    m_data = obj.m_data;
    ref_count_ptr = obj.ref_count_ptr;
    m_id = obj.m_id;

    if(ref_count_ptr)
        ++(*ref_count_ptr);
}

Image::~Image() {
    __detach();
}

Image Image::transformed(uint64_t transformation) const {
    Image result = *this;
    if(m_transformer) {
        result.m_data = m_transformer(m_data, transformation);
    }
    return result;
}

Image Image::nub(int x, int y, int w, int h) const {
    Image result = *this;
    if(m_nub) {
        result.m_data = m_nub(m_data, x, y, w, h);
        result.m_width = w;
        result.m_height = h;
    }
    return result;
}

Image::ptr Image::bitmap() {
    return m_bitmap_getter(m_data);
}

bool Image::isValid() const {
    return m_data != nullptr;
}

bool Image::isNull() const {
    return m_data == nullptr;
}
