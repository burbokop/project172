#ifndef GUICHOICE_H
#define GUICHOICE_H

#include <functional>


#include "gui/guimenuelement.h"


class GUIChoice : public GUIMenuElement {
private:
    Variant value;
    std::function<void(Variant)> set;

public:
    GUIChoice(Controller *player, Variant value, std::function<void(Variant)> set);
    GUIChoice(Controller *player, std::string label, Variant value, std::function<void(Variant)> set);
    GUIChoice(Controller *player, IInformative *informative, Variant value, std::function<void(Variant)> set);

    // GUIElement interface
public:
    bool isSelectable();
    void onEnter();
};

#endif // GUICHOICE_H
