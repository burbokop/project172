#ifndef VARIANT_H
#define VARIANT_H

#define E172_DISABLE_VARIANT_ABSTRACT_CONSTRUCTOR
#define E172_USE_VARIANT_RTTI_OBJECT


#include <vector>
#include <ostream>
#include <functional>
#include <sstream>
#include <type_traits>
#include <list>
#include <map>
#include <cassert>

#include <src/engine/math/vector.h>

#include "type.h"

#include "sfinae.h"
#include "typedefs.h"

#define E172_VARIANT_NUM_CONVERTER(NAME, TYPE) \
    inline TYPE to ## NAME(bool *ok = nullptr) const { return toNumber<TYPE>(ok); }

namespace e172 {





struct VariantBaseHandle { virtual ~VariantBaseHandle() {}; };
template<typename T>
struct VariantHandle : public VariantBaseHandle { T value; };

class VariantRTTIObject {
    std::string m_typeName;
    size_t m_typeHash = 0;

    std::function<void(VariantBaseHandle*)> m_destructor;
    std::function<VariantBaseHandle*(VariantBaseHandle*)> m_copyConstructor;
    std::function<std::string(VariantBaseHandle*)> m_streamValue;
    std::function<std::string(VariantBaseHandle*)> m_stringConvertor;

    std::function<bool(VariantBaseHandle*, VariantBaseHandle*)> m_comparator;
    std::function<bool(VariantBaseHandle*, VariantBaseHandle*)> m_lessOperator;
public:
    inline void destruct(VariantBaseHandle* h) { if(m_destructor) m_destructor(h); }
    inline VariantBaseHandle* copy(VariantBaseHandle* h) {
        if(m_copyConstructor)
            return m_copyConstructor(h);
        return nullptr;
    }
    inline std::string streamValue(VariantBaseHandle* h) { if(m_streamValue) return m_streamValue(h); return ""; }
    inline std::string toString(VariantBaseHandle* h) { if(m_stringConvertor) return m_stringConvertor(h); return ""; }
    inline bool compare(VariantBaseHandle* h0, VariantBaseHandle* h1) {
        if(m_comparator)
            return m_comparator(h0, h1);
        return false;
    }
    inline bool less(VariantBaseHandle* h0, VariantBaseHandle* h1) {
        if(m_lessOperator)
            return m_lessOperator(h0, h1);
        return false;
    }
    inline auto typeName() const { return m_typeName; }
    inline auto typeHash() const { return m_typeHash; }

    template<typename T>
    VariantRTTIObject(T&&) {
        m_destructor = [](VariantBaseHandle* obj) {
            delete dynamic_cast<VariantHandle<T>*>(obj);
        };
        m_copyConstructor = [](VariantBaseHandle* obj) {
            const auto casted_obj = dynamic_cast<VariantHandle<T>*>(obj);
            return new VariantHandle<T>(*casted_obj);
        };

        // additional operators
        if constexpr(sfinae::StreamOperator::exists<std::ostream, T>::value) {
            m_streamValue = [](VariantBaseHandle* obj) {
                VariantHandle<T>* casted_obj = dynamic_cast<VariantHandle<T>*>(obj);
                std::stringstream ss;
                    ss << casted_obj->value;
                return ss.str();
            };
        }

        if constexpr(std::is_same<T, std::string>::value || sfinae::TypeConvertionOperator<T, std::string>::value) {
            m_stringConvertor = [](VariantBaseHandle* obj) {
                return dynamic_cast<VariantHandle<T>*>(obj)->value;
            };
        } else if constexpr(std::is_integral<T>::value || std::is_same<T, double>::value || std::is_same<T, long double>::value || std::is_same<T, float>::value) {
            m_stringConvertor = [](VariantBaseHandle* obj) {
                return std::to_string(dynamic_cast<VariantHandle<T>*>(obj)->value);
            };
        }

        if constexpr(sfinae::EquealOperator::exists<T>::value) {
            m_comparator = [](VariantBaseHandle* obj1, VariantBaseHandle* obj2) -> bool {
                return dynamic_cast<VariantHandle<T>*>(obj1)->value
                        == dynamic_cast<VariantHandle<T>*>(obj2)->value;
            };
        } else {
            m_comparator = nullptr;
        }

        if constexpr(sfinae::LessOperator::exists<T>::value) {
            m_lessOperator = [](VariantBaseHandle* obj1, VariantBaseHandle* obj2){
                return dynamic_cast<VariantHandle<T>*>(obj1)->value
                < dynamic_cast<VariantHandle<T>*>(obj2)->value;
            };
        }

        m_typeName = Type<T>::name;
        m_typeHash = Type<T>::hash;
    }
};

class Variant;

template <typename T>
class VariantRTTITable {
    friend Variant;
    static inline VariantRTTIObject *object = nullptr;
};



typedef std::vector<Variant> VariantVector;
typedef std::list<Variant> VariantList;
typedef std::map<std::string, Variant> VariantMap;

std::ostream &operator<<(std::ostream &stream, const VariantVector &vector);
std::ostream &operator<<(std::ostream &stream, const VariantList &vector);

class Variant {
    friend std::ostream &operator<<(std::ostream &stream, const Variant &arg);
    VariantBaseHandle *m_data = nullptr;

#ifdef E172_USE_VARIANT_RTTI_OBJECT
    VariantRTTIObject *m_rttiObject = nullptr;
#else
    std::string m_typeName;
    size_t m_typeHash = 0;

