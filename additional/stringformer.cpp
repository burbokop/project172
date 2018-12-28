#include "stringformer.h"


std::string StringFormer::line(unsigned int number) {
    return line(number, '-');
}

std::string StringFormer::line(unsigned int number, char simbol) {
    std::string result = "";
    for(unsigned int i = 0; i < number; i++) {
        result += simbol;
    };
    return result;
}

std::string StringFormer::bar(unsigned int number)
{
    switch (number) {
    case 0:
        return " ";
    case 1:
        return "▁";
    case 2:
        return "▂";
    case 3:
        return "▃ \u9603";
    case 4:
        return "▅";
    case 5:
        return "▆";
    case 6:
        return "▇";
    default:
        return " ";
    }

}
