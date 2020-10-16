#ifndef UNITSAMOUNTINFO_H
#define UNITSAMOUNTINFO_H

#include <list>

#include <src/entity.h>

#include <src/iinformative.h>

class UnitsAmountInfo : public IInformative {
private:
    e172::Context *m_context = nullptr;
public:
    UnitsAmountInfo(e172::Context *context);

    // IInformative interface
public:
    std::string info() const override;
};

#endif // UNITSAMOUNTINFO_H
