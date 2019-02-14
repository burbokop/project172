#include "near.h"


const double Near::RADIUS_DELTA = 16;


Near::Near(std::vector<Worker *> *origin, Controller *center, double radius) {
    this->origin = origin;
    this->focus = new std::vector<Worker *>();
    this->center =center;
    this->radius = radius;
}

void Near::add() {
    if(origin->size() > 0) {
        if(addingIterator < origin->size()) {
            Unit *currentUnit = dynamic_cast<Unit*>(origin->at(addingIterator));
            Unit *centerUnit = center->getParent();

            if(
                currentUnit != nullptr &&
                currentUnit != centerUnit &&
                std::find(focus->begin(), focus->end(), currentUnit) == focus->end() &&
                (currentUnit->getPosition() - centerUnit->getPosition()).module() <= radius
            ) {
                focus->push_back(currentUnit);
            }
        }
        if(++addingIterator >= origin->size()) addingIterator = 0;
    }
}

void Near::remove() {
    if(focus->size() > 0) {
        if(removingIterator < focus->size()) {
            Unit *currentUnit = dynamic_cast<Unit*>(focus->at(removingIterator));
            Unit *centerUnit = center->getParent();

            std::vector<Worker *>::iterator focusIt = std::find(focus->begin(), focus->end(), currentUnit);
            std::vector<Worker *>::iterator originIt = std::find(origin->begin(), origin->end(), currentUnit);
            if(
                currentUnit != nullptr && (
                    (
                        focusIt != focus->end() &&
                        (currentUnit->getPosition() - centerUnit->getPosition()).module() > (radius + RADIUS_DELTA)
                    ) ||
                    originIt == origin->end()
                )
            ) {
                focus->erase(focusIt);
            }
        }
        if(++removingIterator >= focus->size()) removingIterator = 0;
    }
}


void Near::update() {
    if(center != nullptr) {
        add();
        remove();
    }
}

std::vector<Worker *> *Near::getFocus() {
    return focus;
}
