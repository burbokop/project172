#include "guichoice.h"


GUIChoice::GUIChoice(Controller *player, old::Variant value, std::function<void(old::Variant)> set) : GUIMenuElement (player) {
    this->value = value;
    this->set = set;
}

GUIChoice::GUIChoice(Controller *player, std::string label, old::Variant value, std::function<void(old::Variant)> set) : GUIMenuElement (player, label) {
    this->value = value;
    this->set = set;
}

GUIChoice::GUIChoice(Controller *player, IInformative *informative, old::Variant value, std::function<void(old::Variant)> set) : GUIMenuElement (player, informative) {
    this->value = value;
    this->set = set;
}

bool GUIChoice::isSelectable() {
    return true;
}

void GUIChoice::onEnter() {
    set(value);
}
