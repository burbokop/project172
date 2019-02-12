#include "guiswitch.h"


GUISwitch::GUISwitch(Controller *player, std::function<void()> on,  std::function<void()> off) : GUIButton (player) {
    this->on = on;
    this->off = off;
}

GUISwitch::GUISwitch(Controller *player, std::string label, std::function<void()> on,  std::function<void()> off) : GUIButton (player, label) {
    this->on = on;
    this->off = off;
}

GUISwitch::GUISwitch(Controller *player, IInformative *informative, std::function<void()> on,  std::function<void()> off) : GUIButton (player, informative) {
    this->on = on;
    this->off = off;
}

bool GUISwitch::press() {
    if(on != nullptr) {
        if(off != nullptr) {
            if(!enabled) {
                on();
                enabled = true;
            } else {
                off();
                enabled = false;
            }
        } else {
            on();
        }
    }
    return false;
}
