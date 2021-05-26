#include "docker.h"
#include <src/math/math.h>
#include <src/units/unit.h>
#include <src/context.h>

void Docker::addNode(const e172::Vector &offset, double angle) {
    m_nodePool.addNode(offset, angle);
}

Docker::Docker() {
    registerInitFunction([this](){
        const auto nodes = asset<std::list<std::pair<e172::Vector, double>>>("nodes");
        for(const auto& node : nodes) {
            addNode(node.first, node.second);
        }
    });
}

Docker::~Docker() {
    closeAllSessions();
}

e172::ptr<DockingSession> Docker::createDockingSessionWithUnit(e172::Context* context, const e172::ptr<Unit> &unit) {
    auto docker = unit->capability<Docker>();
    if(!docker) {
        return nullptr;
    }
    if(!parentUnit()) {
        return nullptr;
    }
    const auto session = DockingSession::createSession(&m_nodePool, &docker->m_nodePool, parentUnit(), unit);
    if(session) {
        m_sessions.push_back(session);
        docker->m_sessions.push_back(session);
        context->addEntity(session);
        return session;
    } else {
        return nullptr;
    }
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

e172::ptr<Unit> Docker::oppositeUnit(size_t index) const {
    const auto session = m_sessions[index];
    if(session) {
        return session->oppositeUnit(parentUnit());
    }
    return nullptr;
}

bool Docker::docked(size_t index) const {
    const auto session = m_sessions[index];
    if(session) {
        return session->docked();
    }
    return false;
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
