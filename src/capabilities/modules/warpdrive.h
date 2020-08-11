#ifndef WARPDRIVE_H
#define WARPDRIVE_H

#include "capabilities/modules/module.h"

class WarpDrive : public Module {
public:
    static const uint8_t WARP_DISABLED;
    static const uint8_t WARP_LOADING;
    static const uint8_t WARP_READY;
    static const uint8_t WARP_EXECUTING;
    static const uint8_t WARP_RECHARGING;
private:

    static const int DEFAULT_CYCLES_NUMBER = 12;

    uint8_t warpState = WARP_DISABLED;
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
    uint8_t abortWarp(e172::Context *context);

    // Entity interface
public:
    void proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler) override;
};

#endif // WARPDRIVE_H
