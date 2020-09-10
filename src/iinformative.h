#ifndef IINFORMATIVE_H
#define IINFORMATIVE_H

#include <string>

class IInformative {
public:
    std::string virtual info() const;
    virtual ~IInformative();
};

#endif // IINFORMATIVE_H
