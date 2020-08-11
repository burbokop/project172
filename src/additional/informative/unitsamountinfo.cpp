#include "unitsamountinfo.h"
#include <list>

UnitsAmountInfo::UnitsAmountInfo(std::list<e172::Entity *> *vector) {
    this->vector = vector;
}

std::string UnitsAmountInfo::getInfo() {
    return "Units amount: " + std::to_string(vector->size()) + '\n';
}
