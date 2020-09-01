#include "near.h"


#include <src/engine/objectregistry.h>


const double Near::RADIUS_DELTA = 16;
const double Near::DEFAULT_RADIUS = 512;
const double Near::WARP_RADIUS_MILTIPLIER = 8;


Near::Near(std::list<e172::Entity *> *origin, Controller *center, double radius) {
    this->origin = origin;
    this->focus = new std::list<e172::Entity*>();
    this->center = center;
    this->radius = radius;

    addingIterator = origin->begin();
    removingIterator = focus->begin();
}

void Near::add() {
    if(origin->size() > 0 && center != nullptr) {
        if(addingIterator != origin->end()) {
            e172::Entity *current = *addingIterator;
            if(ObjectRegistry::getInstance()->exists(current)) {
                Unit *currentUnit = dynamic_cast<Unit*>(current);
                Unit *centerUnit = center->parentUnit();


                if(
                    currentUnit != nullptr &&
                    centerUnit != nullptr &&
                    currentUnit != centerUnit &&
                    std::find(focus->begin(), focus->end(), current) == focus->end() &&
                    (currentUnit->position() - centerUnit->position()).module() <= getLocalRadius(centerUnit)
                ) {
                    focus->push_back(current);
                }
            }
        }

        if(++addingIterator == origin->end()) addingIterator = origin->begin();
    }
}

double Near::getLocalRadius(Unit *center) {
    double result = radius;
    if(Ship *centerShip = dynamic_cast<Ship*>(center)) {
        WarpDrive *wd = centerShip->getFirstWarp();
        if(wd && wd->getState() == WarpDrive::WARP_EXECUTING) {
            result *= WARP_RADIUS_MILTIPLIER;
        }
    }
    return result;
}

void Near::remove() {
    if(focus->size() > 0) {
        if(removingIterator != focus->end()) {
            e172::Entity *current = *removingIterator;
            if(ObjectRegistry::getInstance()->exists(current)) {
                Unit *currentUnit = dynamic_cast<Unit*>(current);
                Unit *centerUnit = center->parentUnit();

                if(currentUnit != nullptr && centerUnit != nullptr) {
                    std::list<e172::Entity*>::iterator focusIt = std::find(focus->begin(), focus->end(), current);
                    std::list<e172::Entity*>::iterator originIt = std::find(origin->begin(), origin->end(), current);

                    if(
                        (
                            focusIt != focus->end() &&
                            (currentUnit->position() - centerUnit->position()).module() > (getLocalRadius(centerUnit) + RADIUS_DELTA)
                        ) ||
                        originIt == origin->end()
                    ) {
                        focus->erase(focusIt);
                    }
                }
            } else {
                std::list<e172::Entity*>::iterator focusIt = std::find(focus->begin(), focus->end(), current);
                if (focusIt != focus->end()) focus->erase(focusIt);
            }
        }
        if(++removingIterator == focus->end()) removingIterator = focus->begin();
    }
}

void Near::update() {
    if(center != nullptr) {
        add();
        remove();
    }
}

std::list<e172::Entity *> *Near::entitiesInFocus() {
    return focus;
}