    std::function<void(VariantBaseHandle*)> m_destructor;
    std::function<VariantBaseHandle*(VariantBaseHandle*)> m_copy_constructor;
    std::function<std::string(VariantBaseHandle*)> m_stream_value;
    std::function<std::string(VariantBaseHandle*)> m_string_convertor;

    std::function<bool(VariantBaseHandle*, VariantBaseHandle*)> m_comparator;
    std::function<bool(VariantBaseHandle*, VariantBaseHandle*)> m_less_operator;
#endif


    template<typename T>
    T value_fast() const { return dynamic_cast<VariantHandle<T>*>(m_data)->value; }

public:

    // Variant base functional
    Variant() {};

#ifndef E172_DISABLE_VARIANT_ABSTRACT_CONSTRUCTOR
    template<typename T>
    Variant(T value) { assign(value); }
#endif

    inline Variant(const Variant &obj) { operator=(obj); }

    template<typename T>
    void operator=(const T& value) { assign(value); }

    void operator=(const Variant &obj) {
#ifdef E172_USE_VARIANT_RTTI_OBJECT
        m_rttiObject = obj.m_rttiObject;
        if(obj.m_data && obj.m_rttiObject)
            m_data = obj.m_rttiObject->copy(obj.m_data);
#else
        m_typeName = obj.m_typeName;
        m_typeHash = obj.m_typeHash;
        m_destructor = obj.m_destructor;
        m_copy_constructor = obj.m_copy_constructor;
        m_stream_value = obj.m_stream_value;
        m_comparator = obj.m_comparator;
        m_less_operator = obj.m_less_operator;
        m_string_convertor = obj.m_string_convertor;
        if(obj.m_data && obj.m_copy_constructor)
            m_data = obj.m_copy_constructor(obj.m_data);
#endif
    }

    inline ~Variant() {
#ifdef E172_USE_VARIANT_RTTI_OBJECT
        if(m_data && m_rttiObject) { m_rttiObject->destruct(m_data); }
#else
        if(m_data && m_destructor) { m_destructor(m_data); }
#endif
    }

    template<typename T>
    T value() const {
        if(!containsType<T>()) {
            throw std::runtime_error("Variant does not contain type: " + Type<T>::name);
        }
        if(m_data)
            return dynamic_cast<VariantHandle<T>*>(m_data)->value;
        return T();
    }

