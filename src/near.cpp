#include "near.h"

#include <src/context.h>
#include <src/debug.h>
#include <src/units/ship.h>
#include <src/capabilities/capability.h>
#include <src/capabilities/modules/warpdrive.h>

namespace proj172::core {

const double Near::DEFAULT_RADIUS_DELTA = 16;
const double Near::DEFAULT_RADIUS = 512;
const double Near::WARP_RADIUS_MILTIPLIER = 8;

Near::Near(e172::FactoryMeta &&meta, Capability *center, double radius, double delta)
    : e172::Entity(std::move(meta))
    , m_center(center)
    , m_radius(radius)
    , m_delta(delta)
{}

int Near::entityInFocusCount() const {
    return m_entitiesInFocus.size();
}

e172::ptr<e172::Entity> Near::entityInFocus(int index) const {
    return m_entitiesInFocus[index];
}

bool Near::containsEntity(const e172::ptr<e172::Entity> &entity) const {
    for(size_t i = 0; i < m_entitiesInFocus.size(); ++i) {
        if(entity == m_entitiesInFocus[i])
            return true;
    }
    return false;
}

void Near::addEntities(e172::Context *context) {
    const auto current = context->autoIteratingEntity();
    if(current) {
        const auto currentUnit = e172::smart_cast<Unit>(current);
        const auto centerUnit = m_center->parentUnit();

        if(
                currentUnit &&
                centerUnit &&
                currentUnit != centerUnit
                ) {
            if(
                    findEntityInFocus(current) == m_entitiesInFocus.end() &&
                    (currentUnit->position() - centerUnit->position()).module() <= localRadius(centerUnit)
                    )
                m_entitiesInFocus.push_back(current);
        }
    }
}

double Near::localRadius(const e172::ptr<Unit> &center) {
    double result = m_radius;
    if(const auto centerShip = e172::smart_cast<Ship>(center)) {
        const auto wd = centerShip->firstWarp();
        if (wd && wd->warpState() == WarpDrive::WarpExecuting) {
            result *= WARP_RADIUS_MILTIPLIER;
        }
    }
    return result;
}

Near::Near(e172::FactoryMeta &&meta, double radius, double delta)
    : e172::Entity(std::move(meta))
    , m_radius(radius)
    , m_delta(delta)
{}

void Near::removeEntities(e172::Context *) {
    if(removingIterator < m_entitiesInFocus.size()) {
        const auto current = m_entitiesInFocus[removingIterator];
        if(current) {
            const auto currentUnit = e172::smart_cast<Unit>(current);
            const auto centerUnit = m_center->parentUnit();
            if(currentUnit && centerUnit) {
                if((currentUnit->position() - centerUnit->position()).module() > (localRadius(centerUnit) + m_delta)) {
                    const auto it = findEntityInFocus(current);
                    m_entitiesInFocus.erase(it);
                }
            }
        } else {
            const auto it = findEntityInFocus(current);
            m_entitiesInFocus.erase(it);
        }
    }
    if(++removingIterator >= m_entitiesInFocus.size()) removingIterator = 0;
}

void Near::proceed(e172::Context *context, e172::EventHandler *) {
    if (m_center) {
        addEntities(context);
        removeEntities(context);
    }
}

} // namespace proj172::core
