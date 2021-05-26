#include "dockingtaskexecutor.h"

#include <src/capabilities/capability.h>
#include <src/math/math.h>
#include <src/capabilities/docker.h>


e172::Line2d DockingTaskExecutor::landingStrip() const {
    return m_landingStrip;
}

bool DockingTaskExecutor::start(const e172::ptr<Unit> &targetUnit) {
    return m_capability.fold<bool>([this, targetUnit](Capability *capability){
        return capability->parentUnit().fold<bool>([this, targetUnit](Unit* unit){
            return unit->capability<Docker>().fold<bool>([this, targetUnit](Docker *docker){
                m_docker = docker;
                m_targetUnit = targetUnit;
                m_status = ApproachingToTarget;
                return true;
            });
        });
    });
}

bool DockingTaskExecutor::undock() {
    if(m_status == Docked) {
        m_status = Idle;
        return true;
    }
    return false;
}

bool DockingTaskExecutor::approachToPoint(const e172::Vector &point, double cryticalDistance, double speed) {
    if(m_capability) {
        if (auto parentShip = e172::smart_cast<Ship>(m_capability->parentUnit())) {
            auto direction = point - parentShip->position();
            auto distance = direction.module();
            auto diractionAngle = direction.angle();
            if(distance > cryticalDistance) {
                m_targetPoint = point;
                auto targeted = (e172::Math::radiansDistance(diractionAngle, parentShip->rotation()) < e172::Math::Pi / 32);
                if(targeted) {
                    parentShip->thrustForward(speed);
                } else {
                    parentShip->addTargetRotationForse(diractionAngle, 1, 1);
                }
                return false;
            }
            return true;
        } else {
            m_status = Idle;
        }
    } else {
        m_status = Idle;
    }
    return false;
}

void DockingTaskExecutor::proceed(e172::Context *context) {
    if(m_capability && m_targetUnit) {
        if (auto parentShip = e172::smart_cast<Ship>(m_capability->parentUnit())) {
            if(m_status == ApproachingToTarget) {
                if (approachToPoint(m_targetUnit->position(), 500)) {
                    m_session = m_docker->createDockingSessionWithUnit(context, m_targetUnit);
                    if (m_session) {
                        m_status = Manuevering;
                    } else {
                        m_status = Idle;
                    }
                }
            } else if(m_status == Manuevering) {
                if(m_session) {
                    const auto nodes = m_session->nodes();
                    const auto parentNode = nodes.at(parentShip);
                    const auto targetNode = nodes.at(m_targetUnit);
                    const auto targetNodeGlobalPosition = targetNode.globalPosition(m_targetUnit.data());

                    m_landingStrip = e172::Line2d::fromAngle(
                                targetNode.angle() + m_targetUnit->rotation() + e172::Math::Pi / 2,
                                targetNodeGlobalPosition - parentShip->rotationMatrix() * parentNode.offset()
                                );

                    const auto n0 = targetNodeGlobalPosition - parentShip->rotationMatrix() * parentNode.offset() + (m_targetUnit->rotationMatrix() * targetNode.offset()).rightNormal().normalized() * 200;

                    if(approachToPoint(n0, 64, 0.7)) {
                        m_status = ApproachingToNode;
                    }
                } else {
                    m_status = Idle;
                }
            } else if(m_status == ApproachingToNode) {
                if(m_session) {
                    const auto units = m_session->units();
                    const auto nodes = m_session->nodes();
                    const auto parentNode = nodes.at(parentShip);
                    const auto targetNode = nodes.at(m_targetUnit);
                    const auto targetNodeGlobalPosition = targetNode.globalPosition(m_targetUnit.data());

                    const auto n1 = targetNodeGlobalPosition - parentShip->rotationMatrix() * parentNode.offset();
                    if(approachToPoint(n1, 32, 0.3)) {
                        m_status = WaitForDocked;
                    }
                } else {
                    m_status = Idle;
                }
            } else if(m_status == WaitForDocked) {
                if(m_session) {
                    if(m_session->docked()) {
                        m_status = Docked;
                    }
                } else {
                    m_status = Idle;
                }
            }
        }
    } else {
        m_status = Idle;
    }
}


e172::Vector DockingTaskExecutor::targetPoint() const {
    return m_targetPoint;
}

DockingTaskExecutor::DockingTaskExecutor(const e172::ptr<Capability> &capability) {
    m_capability = capability;
}
