#ifndef UNITSAMOUNTINFO_H
#define UNITSAMOUNTINFO_H

#include <list>

#include <src/engine/entity.h>

#include <src/iinformative.h>

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
