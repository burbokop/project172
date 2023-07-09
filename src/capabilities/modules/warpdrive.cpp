#include "warpdrive.h"

#include "../../additional/stringformer.h"
#include "../../messagetype.h"
#include "../../units/unit.h"
#include <e172/args.h>
#include <e172/context.h>

namespace proj172::core {

WarpDrive::WarpDrive(e172::FactoryMeta &&meta)
    : Module(std::move(meta))
{
    registerInitFunction([this]() { m_warpVelocity = asset<double>("warp-speed", 0.1); });
}

std::string WarpDrive::stateAsString() const {
    switch (m_warpState) {
    case WarpDisabled:
        return "WARP_DISABLED";
    case WarpLoading:
        return "WARP_LOADING";
    case WarpReady:
        return "WARP_READY";
    case WarpExecuting:
        return "WARP_EXECUTING";
    case WarpRecharging:
        return "WARP_RECHARGING";
    default:
        return std::to_string(m_warpState);
    }
}

std::string WarpDrive::stateAsIcon() const {
    switch (m_warpState) {
    case WarpDisabled:
        return "disabled";
    case WarpLoading:
        return ">>";
    case WarpReady:
        return "ready";
    case WarpExecuting:
        return "=>";
    case WarpRecharging:
        return "<<";
    default:
        return std::to_string(m_warpState);
    }
}

double WarpDrive::charging() const {
    return (static_cast<double>(m_currentChargindIteration) / m_chargindIterations);
}

std::string WarpDrive::info() const {
    std::string chargingBar;
    if (m_warpState == WarpDrive::WarpRecharging) {
        chargingBar = StringFormer::line(static_cast<unsigned int>((1 - charging()) * 4));
    } else if (m_warpState == WarpDrive::WarpLoading) {
        chargingBar = StringFormer::line(static_cast<unsigned int>((m_timer.progress() * 4)));
    } else if (m_warpState == WarpDrive::WarpDisabled) {
        chargingBar = "";
    } else if (m_warpState == WarpDrive::WarpExecuting) {
        chargingBar = "----";
    } else if (m_warpState == WarpDrive::WarpReady) {
        chargingBar = "----";
    }
    return "WD   |" + chargingBar + "|   " + stateAsIcon();
}

bool WarpDrive::prepareWarp() {
    if (m_warpState == WarpDisabled) {
        m_warpState = WarpLoading;
        m_timer.reset();
        return true;
    }
    return false;
}

bool WarpDrive::warp() {
    if (m_warpState == WarpReady) {
        m_warpState = WarpExecuting;
        m_audioPlayer.play();
        m_animator.play(e172::Animator::Loop);
        return true;
    }
    return false;
}

WarpDrive::State WarpDrive::abortWarp(e172::Context *context)
{
    State result = m_warpState;
    if (m_warpState == WarpExecuting) {
        const e172::Args args(parentUnit()->position(), parentUnit()->velocity() * 0.8, 16);
        context->emitMessage(~MessageType::SpawnExplosive, args);
        m_audioPlayer.stop();
        m_animator.play(e172::Animator::NotRender);
    }
    if (m_warpState == WarpExecuting || m_warpState == WarpReady || m_warpState == WarpLoading)
        m_warpState = WarpRecharging;
    return result;
}

void WarpDrive::proceed(e172::Context *context, e172::EventHandler *eventHandler) {
    if (m_warpState == WarpLoading) {
        if (m_timer.check()) {
            m_warpState = WarpReady;
        }
    } else if (m_warpState == WarpRecharging) {
        if (m_timer.check()) {
            m_currentChargindIteration++;
            if (m_currentChargindIteration >= m_chargindIterations) {
                m_currentChargindIteration = 0;
                m_warpState = WarpDisabled;
            }
        }
    }

    this->Module::proceed(context, eventHandler);
}

} // namespace proj172::core
