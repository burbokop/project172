#include "guilist.h"


#include <src/units/projectile.h>
#include "guichoice.h"
#include <src/units/camera.h>
#include <src/engine/objectregistry.h>
#include <src/debug.h>

std::vector<GUIMenuElement *> GUIList::informativeToElement(std::list<Entity*> *array) {
    std::vector<GUIMenuElement*> result;
    if(array && array->size() > 0) {
        for(Entity *worker : *array) {
            EXISTS(worker) {
                if(!worker->instanceOf<Camera>() && !worker->instanceOf<Projectile>()) {
                    Unit *unit = dynamic_cast<Unit*>(worker);
                    if(unit) {
                        result.push_back(forEach(unit));
                    }
                }
            } else {
                old::Debug::err(old::Debug::Code::APPEAL_TO_REMOVED, __func__);
            }
        }
    }
    return result;
}


void GUIList::onChoice(e172::Variant value) {
    auto target = value.toNumber<e172::Entity::id_t>();
    Unit *parent = controller()->parentUnit();
    if(target && parent) {
        Docker *docker = parent->getDocker();
        if(docker) {
            docker->dock(target);
        }
    }
}

GUIMenuElement *GUIList::forEach(Unit *unit) {
    return nullptr;
    return new GUIChoice(unit, unit->entityId(), [this](const e172::Variant &v){
        onChoice(v);
    });
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
