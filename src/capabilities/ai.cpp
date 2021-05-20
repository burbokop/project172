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

bool AI::executeDocking(const e172::ptr<Unit> &targetUnit) {
    if (parentUnit()) {
        if(parentUnit()->docker()) {
            docker = parentUnit()->docker();
            m_targetUnit = targetUnit;
            m_status = DockingExecution;
            statusString = "docken execution";
            return true;
        }
    }
    return false;
}

void AI::proceed(e172::Context *context, e172::AbstractEventHandler *) {
    if (auto thisShip = e172::smart_cast<Ship>(parentUnit())) {
        if(m_status == DockingExecution && m_targetUnit) {
            auto direction = m_targetUnit->position() - thisShip->position();
            auto distance = direction.module();
            auto diractionAngle = direction.angle();
            if(distance > 250) {
                auto targeted = (e172::Math::radiansDistance(diractionAngle, parentUnit()->rotation()) < e172::Math::Pi / 32);
                if(targeted) {
                    thisShip->thrustForward();
                } else {
                    thisShip->addTargetRotationForse(diractionAngle, 1, 1);
                }
            } else {
                if (docker) {
                    if(!session) {
                        session = docker->createDockingSessionWithUnit(context, m_targetUnit);
                        if(session) {
                            statusString = "session created";
                        } else {
                            statusString = "session creation failed";
                        }
                    }
                }
                if(session) {
                    const auto nodes = session->nodes();
                    const auto thisNode = nodes.at(thisShip);
                    const auto targetNode = nodes.at(m_targetUnit);

                    const auto thisNodeGlobalOffset = thisShip->rotationMatrix() * thisNode.offset();
                    const auto targetNodeGlobalOffset = m_targetUnit->rotationMatrix() * targetNode.offset();

                    auto nodeDirection = m_targetUnit->position() - thisShip->position() + targetNodeGlobalOffset - thisNodeGlobalOffset;
                    auto nodeDiractionAngle = nodeDirection.angle();
                    auto nodeDistance = nodeDirection.module();

                    if (nodeDistance > 32) {
                        auto targeted = (e172::Math::radiansDistance(nodeDiractionAngle, parentUnit()->rotation()) < e172::Math::Pi / 32);
                        if(targeted) {
                            thisShip->thrustForward(0.4);
                        } else {
                            thisShip->addTargetRotationForse(diractionAngle, 1, 1);
                        }
                    } else {
                        thisShip->maneuverLeft();
                    }
                }
            }
        } else {
            m_status = Idle;
        }
    }
}


void AI::render(e172::AbstractRenderer *renderer) {
    if(m_status == DockingExecution && parentUnit()) {
        const auto format = e172::TextFormat(e172::TextFormat::AlignHCenter | e172::TextFormat::AlignTop, 10);
        renderer->drawStringShifted(statusString, parentUnit()->position() + e172::Vector(0, -32), 0xffaaaa, format);
    }
}
