#include "variant.h"



namespace e172 {


std::ostream &operator<<(std::ostream &stream, const Variant &arg) {
    if(arg.single_print()) {
        stream << "single print";
        return stream;
    }

    auto s = arg.toString();
    if(s.size() > 0)
        stream << s;
    else
        stream << "unknown type { " << arg.type() << " }";

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
    }
    stream << "]";
    return stream;
}


Variant::Variant(const Variant &obj) {
    operator=(obj);
}


VariantVector Variant::constrained() {
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
    if(varian0.type() != varian1.type())
        return false;

    if(varian0.m_data == nullptr && varian1.m_data == nullptr)
        return true;

    if(varian0.m_data == nullptr || varian1.m_data == nullptr)
        return false;

    if(!varian0.m_comparator)
        return false;

    return varian0.m_comparator(varian0.m_data, varian1.m_data);
}

double Variant::toDouble(bool *ok) {
    if(ok)
        *ok = true;

    if(containsType<bool>()) {
        return value<bool>();
    } else if(containsType<char>()) {
        return value<char>();
    } else if(containsType<signed char>()) {
        return value<signed char>();
    } else if(containsType<unsigned char>()) {
        return value<unsigned char>();
    } else if(containsType<wchar_t>()) {
        return value<wchar_t>();
    } else if(containsType<char16_t>()) {
        return value<char16_t>();
    } else if(containsType<char32_t>()) {
        return value<char32_t>();
    } else if(containsType<short>()) {
        return value<short>();
    } else if(containsType<unsigned short>()) {
        return value<unsigned short>();
    } else if(containsType<unsigned int>()) {
        return value<unsigned int>();
    } else if(containsType<unsigned long>()) {
        return value<unsigned long>();
    } else if(containsType<long long>()) {
        return value<long long>();
    } else if(containsType<unsigned long long>()) {
        return value<unsigned long long>();
    } else if(containsType<float>()) {
        return value<float>();
    } else if(containsType<double>()) {
        return value<double>();
    } else if(containsType<long double>()) {
        return value<long double>();
    } else if(containsType<std::string>()) {
        try {
            return std::stod(value<std::string>());
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

VariantMap Variant::toMap() {
    if(containsType<VariantMap>()) {
        return value<VariantMap>();
    }
    return VariantMap();
}

bool Variant::isNumber() {
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
        return __str_is_number(value<std::string>());
    }
    return 0;
}

bool Variant::__str_is_number(const std::string &string) {
    std::string::const_iterator it = string.begin();
    while (it != string.end() && std::isdigit(*it)) ++it;
    return !string.empty() && it == string.end();
}



}
