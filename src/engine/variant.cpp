#include "additional.h"
#include "variant.h"

#include <src/engine/time/elapsedtimer.h>


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

std::ostream &operator<<(std::ostream &stream, const VariantVector &vector) {
    stream << "[";
    VariantVector::size_type i = 0;
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

std::ostream &operator<<(std::ostream &stream, const VariantList &list) {
    stream << "[";
    VariantList::size_type i = 0;
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

std::ostream &operator<<(std::ostream &stream, const VariantMap &map) {
    stream << "{";
    VariantList::size_type i = 0;
    for(auto v : map) {
        stream << v.first << ": " << v.second;
        if(i < map.size() - 1) {
            stream << ", ";
        }
        ++i;
    }
    stream << "}";
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

bool Variant::isString() const {
    return containsType<std::string>();
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

Variant Variant::fromString(const std::string &string) {
    try {
        return std::stod(string);
    } catch (std::invalid_argument) {
        try {
            return std::stoi(string);
        } catch (std::invalid_argument) {
            return string;
        }
    }
}

VariantMap Variant::fromString(const std::map<std::string, std::string> &map) {
    VariantMap result;
    for(auto m : map) {
        result[m.first] = m.second;
    }
    return result;
}

std::string Variant::toJson() const {
    std::string result;
    if(containsType<VariantMap>()) {
        result += "{";
        const auto c = value_fast<VariantMap>();
        size_t i = 0;
        for(auto cc : c) {
            result += "\"" + cc.first + "\" : " + cc.second.toJson();
            if(i < c.size() - 1) {
                result += ", ";
            }
            ++i;
        }
        result += "}";
        return result;
    } else if(containsType<VariantList>()) {
        return containerToJson(value_fast<VariantList>());
    } else if(containsType<VariantVector>()) {
        return containerToJson(value_fast<VariantVector>());
    } else if(isNumber()) {
        return std::to_string(toDouble());
    } else {
        return "\"" + toString() + "\"";
    }
}

Variant Variant::fromJson(const std::string &json) {
    const auto trimed = Additional::removeSymbols(json, { ' ', '\n', '\t', '\r' });
    if(trimed.size() > 0) {
        if(trimed.front() == '{' && trimed.back() == '}') {
            VariantMap map;
            const auto ss = Additional::jsonTopLevelFields(trimed.substr(1, trimed.size() - 2));
            for(const auto& s : ss) {
                const auto record = Additional::splitIntoPair(s, ':');
                if(record.first.size() > 1 && record.second.size() > 0) {
                    if(record.first.front() == '\"' && record.first.back() == '\"') {
                        map[record.first.substr(1, record.first.size() - 2)] = fromJson(record.second);
                    }
                }
            }
            return map;
        } else if(trimed.front() == '[' && trimed.back() == ']') {
            VariantList list;
            const auto ss = Additional::jsonTopLevelFields(trimed.substr(1, trimed.size() - 2));
            for(const auto& s : ss) {
                list.push_back(fromJson(s));
            }
            return list;
        } else if(trimed.size() > 1 && trimed.front() == '\"' && trimed.back() == '\"') {
            return trimed.substr(1, trimed.size() - 2);
        } else {
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



