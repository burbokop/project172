#ifndef UNITSAMOUNTINFO_H
#define UNITSAMOUNTINFO_H

#include <list>

#include <engine/entity.h>

#include "iinformative.h"

class UnitsAmountInfo : public IInformative {
private:
    std::list<e172::Entity*> *vector;

public:
    UnitsAmountInfo(std::list<e172::Entity*> *vector);

    // IInformative interface
public:
    std::string getInfo();
};

#endif // UNITSAMOUNTINFO_H
