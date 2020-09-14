#include "docker.h"
#include <src/engine/math/math.h>
#include <src/units/unit.h>
#include <src/engine/context.h>

Docker::Docker() {
    m_nodePool.addNode({ 0, -20 }, -e172::Math::Pi / 2);
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
