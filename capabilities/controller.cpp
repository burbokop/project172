#include "controller.h"

Controller::Controller() {

}

Unit *Controller::getParent() {
    return parent;
}

void Controller::loop(std::vector<Worker *> *others, Event *event) {

}

void Controller::render(Renderer *renderer, Vector offset) {

}
