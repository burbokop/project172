#include "guiradar.h"
#include "gui/guichoice.h"


GUIRadar::GUIRadar(std::string label) : GUIList (label) {}

GUIRadar::GUIRadar(IInformative *informative) : GUIList (informative) {}


GUIMenuElement *GUIRadar::forEach(Unit *unit) {
    GUIContainer *container = new GUIContainer(unit);
    container->addMenuElement(new GUIChoice("dock", unit, std::bind(&GUIRadar::onDock, this, std::placeholders::_1)));
    container->addMenuElement(new GUIChoice("select", unit, std::bind(&GUIRadar::onSelect, this, std::placeholders::_1)));
    return container;
}


void GUIRadar::onDock(old::Variant value) {
    if(value.isUnit()) {
        Unit *target = value.toUnit();
        Unit *parent = controller()->parentUnit();
        if(target && parent) {
            Docker *docker = parent->getDocker();
            if(docker) {
                docker->dock(target);
            }
        }
    }
}

void GUIRadar::onSelect(old::Variant value) {
    if(value.isUnit()) {
        Unit *target = value.toUnit();
        if(target) {
            controller()->setSelected(target);
        }
    }
}
