#ifndef GUICHOICE_H
#define GUICHOICE_H

#include <functional>

#include <additional/e_variant.h>


#include "gui/guimenuelement.h"


class GUIChoice : public GUIMenuElement {
private:
    old::Variant value;
    std::function<void(old::Variant)> set;

public:
    GUIChoice(Controller *player, old::Variant value, std::function<void(old::Variant)> set);
    GUIChoice(Controller *player, std::string label, old::Variant value, std::function<void(old::Variant)> set);
    GUIChoice(Controller *player, IInformative *informative, old::Variant value, std::function<void(old::Variant)> set);

    // GUIElement interface
public:
    bool isSelectable();
    void onEnter();
};

#endif // GUICHOICE_H
