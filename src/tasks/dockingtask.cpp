#include "dockingtask.h"

#include <src/capabilities/controller.h>
#include <src/math/math.h>
#include <src/capabilities/docker.h>
#include <src/context.h>
#include <src/units/unit.h>

namespace proj172::core {

bool DockingTask::approachToPoint(const e172::Vector<double> &point, double cryticalDistance, double speed) {
    if(parentController()) {
        if (auto parentShip = e172::smart_cast<Ship>(parentController()->parentUnit())) {
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

void DockingTask::proceed(e172::Context *context) {
    if(parentController() && m_targetUnit) {
        if (auto parentShip = e172::smart_cast<Ship>(parentController()->parentUnit())) {
            if(m_status == ApproachingToTarget) {
                if (approachToPoint(m_targetUnit->position(), 500)) {
                    m_session = m_docker->createDockingSessionWithUnit(context, m_targetUnit);
                    if (m_session) {
                        m_status = Manuevering;
                        out() << "DockingTask: status changed to: " << statusString() << std::endl;
                    } else {
                        m_status = Idle;
                        out() << "DockingTask: failed to create docking session." << std::endl;
                        completeTask();
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
                        out() << "DockingTask: status changed to: " << statusString() << std::endl;
                    }
                } else {
                    m_status = Idle;
                    out() << "DockingTask: session do not exist" << std::endl;
                    completeTask();
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
                        out() << "DockingTask: status changed to: " << statusString() << std::endl;
                    }
                } else {
                    m_status = Idle;
                    out() << "DockingTask: session do not exist." << std::endl;
                    completeTask();
                }
            } else if(m_status == WaitForDocked) {
                if(m_session) {
                    if(m_session->docked()) {
                        out() << "DockingTask: docking compleated." << std::endl;
                        completeTask();
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

DockingTask::DockingTask(const e172::ptr<Unit> &targetUnit) {
    m_targetUnit = targetUnit;
}

bool DockingTask::start(e172::Context *) {
    return parentController().fold<bool>([this](Controller *controller) {
        return controller->parentUnit().fold<bool>([this](Unit* unit) {
            return unit->capability<Docker>().fold<bool>([this](Docker *docker){
                m_docker = docker;
                m_status = ApproachingToTarget;
                return true;
            }, [this](){
                out() << "DockingTask: error: parent unit does not have docker" << std::endl;
                completeTask();
                return false;
            });
        }, [this](){
            out() << "DockingTask: error: controller do not have parent unit" << std::endl;
            completeTask();
            return false;
        });
    }, [this](){
        out() << "DockingTask: error: parent controller is null" << std::endl;
        completeTask();
        return false;
    });
}


void DockingTask::initFromCommand(const std::vector<std::string> &args, e172::Context *context) {
    if (args.size() > 1) {
        bool ok;
        auto targetId = e172::Variant(args[1]).toNumber<e172::Entity::Id>(&ok);
        if(ok) {
            if(auto target = context->entityById<Unit>(targetId)){
                m_targetUnit = target;
            } else {
                out() << "DockingTask: error: target with id: " << targetId << " not found" << std::endl;
                completeTask();
            }
        } else {
            out() << "DockingTask: error: " << args[1] << " invlid target id" << std::endl;
            completeTask();
        }
    } else {
        out() << "DockingTask: error: must have 2 arguments" << std::endl;
        completeTask();
    }
}

} // namespace proj172::core