    template<typename T>
    T value_default() const {
        if(containsType<T>()) {
            return dynamic_cast<VariantHandle<T>*>(m_data)->value;
        }
        return T();
    }

#ifdef E172_USE_VARIANT_RTTI_OBJECT
    template<typename T>
    void assign(const T& value) {
        if(!VariantRTTITable<T>::object) {
            VariantRTTITable<T>::object = new VariantRTTIObject(T());
        }

        if(m_rttiObject != VariantRTTITable<T>::object) {
            if(m_data)
                m_rttiObject->destruct(m_data);

            m_data = new VariantHandle<T>();
        }
        dynamic_cast<VariantHandle<T>*>(m_data)->value = value;
    }
#else
    template<typename T>
    void assign(const T& value) {
        auto hash = Type<T>::hash;
        if(hash != m_typeHash) {

            if(m_data)
                m_destructor(m_data);

            // main operators
            m_data = new VariantHandle<T>();
            m_destructor = [](VariantBaseHandle* obj){
                delete dynamic_cast<VariantHandle<T>*>(obj);
            };
            m_copy_constructor = [](VariantBaseHandle* obj) {
                const auto casted_obj = dynamic_cast<VariantHandle<T>*>(obj);
                return new VariantHandle<T>(*casted_obj);
            };

            // additional operators
            if constexpr(sfinae::StreamOperator::exists<std::ostream, T>::value) {
                m_stream_value = [](VariantBaseHandle* obj) {
                    VariantHandle<T>* casted_obj = dynamic_cast<VariantHandle<T>*>(obj);
                    std::stringstream ss;
                        ss << casted_obj->value;
                    return ss.str();
                };
            } else {
                m_stream_value = nullptr;
            }

            if constexpr(std::is_same<T, std::string>::value || sfinae::TypeConvertionOperator<T, std::string>::value) {
                m_string_convertor = [](VariantBaseHandle* obj) {
                    return dynamic_cast<VariantHandle<T>*>(obj)->value;
                };
            } else if constexpr(std::is_integral<T>::value) {
                m_string_convertor = [](VariantBaseHandle* obj) {
                    return std::to_string(dynamic_cast<VariantHandle<T>*>(obj)->value);
                };
            } else {
                m_string_convertor = nullptr;
            }

            if constexpr(sfinae::EquealOperator::exists<T>::value) {
                m_comparator = [](VariantBaseHandle* obj1, VariantBaseHandle* obj2) -> bool {
                    return dynamic_cast<VariantHandle<T>*>(obj1)->value
                            == dynamic_cast<VariantHandle<T>*>(obj2)->value;
                };
            } else {
                m_comparator = nullptr;
            }

            if constexpr(sfinae::LessOperator::exists<T>::value) {
                m_less_operator = [](VariantBaseHandle* obj1, VariantBaseHandle* obj2){
                    return dynamic_cast<VariantHandle<T>*>(obj1)->value
                    < dynamic_cast<VariantHandle<T>*>(obj2)->value;
                };
            } else {
                m_less_operator = nullptr;
            }

            m_typeName = Type<T>::name;
            m_typeHash = hash;
        }

        dynamic_cast<VariantHandle<T>*>(m_data)->value = value;
    }
#endif


#ifdef E172_USE_VARIANT_RTTI_OBJECT
    std::string typeName() const { return m_rttiObject ? m_rttiObject->typeName() : ""; }
    template<typename T>
    bool containsType() const { return m_rttiObject == VariantRTTITable<T>::object; }
#else
    std::string typeName() const { return m_typeName; }
    template<typename T>
    bool containsType() const { return m_typeHash == Type<T>::hash; }
#endif
    friend bool operator==(const Variant &varian0, const Variant &varian1);
    friend bool operator<(const Variant &varian0, const Variant &varian1);

    template<typename T>
    static Variant fromValue(const T &value) { Variant v; v.assign(value); return v; }


    // Static tools

    static bool containsNumber(const std::string& string);


    // User interface methods
    Variant(const std::string &value) { assign(value); }
    Variant(const char *value) : Variant(std::string(value)) {}
    Variant(const VariantMap &value) { assign(value); }
    Variant(const VariantList &value) { assign(value); }
    Variant(const VariantVector &value) { assign(value); }
    Variant(const Vector &value) { assign(value); }

    Variant(double value) { assign(value); }

