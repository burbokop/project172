#include "guiradar.h"



#include "guichoice.h"


GUIRadar::GUIRadar(std::string label) : GUIList (label) {}

GUIRadar::GUIRadar(IInformative *informative) : GUIList (informative) {}


GUIMenuElement *GUIRadar::forEach(Unit *unit) {
    GUIContainer *container = new GUIContainer(unit);
    container->addMenuElement(new GUIChoice("dock", unit->entityId(), std::bind(&GUIRadar::onDock, this, std::placeholders::_1)));
    container->addMenuElement(new GUIChoice("select", unit->entityId(), std::bind(&GUIRadar::onSelect, this, std::placeholders::_1)));
    return container;
}


void GUIRadar::onDock(e172::Variant value) {
    if(value.isNumber()) {
        const auto targetId = value.toNumber<Entity::id_t>();

        Unit *parent = controller()->parentUnit();
        if(targetId && parent) {
            Docker *docker = parent->getDocker();
            if(docker) {
                docker->dock(targetId);
            }
        }
    }
}

void GUIRadar::onSelect(e172::Variant value) {
    controller()->setSelectedEntity(value.toNumber<Entity::id_t>());
}
