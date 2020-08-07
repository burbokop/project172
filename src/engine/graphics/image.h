#ifndef IMAGE_H
#define IMAGE_H


#include <functional>

namespace e172 {
class Image {
    friend class AbstractGraphicsProvider;
    friend class AbstractRenderer;
public:
    typedef const void* ptr;
    struct base_handle { virtual ~base_handle() {} };
    template<typename T> struct handle : public base_handle { T c; handle(const T &v) { c = v; } };
    template<typename T>
    static handle<T> *handle_cast(const base_handle *ptr) { return const_cast<handle<T>*>(dynamic_cast<const handle<T>*>(ptr)); }
    typedef const base_handle* data_ptr;
private:
    data_ptr m_data = nullptr;
    ptr m_id = nullptr;
    int m_width;
    int m_height;

    int m_copyNumber = 0;

    typedef std::function<data_ptr(data_ptr, int, int, int&, int&)> fragment_t;
    typedef std::function<void(data_ptr)> destructor_t;
    typedef std::function<data_ptr(data_ptr, uint64_t)> transformer_t;
    typedef std::function<ptr(data_ptr)> bitmap_getter_t;

    destructor_t m_destructor;
    transformer_t m_transformer;
    fragment_t m_fragment;
    bitmap_getter_t m_bitmap_getter;

    int *ref_count_ptr = nullptr;
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
    Image(const Image &obj);
    void operator=(const Image &obj);
    ~Image();

    Image transformed(uint64_t transformation) const;

    Image fragment(int x, int y, int w, int h) const;

    ptr bitmap();

    bool isValid() const;
    bool isNull() const;
    int width() const;
    int height() const;
};


}


#endif // IMAGE_H
