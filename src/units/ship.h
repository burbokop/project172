#ifndef SHIP_H
#define SHIP_H


#include "units/movable.h"
#include "capabilities/modules/warpdrive.h"


class Ship : public Movable {
private:
    static const double ONE_WARP_POINT;
public:
    Ship();
    Ship(Loadable *tmp);

    bool prepareWarp();
    bool warp();
    uint8_t abortWarp(Context *context);
    WarpDrive *getFirstWarp();

    // Worker interface
public:
    void tick(Context *context, e172::AbstractEventHandler *eventHandler);

    // Movable interface
protected:
    bool onAcceleration(bool start);
};

#endif // SHIP_H
