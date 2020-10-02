#include "additional.h"
#include "variant.h"

#include <src/engine/time/elapsedtimer.h>

#include <iostream>

namespace e172 {


std::ostream &operator<<(std::ostream &stream, const Variant &arg) {
#ifdef E172_USE_VARIANT_RTTI_OBJECT
    if(arg.m_rttiObject) {
        stream << arg.m_rttiObject->streamValue(arg.m_data);
        return stream;
    }
#else
    if(arg.m_stream_value) {
        stream << arg.m_stream_value(arg.m_data);
        return stream;
    }
#endif
    auto s = arg.toString();
    if(s.size() > 0)
        stream << s;
    else
        stream << "e172::Variant: Unknown type { " << arg.typeName() << " }";

    return stream;
}

std::ostream &operator<<(std::ostream &stream, const std::vector<Variant> &vector) {
    stream << "[";
    std::vector<Variant>::size_type i = 0;
    for(auto v : vector) {
        stream << v;
        if(i < vector.size() - 1) {
            stream << ", ";
        }
        ++i;
    }
    stream << "]";
    return stream;
}

std::ostream &operator<<(std::ostream &stream, const std::list<Variant> &list) {
    stream << "[";
    std::vector<Variant>::size_type i = 0;
    for(auto v : list) {
        stream << v;
        if(i < list.size() - 1) {
            stream << ", ";
        }
        ++i;
    }
    stream << "]";
    return stream;
}


VariantVector Variant::constrained() const {
    VariantVector result;
    if(containsType<VariantVector>()) {
        const auto vec = value<VariantVector>();
        for(auto v : vec) {
            auto c = v.constrained();
            for(auto item : c) {
                result.push_back(item);
            }
        }
    } else if(containsType<Variant>()) {
        return { value<Variant>() };
    } else {
        return { *this };
    }
    return result;
}

bool operator==(const Variant &varian0, const Variant &varian1) {
#ifdef E172_USE_VARIANT_RTTI_OBJECT
    if(varian0.m_rttiObject != varian1.m_rttiObject)
        return false;

    if(varian0.m_data == nullptr && varian1.m_data == nullptr)
        return true;

    if(varian0.m_data == nullptr || varian1.m_data == nullptr)
        return false;

    if(!varian0.m_rttiObject)
        return false;

    return varian0.m_rttiObject->compare(varian0.m_data, varian1.m_data);
#else
    if(varian0.m_typeHash != varian1.m_typeHash)
        return false;

    if(varian0.m_data == nullptr && varian1.m_data == nullptr)
        return true;

    if(varian0.m_data == nullptr || varian1.m_data == nullptr)
        return false;

    if(!varian0.m_comparator)
        return false;

    return varian0.m_comparator(varian0.m_data, varian1.m_data);
#endif
}

bool operator<(const Variant &varian0, const Variant &varian1) {
#ifdef E172_USE_VARIANT_RTTI_OBJECT
    if(varian0.m_rttiObject == varian1.m_rttiObject)
        return varian0.m_rttiObject->less(varian0.m_data, varian1.m_data);

    return varian0.m_rttiObject < varian1.m_rttiObject;
#else
    if(varian0.m_typeHash == varian1.m_typeHash) {
        if(varian0.m_less_operator)
            return varian0.m_less_operator(varian0.m_data, varian1.m_data);

        return false;
    }

    return varian0.m_typeHash < varian1.m_typeHash;
#endif
}

bool Variant::containsNumber(const std::string &string) {
    std::string::const_iterator it = string.begin();
    while (it != string.end() && std::isdigit(*it)) ++it;
    return !string.empty() && it == string.end();
}



bool Variant::isNumber() const {
    if(containsType<bool>()
    || containsType<char>()
    || containsType<signed char>()
    || containsType<unsigned char>()
    || containsType<wchar_t>()
    || containsType<char16_t>()
    || containsType<char32_t>()
    || containsType<short>()
    || containsType<unsigned short>()
    || containsType<unsigned int>()
    || containsType<unsigned long>()
    || containsType<long long>()
    || containsType<unsigned long long>()
    || containsType<float>()
    || containsType<double>()
    || containsType<long double>()) {
        return true;
    } else if(containsType<std::string>()) {
        return containsNumber(value<std::string>());
    }
    return 0;
}

std::string Variant::toString() const {
    if(containsType<std::string>())
        return value_fast<std::string>();
#ifdef E172_USE_VARIANT_RTTI_OBJECT
    if(m_rttiObject)
        return m_rttiObject->toString(m_data);
#else
    if(m_string_convertor)
        return m_string_convertor(m_data);
#endif
    return std::string();
}


std::string Variant::toJson() const {

}

Variant Variant::fromJson(const std::string &json) {
    std::string trimed = Additional::removeSymbols(json, { ' ', '\n', '\t' });
    std::cout << "call: " << trimed << "\n";

    if(trimed.size() > 0) {
        std::cout << "json: " << trimed.front() << " : " << trimed.back() << "\n";
        if(trimed.front() == '{' && trimed.back() == '}') {
            std::cout << "obj : " << trimed << "\n";
            VariantMap map;
            const auto ss = Additional::split(trimed.substr(1, trimed.size() - 2), ',');
            for(const auto& s : ss) {
                const auto recored = Additional::split(s, ':');
                if(recored.size() > 1) {
                    if(recored[1].size() > 0) {
                        if(recored[1][0] == '{') {
                            map[recored[0]] = fromJson(Additional::fencedArea(s, Additional::CurlyBraces));
                        } else if(recored[1][0] == '[') {
                            map[recored[0]] = fromJson(Additional::fencedArea(s, Additional::Brackets));
                        } else {
                            map[recored[0]] = fromJson(recored[1]);
                        }
                    }
                }
            }
            std::cout << "obj result: " << map << "\n";
            return map;
        } else if(trimed.front() == '[' && trimed.back() == ']') {
            std::cout << "list: " << trimed << "\n";
            VariantList list;
            const auto ss = Additional::split(trimed.substr(1, trimed.size() - 2), ',');
            for(const auto& s : ss) {
                list.push_back(fromJson(s));
            }
            std::cout << "list result: " << list << "\n";
            return list;
        } else {
            std::cout << "else: " << trimed << "\n";
            try {
                return std::stod(trimed);
            } catch (std::invalid_argument) {
                return trimed;
            }
        }
    }
    return Variant();
}







int e172_Variant_ts_d;

void e172_Variant_ts_foo(const e172::Variant &value) {
    e172_Variant_ts_d = value.toInt();
}

void e172_Variant_ts_bar(int value) {
    e172_Variant_ts_d = value;
}

std::pair<int64_t, int64_t> e172::Variant::testSpeed(size_t count) {
    e172::ElapsedTimer t;
    for(size_t i = 0; i < count; ++i) {
        e172_Variant_ts_foo(i);
    }
    const auto t0 = t.elapsed();
    t.reset();
    for(size_t i = 0; i < count; ++i) {
        e172_Variant_ts_bar(i);
    }
    const auto t1 = t.elapsed();
    return { t0, t1 };
}


int64_t e172::Variant::testSpeed() {
    size_t c = 1;
    while (true) {
        const auto result = testSpeed(c *= 2);
        if(result.first != 0 && result.second != 0) {
            return result.first / result.second;
        }
    }
}

}


