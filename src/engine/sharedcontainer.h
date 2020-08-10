#ifndef SHAREDCONTAINER_H
#define SHAREDCONTAINER_H

#include <functional>

namespace e172 {



class SharedContainer {
public:
    typedef const void* ptr;
    struct base_handle { virtual ~base_handle(); };
    template<typename T> struct handle : public base_handle { T c; handle(const T &v) { c = v; } handle() {} };
    typedef const base_handle* data_ptr;
    template<typename T>
    static handle<T> *handle_cast(const base_handle *ptr) { return const_cast<handle<T>*>(dynamic_cast<const handle<T>*>(ptr)); }

    typedef handle<void*> void_handle;
protected:
    template<typename T>
    handle<T> *casted_handle() const { return handle_cast<T>(m_data); }
    ptr id() const;
    typedef std::function<void(data_ptr)> destructor_t;

    template<typename T>
    static T newSharedContainer(data_ptr data, ptr id, destructor_t destructor) {
        T i;
        i.ref_count_ptr = new int(1);
        i.m_data = data;
        i.m_id = id;
        i.m_destructor = destructor;
        return i;
    }
    data_ptr data() const;
    void setData(const data_ptr &data);
private:
    data_ptr m_data = nullptr;
    ptr m_id = nullptr;


    destructor_t m_destructor;

    int *ref_count_ptr = nullptr;

    void __detach();
public:
    SharedContainer();
    SharedContainer(const SharedContainer &obj);
    void operator=(const SharedContainer &obj);
    ~SharedContainer();

    bool isValid() const;
    bool isNull() const;
};

}


#endif // SharedContainer_H
