#ifndef GUISWITCH_H
#define GUISWITCH_H

#include <functional>


#include "gui/guibutton.h"


class GUISwitch : public GUIButton {
private:
    std::function<void()> on;
    std::function<void()> off;
    bool enabled = false;

public:
    GUISwitch(Controller *player, std::function<void()> on = nullptr,  std::function<void()> off = nullptr);
    GUISwitch(Controller *player, std::string label, std::function<void()> on = nullptr,  std::function<void()> off = nullptr);
    GUISwitch(Controller *player, IInformative *informative, std::function<void()> on = nullptr,  std::function<void()> off = nullptr);

    // GUIButton interface
public:
    bool press();
};

#endif // GUISWITCH_H
