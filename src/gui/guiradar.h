#ifndef GUIRADAR_H
#define GUIRADAR_H

#include "gui/guilist.h"

class GUIRadar : public GUIList {
public:    
    GUIRadar(Controller *player);
    GUIRadar(std::string label);
    GUIRadar(IInformative *informative);

    void onDock(old::Variant value);
    void onSelect(old::Variant value);

    // GUIList interface
private:
    GUIMenuElement *forEach(Unit *unit);
};

#endif // GUIRADAR_H
