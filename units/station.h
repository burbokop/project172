#ifndef STATION_H
#define STATION_H

#include "units/unit.h"

class Station : public Unit {
public:
    Station();
    Station(Loadable *tmp);
};

#endif // STATION_H
