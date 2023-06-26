#pragma once

#include <string>

namespace proj172::core {

struct StringFormer {
    static std::string line(unsigned number);
    static std::string line(unsigned number, char simbol);
    static std::string line(unsigned number, unsigned max);
    static std::string line(unsigned number, char simbol, unsigned max);


    static std::string bar(unsigned number);
    static std::string horisontalBar(unsigned number);
};

} // namespace proj172::core
