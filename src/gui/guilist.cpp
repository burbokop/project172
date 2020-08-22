#include "guilist.h"


#include "units/projectile.h"
#include "gui/guichoice.h"
#include "units/camera.h"
#include "objectregistry.h"
#include "debug.h"

std::vector<GUIMenuElement *> GUIList::informativeToElement(std::list<Entity*> *array) {
    std::vector<GUIMenuElement*> result;
    if(array && array->size() > 0) {
        for(Entity *worker : *array) {
            EXISTS(worker) {
                if(worker->isNot<Camera*>() && worker->isNot<Projectile*>()) {
                    Unit *unit = dynamic_cast<Unit*>(worker);
                    if(unit) {
                        result.push_back(forEach(unit));
                    }
                }
            } else {
                Debug::err(Debug::Code::APPEAL_TO_REMOVED, __func__);
            }
        }
    }
    return result;
}


void GUIList::onChoice(old::Variant value) {
    Unit *target = value.toUnit();
    Unit *parent = controller()->parentUnit();
    if(target && parent) {
        Docker *docker = parent->getDocker();
        if(docker) {
            docker->dock(target);
        }
    }
}

GUIMenuElement *GUIList::forEach(Unit *unit) {
    return new GUIChoice(unit, unit, std::bind(&GUIList::onChoice, this, std::placeholders::_1));
}


GUIList::GUIList(std::string label) : GUIContainer (label) {}

GUIList::GUIList(IInformative *informative) : GUIContainer (informative) {}

void GUIList::addArray(std::list<Entity*> *array) {
    this->array = array;
}

void GUIList::render(e172::AbstractRenderer *renderer) {
    m_menuElements = informativeToElement(array);
    this->GUIContainer::render(renderer);
}
