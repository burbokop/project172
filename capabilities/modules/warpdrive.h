#ifndef WARPDRIVE_H
#define WARPDRIVE_H

#include "module.h"

class WarpDrive : public Module {
public:
    static const Uint8 WARP_DISABLED;
    static const Uint8 WARP_LOADING;
    static const Uint8 WARP_READY;
    static const Uint8 WARP_EXECUTING;
    static const Uint8 WARP_RECHARGING;
private:

    static const int DEFAULT_CYCLES_NUMBER = 12;

    Uint8 warpState = WARP_DISABLED;
    int currentChargindIteration = 0;
    int chargindIterations = DEFAULT_CYCLES_NUMBER;

public:
    WarpDrive();
    WarpDrive(Loadable *tmp);

    int getState();
    double getSpeadUnit();

    bool prepareWarp();
    bool warp();
    Uint8 abortWarp();

    // Worker interface
public:
    void loop(Context *context, Event *event);
};

#endif // WARPDRIVE_H
