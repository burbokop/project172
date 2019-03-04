#ifndef STRING_H
#define STRING_H

#include <string>


#include "object.h"


class StringFormer : public Object {
public:
    static std::string line(unsigned number);
    static std::string line(unsigned number, char simbol);
    static std::string line(unsigned number, unsigned max);
    static std::string line(unsigned number, char simbol, unsigned max);


    static std::string bar(unsigned number);
    static std::string horisontalBar(unsigned number);
};

#endif // STRING_H
