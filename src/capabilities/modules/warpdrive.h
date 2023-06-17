#pragma once

#include "module.h"

namespace proj172::core {

class WarpDrive : public Module {
public:
    enum State { WarpDisabled, WarpLoading, WarpReady, WarpExecuting, WarpRecharging };

public:
    WarpDrive(e172::FactoryMeta &&meta);
    WarpDrive(e172::FactoryMeta &&meta, Loadable *tmp);

    State warpState() const { return m_warpState; }
    double warpVelocity() const { return m_warpVelocity; }

    bool prepareWarp();
    bool warp();
    State abortWarp(e172::Context *context);

    // Entity interface
public:
    void proceed(e172::Context *context, e172::EventHandler *eventHandler) override;

    // IInformative interface
public:
    std::string info() const override;

private:
    double charging() const;
    std::string stateAsString() const;
    std::string stateAsIcon() const;

private:
    static const int DEFAULT_CYCLES_NUMBER = 12;

    State m_warpState = WarpDisabled;
    int m_currentChargindIteration = 0;
    int m_chargindIterations = DEFAULT_CYCLES_NUMBER;
    double m_warpVelocity = 0.1;
};

} // namespace proj172::core
