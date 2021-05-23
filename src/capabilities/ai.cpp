#include "ai.h"

#include <src/graphics/abstractrenderer.h>
#include <src/units/ship.h>
#include <src/units/unit.h>
#include <e172/src/math/math.h>
#include <src/debug.h>
#include <src/math/line2d.h>
#include <src/math/math.h>
#include <iostream>

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
            lastStage = false;
            return true;
        }
    }
    return false;
}

bool AI::goToPoint(const e172::Vector &point, double cryticalDistance, double speed) {
    if (auto thisShip = e172::smart_cast<Ship>(parentUnit())) {
        auto direction = point - parentUnit()->position();
        auto distance = direction.module();
        auto diractionAngle = direction.angle();
        if(distance > cryticalDistance) {
            auto targeted = (e172::Math::radiansDistance(diractionAngle, parentUnit()->rotation()) < e172::Math::Pi / 32);
            if(targeted) {
                thisShip->thrustForward(speed);
            } else {
                thisShip->addTargetRotationForse(diractionAngle, 1, 1);
            }
            return false;
        }
        return true;
    }
    return false;
}

void AI::proceed(e172::Context *context, e172::AbstractEventHandler *) {
    if (auto thisShip = e172::smart_cast<Ship>(parentUnit())) {
        if(m_status == DockingExecution && m_targetUnit) {
            if (goToPoint(m_targetUnit->position(), 500)) {
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

                    const auto thisNodeGlobalPosition = thisShip->position() + thisShip->rotationMatrix() * thisNode.offset();
                    const auto targetNodeGlobalPosition = m_targetUnit->position() + m_targetUnit->rotationMatrix() * targetNode.offset();

                    _vec = targetNodeGlobalPosition;
                    _line = e172::Line2d::fromAngle(targetNode.angle() + m_targetUnit->rotation() + e172::Math::Pi / 2, targetNodeGlobalPosition + m_targetUnit->rotationMatrix() * thisNode.offset());
                    _dist = _line.distanceToPoint(thisNodeGlobalPosition);

                    auto angl = e172::Math::topLimitedFunction(_dist) * e172::Math::Pi / 2;
                    angl *= -1.5;


                    const auto n0 = targetNodeGlobalPosition + m_targetUnit->rotationMatrix() * thisNode.offset() + (m_targetUnit->rotationMatrix() * targetNode.offset()).rightNormal().normalized() * 300;



                    auto nodeDirection = targetNodeGlobalPosition - thisNodeGlobalPosition;
                    auto nodeDiractionAngle = nodeDirection.angle();
                    auto nodeDistance = nodeDirection.module();

                    if(!lastStage) {
                        if(goToPoint(n0, 64, 0.5)) {
                            lastStage = true;
                        }
                        _vec = n0;
                    } else {
                        auto n1 = targetNodeGlobalPosition + m_targetUnit->rotationMatrix() * thisNode.offset();
                        if(goToPoint(n1, 32, 0.1)) {
                            statusString = "ready dock";
                            session.
                            m_status = Docked;
                        }
                        _vec = n1;
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
        renderer->drawStringShifted(statusString + " " + std::to_string(_dist), parentUnit()->position() + e172::Vector(0, -32), 0xffaaaa, format);
        renderer->drawLineShifted(_line, 0xffaaff);
        renderer->drawCircleShifted(_vec, 8, 0xffaaff);
    }
}
