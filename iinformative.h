#ifndef IINFORMATIVE_H
#define IINFORMATIVE_H

#include <string>

class IInformative {
public:
    std::string virtual getInfo();
    virtual ~IInformative();
};

#endif // IINFORMATIVE_H
