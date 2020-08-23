#ifndef UNITSAMOUNTINFO_H
#define UNITSAMOUNTINFO_H

#include <list>

#include <engine/entity.h>

#include "iinformative.h"

class UnitsAmountInfo : public IInformative {
private:
    e172::Context *m_context = nullptr;
public:
    UnitsAmountInfo(e172::Context *context);

    // IInformative interface
public:
    std::string getInfo();
};

#endif // UNITSAMOUNTINFO_H
