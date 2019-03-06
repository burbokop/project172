#ifndef GUICHOICE_H
#define GUICHOICE_H

#include <functional>


#include "gui/guibutton.h"


class GUIChoice : public GUIButton {
private:
    Variant value;
    std::function<void(Variant)> set;

public:
    GUIChoice(Controller *player, Variant value, std::function<void(Variant)> set);
    GUIChoice(Controller *player, std::string label, Variant value, std::function<void(Variant)> set);
    GUIChoice(Controller *player, IInformative *informative, Variant value, std::function<void(Variant)> set);

    // GUIButton interface
public:
    bool press();
};

#endif // GUICHOICE_H
