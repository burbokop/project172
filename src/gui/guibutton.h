#ifndef GUIBUTTON_H
#define GUIBUTTON_H

#include "gui/guilabel.h"
#include "units/ship.h"
#include "additional/stringformer.h"

class GUIButton : public GUILabel {
public:
    GUIButton(Controller *player);
    GUIButton(Controller *player, std::string label);
    GUIButton(Controller *player, IInformative *informative);

    virtual bool press();

    virtual void inc();
    virtual void dec();


    // GUIElement interface
public:
    void update();
};

#endif // GUIBUTTON_H
