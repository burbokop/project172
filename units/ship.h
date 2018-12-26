#ifndef SHIP_H
#define SHIP_H

#include "movable.h"
#include "capabilities/modules/warpdrive.h"

class Ship : public Movable {
private:
    static const double ONE_WARP_POINT;
public:
    Ship();
    Ship(Loadable *tmp);

    bool prepareWarp();
    bool warp();
    Uint8 abortWarp();


    // Worker interface
public:


    // Worker interface
public:
    void loop(Context *context, Event *event);
};

#endif // SHIP_H
