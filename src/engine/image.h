#ifndef IMAGE_H
#define IMAGE_H


#include <functional>

namespace e172 {
class Image {
    friend class AbstractGraphicsProvider;
    friend class AbstractRenderer;
public:
    typedef const void* ptr;
private:
    ptr m_data = nullptr;
    ptr m_id = nullptr;
    int m_width;
    int m_height;

    std::function<void(ptr)> m_destructor;
    std::function<ptr(ptr, uint64_t)> m_transformer;


    typedef std::function<ptr(ptr, int, int, int&, int&)> nub_t;
    typedef std::function<void(ptr)> destructor_t;
    typedef std::function<ptr(ptr, uint64_t)> transformer_t;
    nub_t m_nub;

    int *ref_count_ptr = nullptr;
    static Image newImage(ptr data,
            ptr id,
            int width,
            int height,
            destructor_t destructor,
            nub_t nub = nub_t(),
            transformer_t transformer = transformer_t()
            );

    void __detach();
public:
    Image();
    Image(const Image &obj);
    void operator=(const Image &obj);
    ~Image();

    Image transformed(uint64_t transformation) const;

    Image nub(int x, int y, int w, int h) const;

    bool isValid() const;
    bool isNull() const;
    int width() const;
    int height() const;
};


}


#endif // IMAGE_H
