#include "near.h"


#include "objectregistry.h"


const double Near::RADIUS_DELTA = 16;


Near::Near(std::vector<Worker*> *origin, Controller *center, double radius) {
    this->origin = origin;
    this->focus = new std::vector<Worker*>();
    this->center = center;
    this->radius = radius;
}

void Near::add() {
    //std::cout << "void Near::add()\n";
    if(origin->size() > 0 && center != nullptr) {
        if(addingIterator < origin->size()) {
            Worker *current = origin->at(addingIterator);
            if(ObjectRegistry::getInstance()->exists(current)) {
                Unit *currentUnit = dynamic_cast<Unit*>(current);
                Unit *centerUnit = center->getParent();

                if(
                    currentUnit != nullptr &&
                    centerUnit != nullptr &&
                    currentUnit != centerUnit &&
                    std::find(focus->begin(), focus->end(), current) == focus->end() &&
                    (currentUnit->getPosition() - centerUnit->getPosition()).module() <= radius
                ) {
                    focus->push_back(current);
                }
            }
        }
        if(++addingIterator >= origin->size()) addingIterator = 0;
    }
    //std::cout << "void Near::add() END\n";
}

void Near::remove() {
    //std::cout << "void Near::remove()\n";
    if(focus->size() > 0) {
        if(removingIterator < focus->size()) {
            Worker *current = focus->at(removingIterator);
            if(ObjectRegistry::getInstance()->exists(current)) {
                Unit *currentUnit = dynamic_cast<Unit*>(current);
                Unit *centerUnit = center->getParent();

                if(currentUnit != nullptr && centerUnit != nullptr) {
                    std::vector<Worker*>::iterator focusIt = std::find(focus->begin(), focus->end(), current);
                    std::vector<Worker*>::iterator originIt = std::find(origin->begin(), origin->end(), current);

                    if(
                        (
                            focusIt != focus->end() &&
                            (currentUnit->getPosition() - centerUnit->getPosition()).module() > (radius + RADIUS_DELTA)
                        ) ||
                        originIt == origin->end()
                    ) {
                        focus->erase(focusIt);
                    }
                }
            } else {
                std::vector<Worker*>::iterator focusIt = std::find(focus->begin(), focus->end(), current);
                if (focusIt != focus->end()) focus->erase(focusIt);
            }
        }
        if(++removingIterator >= focus->size()) removingIterator = 0;
    }
    //std::cout << "void Near::remove() END\n";
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
