#include "guichoice.h"


GUIChoice::GUIChoice(Controller *player, Variant value, std::function<void(Variant)> set) : GUIMenuElement (player) {
    this->value = value;
    this->set = set;
}

GUIChoice::GUIChoice(Controller *player, std::string label, Variant value, std::function<void(Variant)> set) : GUIMenuElement (player, label) {
    this->value = value;
    this->set = set;
}

GUIChoice::GUIChoice(Controller *player, IInformative *informative, Variant value, std::function<void(Variant)> set) : GUIMenuElement (player, informative) {
    this->value = value;
    this->set = set;
}

bool GUIChoice::isSelectable() {
    return true;
}

void GUIChoice::onEnter() {
    set(value);
}
