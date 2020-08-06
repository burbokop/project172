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

kgram_variant_vector kgram_variant_constrain(const Variant &variant) {
    kgram_variant_vector result;
    if(variant.containsType<kgram_variant_vector>()) {
        const auto vec = variant.value<kgram_variant_vector>();
        for(auto v : vec) {
            auto c = kgram_variant_constrain(v);
            for(auto item : c) {
                result.push_back(item);
            }
        }
    } else if(variant.containsType<Variant>()) {
        return { variant.value<Variant>() };
    } else {
        return { variant };
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

double kgram_to_double(const Variant &variant, bool *ok) {
    if(ok)
        *ok = true;

    if(variant.containsType<bool>()) {
        return variant.value<bool>();
    } else if(variant.containsType<char>()) {
        return variant.value<char>();
    } else if(variant.containsType<signed char>()) {
        return variant.value<signed char>();
    } else if(variant.containsType<unsigned char>()) {
        return variant.value<unsigned char>();
    } else if(variant.containsType<wchar_t>()) {
        return variant.value<wchar_t>();
    } else if(variant.containsType<char16_t>()) {
        return variant.value<char16_t>();
    } else if(variant.containsType<char32_t>()) {
        return variant.value<char32_t>();
    } else if(variant.containsType<short>()) {
        return variant.value<short>();
    } else if(variant.containsType<unsigned short>()) {
        return variant.value<unsigned short>();
    } else if(variant.containsType<unsigned int>()) {
        return variant.value<unsigned int>();
    } else if(variant.containsType<unsigned long>()) {
        return variant.value<unsigned long>();
    } else if(variant.containsType<long long>()) {
        return variant.value<long long>();
    } else if(variant.containsType<unsigned long long>()) {
        return variant.value<unsigned long long>();
    } else if(variant.containsType<float>()) {
        return variant.value<float>();
    } else if(variant.containsType<double>()) {
        return variant.value<double>();
    } else if(variant.containsType<long double>()) {
        return variant.value<long double>();
    } else if(variant.containsType<std::string>()) {
        try {
            return std::stod(variant.value<std::string>());
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

bool kgram_is_number(const Variant &variant) {
    if(variant.containsType<bool>()
    || variant.containsType<char>()
    || variant.containsType<signed char>()
    || variant.containsType<unsigned char>()
    || variant.containsType<wchar_t>()
    || variant.containsType<char16_t>()
    || variant.containsType<char32_t>()
    || variant.containsType<short>()
    || variant.containsType<unsigned short>()
    || variant.containsType<unsigned int>()
    || variant.containsType<unsigned long>()
    || variant.containsType<long long>()
    || variant.containsType<unsigned long long>()
    || variant.containsType<float>()
    || variant.containsType<double>()
    || variant.containsType<long double>()) {
        return true;
    } else if(variant.containsType<std::string>()) {
        return kgram_is_number(variant.value<std::string>());
    }
    return 0;
}

bool kgram_is_number(const std::string &string) {
    std::string::const_iterator it = string.begin();
    while (it != string.end() && std::isdigit(*it)) ++it;
    return !string.empty() && it == string.end();
}

}
