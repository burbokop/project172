#ifndef WARPDRIVE_H
#define WARPDRIVE_H

#include "capabilities/modules/module.h"

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
    double warpVelocity = 0.1;

    double getCharging();
    std::string getStateAsString();
    std::string getStateAsIcon();
public:
    WarpDrive();
    WarpDrive(Loadable *tmp);

    int getState();

    std::string getInfo() override;

    double getSpeadUnit() const;

    bool prepareWarp();
    bool warp();
    Uint8 abortWarp(Context *context);

    // Worker interface
public:
    void tick(Context *context, Event *event) override;
};

#endif // WARPDRIVE_H
