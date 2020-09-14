#include "near.h"


#include <src/engine/context.h>
#include <src/engine/objectregistry.h>

#include <src/units/ship.h>
#include <src/capabilities/capability.h>
#include <src/capabilities/modules/warpdrive.h>


const double Near::DEFAULT_RADIUS_DELTA = 16;
const double Near::DEFAULT_RADIUS = 512;
const double Near::WARP_RADIUS_MILTIPLIER = 8;


Near::Near(Capability *center, double radius, double delta) {
    m_center = center;
    m_radius = radius;
    m_delta = delta;
}

int Near::entityInFocusCount() const {
    return m_entitiesInFocus.size();
}

e172::Entity *Near::entityInFocus(int index) const {
    return m_entitiesInFocus[index];
}

bool Near::containsEntity(e172::Entity *entity) const {
    for(size_t i = 0; i < m_entitiesInFocus.size(); ++i) {
        if(entity == m_entitiesInFocus[i])
            return true;
    }
    return false;
}

void Near::addEntities(e172::Context *context) {
    const auto current = context->autoIteratingEntity();

    if(e172::ObjectRegistry::exists(current)) {
        Unit *currentUnit = dynamic_cast<Unit*>(current);
        Unit *centerUnit = m_center->parentUnit();


        if(
                currentUnit != nullptr &&
                centerUnit != nullptr &&
                currentUnit != centerUnit &&
                std::find(m_entitiesInFocus.begin(), m_entitiesInFocus.end(), current) == m_entitiesInFocus.end() &&
                (currentUnit->position() - centerUnit->position()).module() <= localRadius(centerUnit)
                ) {
            m_entitiesInFocus.push_back(current);
        }
    }
}

double Near::localRadius(Unit *center) {
    double result = m_radius;
    if(Ship *centerShip = dynamic_cast<Ship*>(center)) {
        WarpDrive *wd = centerShip->firstWarp();
        if(wd && wd->getState() == WarpDrive::WARP_EXECUTING) {
            result *= WARP_RADIUS_MILTIPLIER;
        }
    }
    return result;
}

Near::Near(double radius, double delta) {
    m_radius = radius;
    m_delta = delta;
}

Capability *Near::center() const {
    return m_center;
}

void Near::setCenter(Capability *center) {
    m_center = center;
}

void Near::removeEntities(e172::Context *) {
    if(removingIterator < m_entitiesInFocus.size()) {
        e172::Entity *current = m_entitiesInFocus[removingIterator];
        if(current == e172::Alive) {
            const auto currentUnit = dynamic_cast<Unit*>(current);
            const auto centerUnit = m_center->parentUnit();
            if(currentUnit && centerUnit == e172::Alive) {
                if((currentUnit->position() - centerUnit->position()).module() > (localRadius(centerUnit) + m_delta)) {
                    const auto it = std::find(m_entitiesInFocus.begin(), m_entitiesInFocus.end(), current);
                    m_entitiesInFocus.erase(it);
                }
            }
        } else {
            const auto it = std::find(m_entitiesInFocus.begin(), m_entitiesInFocus.end(), current);
            m_entitiesInFocus.erase(it);
        }
    }
    if(++removingIterator >= m_entitiesInFocus.size()) removingIterator = 0;
}

void Near::proceed(e172::Context *context, e172::AbstractEventHandler *) {
    if(m_center != nullptr) {
        addEntities(context);
        removeEntities(context);
    }
}
