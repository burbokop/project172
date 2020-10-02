#ifndef GUICHOICE_H
#define GUICHOICE_H

#include <functional>


#include <src/gui/base/guimenuelement.h>

class GUIChoice : public GUIMenuElement {
private:
    e172::Variant value;
    std::function<void(e172::Variant)> set;

public:
    [[deprecated("Use GUIButton instead")]]
    GUIChoice(e172::Variant value, std::function<void(e172::Variant)> set);
    [[deprecated("Use GUIButton instead")]]
    GUIChoice(std::string label, e172::Variant value, std::function<void(e172::Variant)> set);
    [[deprecated("Use GUIButton instead")]]
    GUIChoice(IInformative *informative, e172::Variant value, std::function<void(e172::Variant)> set);

    // GUIElement interface
public:
    bool isSelectable() override;
    void enter(e172::Context *) override;
};

#endif // GUICHOICE_H
