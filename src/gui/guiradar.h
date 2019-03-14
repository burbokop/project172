#ifndef GUIRADAR_H
#define GUIRADAR_H

#include "gui/guilist.h"

class GUIRadar : public GUIList {
public:    
    GUIRadar(Controller *player);
    GUIRadar(Controller *player, std::string label);
    GUIRadar(Controller *player, IInformative *informative);

    void onDock(Variant value);
    void onSelect(Variant value);

    // GUIList interface
private:
    GUIMenuElement *forEach(Unit *unit);
};

#endif // GUIRADAR_H
