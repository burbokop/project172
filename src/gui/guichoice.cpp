#include "guichoice.h"


GUIChoice::GUIChoice(Controller *player, Auto value, std::function<void(Auto)> set) : GUIButton (player) {
    this->value = value;
    this->set = set;
}

GUIChoice::GUIChoice(Controller *player, std::string label, Auto value, std::function<void(Auto)> set) : GUIButton (player, label) {
    this->value = value;
    this->set = set;
}

GUIChoice::GUIChoice(Controller *player, IInformative *informative, Auto value, std::function<void(Auto)> set) : GUIButton (player, informative) {
    this->value = value;
    this->set = set;
}


bool GUIChoice::press() {
    set(value);
    return false;
}
