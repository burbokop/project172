#ifndef SHIP_H
#define SHIP_H


#include "movable.h"

class WarpDrive;
class Ship : public Movable {
private:
    static const double ONE_WARP_POINT;
public:
    Ship();

    bool prepareWarp();
    bool warp();
    uint8_t abortWarp(e172::Context *context);
    WarpDrive *getFirstWarp();

    // Entity interface
public:
    void proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler);

    // Movable interface
protected:
    bool onAcceleration(bool start);
};

#endif // SHIP_H
