#include "near.h"


#include <src/engine/context.h>
#include <src/engine/objectregistry.h>


const double Near::RADIUS_DELTA = 16;
const double Near::DEFAULT_RADIUS = 512;
const double Near::WARP_RADIUS_MILTIPLIER = 8;


Near::Near(Controller *center, double radius) {
    m_center = center;
    this->radius = radius;
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
    double result = radius;
    if(Ship *centerShip = dynamic_cast<Ship*>(center)) {
        WarpDrive *wd = centerShip->getFirstWarp();
        if(wd && wd->getState() == WarpDrive::WARP_EXECUTING) {
            result *= WARP_RADIUS_MILTIPLIER;
        }
    }
    return result;
}

Near::Near(double radius) {
    this->radius = radius;
}

Controller *Near::center() const
{
    return m_center;
}

void Near::setCenter(Controller *center)
{
    m_center = center;
}

void Near::removeEntities(e172::Context *) {
    if(removingIterator != m_entitiesInFocus.end()) {
        e172::Entity *current = *removingIterator;
        if(e172::ObjectRegistry::exists(current)) {
            const auto currentUnit = dynamic_cast<Unit*>(current);
            const auto centerUnit = m_center->parentUnit();
            if(currentUnit && centerUnit == e172::Alive) {
                if((currentUnit->position() - centerUnit->position()).module() > (localRadius(centerUnit) + RADIUS_DELTA)) {
                    removingIterator = m_entitiesInFocus.erase(removingIterator);
                }
            }
        }
    }
    if(++removingIterator == m_entitiesInFocus.end()) removingIterator = m_entitiesInFocus.begin();
}

std::list<e172::Entity *> Near::entitiesInFocus() {
    return m_entitiesInFocus;
}

void Near::proceed(e172::Context *context, e172::AbstractEventHandler *) {
    if(m_center != nullptr) {
        addEntities(context);
        removeEntities(context);
    }
}
