#include "variant.h"



namespace e172 {


std::ostream &operator<<(std::ostream &stream, const Variant &arg) {    
    if(arg.m_stream_value) {
        stream << arg.m_stream_value(arg.m_data);
        return stream;
    }

    auto s = arg.toString();
    if(s.size() > 0)
        stream << s;
    else
        stream << "e172::Variant: Unknown type { " << arg.type() << " }";

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


Variant::Variant(const Variant &obj) {
    operator=(obj);
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

bool operator<(const Variant &varian0, const Variant &varian1) {
    if(varian0.type() == varian1.type()) {
        if(varian0.m_less_operator)
            return varian0.m_less_operator(varian0.m_data, varian1.m_data);

        return false;
    }

    return varian0.type() < varian1.type();
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
    if(m_string_convertor)
        return m_string_convertor(m_data);

    if(m_stream_value)
        return m_stream_value(m_data);

    return std::string();
}


ByteArray Variant::toJson() {
    return ByteArray();
}


Variant Variant::fromJson(const ByteArray &json) {
    (void)json;
    return Variant();
}


}

