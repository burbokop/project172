#include "guilist.h"


#include "units/projectile.h"
#include "gui/guichoice.h"
#include "units/camera.h"
#include "objectregistry.h"
#include "debug.h"

std::vector<GUIMenuElement *> *GUIList::informativeToElement(std::vector<Worker *> *array) {
    std::vector<GUIMenuElement*> *result = new std::vector<GUIMenuElement*>();
    if(array && array->size() > 0) {
        for(Worker *worker : *array) {
            EXISTS(worker) {
                if(worker->isNot<Camera*>() && worker->isNot<Projectile*>()) {
                    Unit *unit = dynamic_cast<Unit*>(worker);
                    if(unit) {
                        result->push_back(forEach(unit));
                    }
                }
            } else {
                Debug::err(Debug::APPEAL_TO_REMOVED, __func__);
            }
        }
    }
    return result;
}


void GUIList::onChoice(Variant value) {
    Unit *target = value.toUnit();
    Unit *parent = player->getParent();
    if(target && parent) {
        Docker *docker = parent->getDocker();
        if(docker) {
            docker->dock(target);
        }
    }
}

GUIMenuElement *GUIList::forEach(Unit *unit) {
    return new GUIChoice(player, unit, unit, std::bind(&GUIList::onChoice, this, std::placeholders::_1));
}

GUIList::GUIList(Controller *player) : GUIContainer (player) {}

GUIList::GUIList(Controller *player, std::string label) : GUIContainer (player, label) {}

GUIList::GUIList(Controller *player, IInformative *informative) : GUIContainer (player, informative) {}

void GUIList::addArray(std::vector<Worker *> *array) {
    this->array = array;
}

void GUIList::render(Renderer *renderer) {
    delete elements;
    elements = informativeToElement(array);
    this->GUIContainer::render(renderer);
}
