#ifndef GUIRADAR_H
#define GUIRADAR_H

#include "guilist.h"

class GUIRadar : public GUIList {
public:
    GUIRadar(Controller *player);
    GUIRadar(std::string label);
    GUIRadar(IInformative *informative);

    void onDock(e172::Variant value);
    void onSelect(e172::Variant value);

    // GUIList interface
private:
    GUIMenuElement *forEach(Unit *unit);
};

#endif // GUIRADAR_H
