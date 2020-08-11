#include "guiradar.h"
#include "gui/guichoice.h"

GUIRadar::GUIRadar(Controller *player) : GUIList (player) {}

GUIRadar::GUIRadar(Controller *player, std::string label) : GUIList (player, label) {}

GUIRadar::GUIRadar(Controller *player, IInformative *informative) : GUIList (player, informative) {}


GUIMenuElement *GUIRadar::forEach(Unit *unit) {
    GUIContainer *container = new GUIContainer(controller(), unit);
    container->addElement(new GUIChoice(controller(), "dock", unit, std::bind(&GUIRadar::onDock, this, std::placeholders::_1)));
    container->addElement(new GUIChoice(controller(), "select", unit, std::bind(&GUIRadar::onSelect, this, std::placeholders::_1)));
    return container;
}


void GUIRadar::onDock(old::Variant value) {
    if(value.isUnit()) {
        Unit *target = value.toUnit();
        Unit *parent = controller()->parent();
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