    Variant(uint8_t value) { assign(value); }
    Variant(uint16_t value) { assign(value); }
    Variant(uint32_t value) { assign(value); }
    Variant(uint64_t value) { assign(value); }

    Variant(int8_t value) { assign(value); }
    Variant(int16_t value) { assign(value); }
    Variant(int32_t value) { assign(value); }
    Variant(int64_t value) { assign(value); }


    VariantVector constrained() const;

    bool isNumber() const;

#ifdef E172_USE_VARIANT_RTTI_OBJECT
    inline bool isNull() const { return m_rttiObject; }
#else
    inline bool isNull() const { return m_typeName.size() <= 0; }
#endif

    template<typename T>
    T toNumber(bool *ok = nullptr) const;

    E172_VARIANT_NUM_CONVERTER(Double, double)
    E172_VARIANT_NUM_CONVERTER(Float, float)
    E172_VARIANT_NUM_CONVERTER(Int, int)
    E172_VARIANT_NUM_CONVERTER(UInt, unsigned int)
    E172_VARIANT_NUM_CONVERTER(Char, char)
    E172_VARIANT_NUM_CONVERTER(Bool, bool)

    E172_VARIANT_NUM_CONVERTER(UInt8, uint8_t)
    E172_VARIANT_NUM_CONVERTER(UInt16, uint16_t)
    E172_VARIANT_NUM_CONVERTER(UInt32, uint32_t)
    E172_VARIANT_NUM_CONVERTER(UInt64, uint64_t)

    E172_VARIANT_NUM_CONVERTER(Int8, int8_t)
    E172_VARIANT_NUM_CONVERTER(Int16, int16_t)
    E172_VARIANT_NUM_CONVERTER(Int32, int32_t)
    E172_VARIANT_NUM_CONVERTER(Int64, int64_t)

    inline auto toMap() const { return value_default<VariantMap>(); };
    inline auto toList() const { return value_default<VariantList>(); };
    inline auto toVector() const { return value_default<VariantVector>();};
    inline auto toMathVector() const { return value_default<Vector>();};

    std::string toString() const;


    [[deprecated("Will be added in future")]]
    ByteArray toJson() const;
    [[deprecated("Will be added in future")]]
    static Variant fromJson(const ByteArray &json);



    static std::pair<int64_t, int64_t> testSpeed(size_t count);
    static int64_t testSpeed();
};




template<typename T>
T Variant::toNumber(bool *ok) const {
    if(ok)
        *ok = true;

    if(containsType<bool>()) { return value_fast<bool>();
    } else if(containsType<int                >()) { return value_fast<int>();
    } else if(containsType<unsigned int       >()) { return value_fast<unsigned int>();
    } else if(containsType<long               >()) { return value_fast<long>();
    } else if(containsType<unsigned long      >()) { return value_fast<unsigned long>();
    } else if(containsType<long long          >()) { return value_fast<long long>();
    } else if(containsType<float              >()) { return value_fast<float>();
    } else if(containsType<double             >()) { return value_fast<double>();
    } else if(containsType<long double        >()) { return value_fast<long double>();
    } else if(containsType<char               >()) { return value_fast<char>();
    } else if(containsType<signed char        >()) { return value_fast<signed char>();
    } else if(containsType<unsigned char      >()) { return value_fast<unsigned char>();
    } else if(containsType<wchar_t            >()) { return value_fast<wchar_t>();
    } else if(containsType<char16_t           >()) { return value_fast<char16_t>();
    } else if(containsType<char32_t           >()) { return value_fast<char32_t>();
    } else if(containsType<short              >()) { return value_fast<short>();
    } else if(containsType<unsigned short     >()) { return value_fast<unsigned short>();
    } else if(containsType<unsigned long long >()) { return value_fast<unsigned long long>();
    } else if(containsType<std::string        >()) {
        try {
            return std::stod(value_fast<std::string>());
        } catch (std::invalid_argument) {
            if(ok)
                *ok = false;
            return 0;
        }
    }

    if(ok)
        *ok = false;
    return 0;
}








}

#endif // VARIANT_H
