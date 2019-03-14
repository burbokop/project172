#ifndef UNITSAMOUNTINFO_H
#define UNITSAMOUNTINFO_H

#include <vector>

#include "worker.h"
#include "iinformative.h"

class UnitsAmountInfo : public IInformative {
private:
    std::vector<Worker*> *vector;

public:
    UnitsAmountInfo(std::vector<Worker*> *vector);

    // IInformative interface
public:
    std::string getInfo();
};

#endif // UNITSAMOUNTINFO_H
