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
    Uint8 abortWarp(Context *context);
    WarpDrive *getFirstWarp();

    // Worker interface
public:
    void loop(Context *context, Event *event);

    // Movable interface
protected:
    void onAcceleration(bool start, double acc);
};

#endif // SHIP_H
