#include "guibutton.h"

GUIButton::GUIButton(Controller *player) : GUILabel (player) {
}

GUIButton::GUIButton(Controller *player, std::string label) : GUILabel (player, label) {
}

GUIButton::GUIButton(Controller *player, IInformative *informative) : GUILabel (player, informative) {
}

bool GUIButton::press() {
    return 0;
}

void GUIButton::update() {
}
