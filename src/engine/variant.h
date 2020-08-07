#ifndef VARIANT_H
#define VARIANT_H

#define E172_DISABLE_VARIANT_ABSTRACT_CONSTRUCTOR

#include <vector>
#include <ostream>
#include <functional>
#include <sstream>
#include <type_traits>
#include <list>
#include <map>
#include <cassert>

#include "type.h"


namespace e172 {


namespace kgram_stream_operator__ {
    struct no { bool b[2]; };
    template<typename T, typename Arg> no operator<< (T&, const Arg&);

    bool check (...);
    no& check (const no&);

    template <typename T, typename Arg = T>
    struct exists {
        enum { value = (sizeof(check(*(T*)(0) << *(Arg*)(0))) != sizeof(no)) };
    };
}

struct kgram_variant_handle_base_t { virtual ~kgram_variant_handle_base_t() {}; };
template<typename T>
struct kgram_variant_handle_t : kgram_variant_handle_base_t { T value; };

class Variant;
std::ostream &operator<<(std::ostream &stream, const Variant &arg);
typedef std::vector<Variant> VariantVector;
typedef std::list<Variant> VariantList;
typedef std::map<std::string, Variant> VariantMap;

class Variant {
    kgram_variant_handle_base_t *m_data = nullptr;
    std::string m_type;

    std::function<void(kgram_variant_handle_base_t*)> m_destructor;
    std::function<kgram_variant_handle_base_t*(kgram_variant_handle_base_t*)> m_copy_constructor;
    std::function<std::string(kgram_variant_handle_base_t*)> m_to_string;

    std::function<bool(kgram_variant_handle_base_t*, kgram_variant_handle_base_t*)> m_comparator;

    bool m_single_print = false;
public:
    Variant() {};

#ifndef E172_DISABLE_VARIANT_ABSTRACT_CONSTRUCTOR
    template<typename T>
    Variant(T value) { assign(value); }
#endif

    template<typename T>
    static Variant fromValue(const T &value) { Variant v; v.assign(value); return v; }

    Variant(const std::string &value) { assign(value); }
    Variant(const int &value) { assign(value); }
    Variant(const unsigned int &value) { assign(value); }
    Variant(const double &value) { assign(value); }
    Variant(const char *value) : Variant(std::string(value)) {}
    Variant(const VariantMap &value) { assign(value); }
    Variant(const VariantList &value) { assign(value); }
    Variant(const VariantVector &value) { assign(value); }

    Variant(const Variant &obj);
    template<typename T>
    void operator=(T value) { assign(value); }
    void operator=(const Variant &obj) {
        m_type = obj.m_type;
        m_destructor = obj.m_destructor;
        m_copy_constructor = obj.m_copy_constructor;
        m_to_string = obj.m_to_string;
        m_comparator = obj.m_comparator;
        if(obj.m_data && obj.m_copy_constructor)
            m_data = obj.m_copy_constructor(obj.m_data);
    }

    ~Variant() { if(m_data && m_destructor) { m_destructor(m_data); } }

    template<typename T>
    T value() const {
        if(!containsType<T>()) {
            throw std::runtime_error("Variant does not contain type: " + Type<T>::name);
        }
        if(m_data)
            return dynamic_cast<kgram_variant_handle_t<T>*>(m_data)->value;
        return T();
    }

    std::string toString() const { if(m_data && m_to_string) return m_to_string(m_data); return std::string(); }
    bool single_print() const { return m_single_print; };

    VariantVector constrained();
    bool isNumber();
    static bool __str_is_number(const std::string& string);
    double toDouble(bool *ok = nullptr);

    VariantMap toMap();

    template<typename T>
    void assign(T value) {
        auto t = Type<T>::name;
        if(t != m_type) {

            if(m_data)
                m_destructor(m_data);

            m_data = new kgram_variant_handle_t<T>();
            m_destructor = [](kgram_variant_handle_base_t* obj){
                kgram_variant_handle_t<T>* casted_obj = dynamic_cast<kgram_variant_handle_t<T>*>(obj);
                delete casted_obj;
            };
            m_copy_constructor = [](kgram_variant_handle_base_t* obj) {
                kgram_variant_handle_t<T>* casted_obj = dynamic_cast<kgram_variant_handle_t<T>*>(obj);
                return new kgram_variant_handle_t<T>(*casted_obj);
            };

            m_comparator = [](kgram_variant_handle_base_t* obj1, kgram_variant_handle_base_t* obj2) -> bool {
                return dynamic_cast<kgram_variant_handle_t<T>*>(obj1)->value
                == dynamic_cast<kgram_variant_handle_t<T>*>(obj2)->value;
            };

            if constexpr(kgram_stream_operator__::exists<std::ostream, T>::value) {
                m_to_string = [](kgram_variant_handle_base_t* obj) {
                    kgram_variant_handle_t<T>* casted_obj = dynamic_cast<kgram_variant_handle_t<T>*>(obj);
                    std::stringstream ss;
                        ss << casted_obj->value;
                    return ss.str();
                };
            }


            m_type = t;
        }

        dynamic_cast<kgram_variant_handle_t<T>*>(m_data)->value = value;
    }
    std::string type() const { return m_type; }
    template<typename T>
    bool containsType() const { return m_type == Type<T>::name; }

    friend bool operator==(const Variant &varian0, const Variant &varian1);
};








std::ostream &operator<<(std::ostream &stream, const std::vector<Variant> &vector);
std::ostream &operator<<(std::ostream &stream, const std::list<Variant> &vector);




}

#endif // VARIANT_H
