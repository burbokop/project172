#ifndef GUICHOICE_H
#define GUICHOICE_H

#include <functional>

#include <additional/e_variant.h>

#include <gui/base/guimenuelement.h>


class GUIChoice : public GUIMenuElement {
private:
    old::Variant value;
    std::function<void(old::Variant)> set;

public:
    GUIChoice(old::Variant value, std::function<void(old::Variant)> set);
    GUIChoice(std::string label, old::Variant value, std::function<void(old::Variant)> set);
    GUIChoice(IInformative *informative, old::Variant value, std::function<void(old::Variant)> set);

    // GUIElement interface
public:
    bool isSelectable();
    void onEnter();
};

#endif // GUICHOICE_H
