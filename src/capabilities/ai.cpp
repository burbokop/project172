#include "ai.h"

#include <src/graphics/abstractrenderer.h>
#include <src/units/ship.h>
#include <src/units/unit.h>
#include <e172/src/math/math.h>
#include <src/debug.h>
AI::Status AI::status() const {
    return m_status;
}

AI::AI() : Controller () {
}

void AI::executeDocking(const e172::ptr<Unit> &targetUnit) {
    m_targetUnit = targetUnit;
    m_status = DockingExecution;
}

void AI::proceed(e172::Context *context, e172::AbstractEventHandler *) {
    if (auto thisShip = e172::smart_cast<Ship>(parentUnit())) {
        if(m_status == DockingExecution && m_targetUnit) {
            auto direction = m_targetUnit->position() - thisShip->position();
            auto diractionAngle = direction.angle();
            auto targeted = (e172::Math::radiansDistance(diractionAngle, parentUnit()->rotation()) < e172::Math::Pi / 32);
            if(targeted) {
                thisShip->thrustForward();
            } else {
                thisShip->addTargetRotationForse(diractionAngle, 1, 1);
            }
        } else {
            m_status = Idle;
        }
    }
}


void AI::render(e172::AbstractRenderer *renderer) {
    if(m_status == DockingExecution && parentUnit()) {
        const auto format = e172::TextFormat(e172::TextFormat::AlignHCenter | e172::TextFormat::AlignTop, 10);
        renderer->drawStringShifted("docking execution", parentUnit()->position() + e172::Vector(0, -32), 0xffaaaa, format);
    }
}
