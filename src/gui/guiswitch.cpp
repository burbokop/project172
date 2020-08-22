#include "guiswitch.h"


GUISwitch::GUISwitch(std::function<void()> on,  std::function<void()> off) {
    this->on = on;
    this->off = off;
}

GUISwitch::GUISwitch(std::string label, std::function<void()> on,  std::function<void()> off) : GUIMenuElement (label) {
    this->on = on;
    this->off = off;
}

GUISwitch::GUISwitch(IInformative *informative, std::function<void()> on,  std::function<void()> off) : GUIMenuElement (informative) {
    this->on = on;
    this->off = off;
}

bool GUISwitch::isSelectable() {
    return true;
}

void GUISwitch::onEnter() {
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
}
