#include "stringformer.h"

namespace proj172::core {

std::string StringFormer::line(unsigned number) {
    return line(number, '-');
}

std::string StringFormer::line(unsigned number, char simbol) {
    std::string result = "";
    for(unsigned i = 0; i < number; i++) {
        result += simbol;
    };
    return result;
}

std::string StringFormer::line(unsigned number, unsigned max) {
    return number < max ? line(number) : line(max);
}

std::string StringFormer::line(unsigned number, char simbol, unsigned max) {
    return number < max ? line(number, simbol) : line(max, simbol);
}

std::string StringFormer::bar(unsigned number) {
    switch (number) {
    case 0:
        return "";
    case 1:
        return "\uE000";
    case 2:
        return "\uE001";
    case 3:
        return "\uE002";
    case 4:
        return "\uE003";
    case 5:
        return "\uE004";
    case 6:
        return "\uE005";
    case 7:
        return "\uE006";
    case 8:
        return "\uE007";
    default:
        return "\uE007";
    }
}

std::string StringFormer::horisontalBar(unsigned number) {
    switch (number) {
    case 0:
        return "";
    case 1:
        return "\uE008";
    case 2:
        return "\uE009";
    case 3:
        return "\uE00A";
    case 4:
        return "\uE00B";
    case 5:
        return "\uE00B \uE008";
    case 6:
        return "\uE00B \uE009";
    case 7:
        return "\uE00B \uE00A";
    case 8:
        return "\uE00B \uE00B";
    default:
        return "\uE00B \uE00B";
    }
}

} // namespace proj172::core
