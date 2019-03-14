#include "unitsamountinfo.h"

UnitsAmountInfo::UnitsAmountInfo(std::vector<Worker *> *vector) {
    this->vector = vector;
}

std::string UnitsAmountInfo::getInfo() {
    return "Units amount: " + std::to_string(vector->size()) + '\n';
}
