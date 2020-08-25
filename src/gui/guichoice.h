#ifndef GUICHOICE_H
#define GUICHOICE_H

#include <functional>


#include <src/gui/base/guimenuelement.h>


class GUIChoice : public GUIMenuElement {
private:
    e172::Variant value;
    std::function<void(e172::Variant)> set;

public:
    GUIChoice(e172::Variant value, std::function<void(e172::Variant)> set);
    GUIChoice(std::string label, e172::Variant value, std::function<void(e172::Variant)> set);
    GUIChoice(IInformative *informative, e172::Variant value, std::function<void(e172::Variant)> set);

    // GUIElement interface
public:
    bool isSelectable();
    void onEnter();
};

#endif // GUICHOICE_H
