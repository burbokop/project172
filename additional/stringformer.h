#ifndef STRING_H
#define STRING_H

#include <string>

#include "object.h"

class StringFormer : public Object
{
public:
    static std::string line(unsigned int number);
    static std::string line(unsigned int number, char simbol);
    static std::string line(unsigned int number, unsigned int max);
    static std::string line(unsigned int number, char simbol, unsigned int max);


    static std::string bar(unsigned int number);
    static std::string horisontalBar(unsigned int number);
};

#endif // STRING_H
