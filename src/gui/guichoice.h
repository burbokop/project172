#ifndef GUICHOICE_H
#define GUICHOICE_H

#include <functional>


#include "gui/guibutton.h"


class GUIChoice : public GUIButton {
private:
    Auto value;
    std::function<void(Auto)> set;

public:
    GUIChoice(Controller *player, Auto value, std::function<void(Auto)> set);
    GUIChoice(Controller *player, std::string label, Auto value, std::function<void(Auto)> set);
    GUIChoice(Controller *player, IInformative *informative, Auto value, std::function<void(Auto)> set);

    // GUIButton interface
public:
    bool press();
};

#endif // GUICHOICE_H
