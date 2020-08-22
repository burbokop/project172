#include "guichoice.h"


GUIChoice::GUIChoice(old::Variant value, std::function<void(old::Variant)> set) {
    this->value = value;
    this->set = set;
}

GUIChoice::GUIChoice(std::string label, old::Variant value, std::function<void(old::Variant)> set) : GUIMenuElement (label) {
    this->value = value;
    this->set = set;
}

GUIChoice::GUIChoice(IInformative *informative, old::Variant value, std::function<void(old::Variant)> set) : GUIMenuElement (informative) {
    this->value = value;
    this->set = set;
}

bool GUIChoice::isSelectable() {
    return true;
}

void GUIChoice::onEnter() {
    set(value);
}
