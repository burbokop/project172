#include "guichoice.h"


GUIChoice::GUIChoice(e172::Variant value, std::function<void(e172::Variant)> set) {
    this->value = value;
    this->set = set;
}

GUIChoice::GUIChoice(std::string label, e172::Variant value, std::function<void(e172::Variant)> set) : GUIMenuElement (label) {
    this->value = value;
    this->set = set;
}

GUIChoice::GUIChoice(IInformative *informative, e172::Variant value, std::function<void(e172::Variant)> set) : GUIMenuElement (informative) {
    this->value = value;
    this->set = set;
}

bool GUIChoice::isSelectable() {
    return true;
}

void GUIChoice::enter(e172::Context *) {
    set(value);
}
