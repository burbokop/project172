#include "guilist.h"


#include <src/units/projectile.h>
#include "guichoice.h"
#include <src/units/camera.h>
#include <src/engine/objectregistry.h>
#include <src/old_debug.h>

std::vector<GUIMenuElement *> GUIList::informativeToElements(std::list<Entity*> array) {
    std::vector<GUIMenuElement*> result;
    if(array.size() > 0) {
        for(Entity *entity : array) {
             if(entity == e172::Alive) {
                if(!entity->instanceOf<Camera>() && !entity->instanceOf<Projectile>()) {
                    Unit *unit = dynamic_cast<Unit*>(entity);
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

Near *GUIList::near() const {
    return m_near;
}

void GUIList::setNear(Near *near) {
    m_near = near;
}

GUIMenuElement *GUIList::forEach(Unit *unit) {
    return nullptr;
    return new GUIChoice(unit, unit->entityId(), [this](const e172::Variant &v){
        onChoice(v);
    });
}


GUIList::GUIList(std::string label) : GUIContainer (label) {}

GUIList::GUIList(IInformative *informative) : GUIContainer (informative) {}

void GUIList::render(e172::AbstractRenderer *renderer) {
    if(m_near) {
        terminateElements();
        const auto newMenuElements = informativeToElements(m_near->entitiesInFocus());
        for(const auto& n : newMenuElements)
            addMenuElement(n);
    }
    this->GUIContainer::render(renderer);
}
