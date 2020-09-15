#include "docker.h"
#include <src/engine/math/math.h>
#include <src/units/unit.h>
#include <src/engine/context.h>

void Docker::addNode(const e172::Vector &offset, double angle) {
    m_nodePool.addNode(offset, angle);
}

Docker::Docker() {}

Docker::~Docker() {
    closeAllSessions();
}

bool Docker::createDockingSessionWithUnit(e172::Context* context, Unit *unit) {
    auto docker = unit->docker();
    if(docker && parentUnit()) {
        const auto session = DockingSession::createSession(&m_nodePool, &docker->m_nodePool, parentUnit(), unit);
        if(session) {
            m_sessions.push_back(session);
            docker->m_sessions.push_back(session);
            context->addEntity(session);
            return true;
        }
    }
    return false;
}

void Docker::closeAllSessions() {
    for(auto s : m_sessions) {
        s->release();
    }
    m_sessions.clear();
}

size_t Docker::sessionCount() const {
    return m_sessions.size();
}

std::string Docker::sessionInfo(size_t index) const {
    const auto session = m_sessions[index];
    if(session) {
        const auto oppositeUnit = session->oppositeUnit(parentUnit());
        if(oppositeUnit) {
            if(session->state() == PhysicalDockingAttractor::NotDocked) {
                return oppositeUnit->info() + " [docking permitted]";
            } else if(session->state() == PhysicalDockingAttractor::InInterception) {
                return oppositeUnit->info() + " [docking strarted]";
            } else if(session->state() == PhysicalDockingAttractor::Docked) {
                return oppositeUnit->info() + " [docking compleated]";
            }
        }
    }
    return "[session info error]";
}

void Docker::proceed(e172::Context *, e172::AbstractEventHandler *) {
    auto it = m_sessions.begin();
    while (it != m_sessions.end()) {
        if(!(*it)->fullUsageCount()) {
            (*it)->release();
            it = m_sessions.erase(it);
        } else {
            ++it;
        }
    }
}

void Docker::render(e172::AbstractRenderer *renderer) {}
