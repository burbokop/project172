#ifndef GUILABEL_H
#define GUILABEL_H

#include "gui/guielement.h"
#include "iinformative.h"

class GUILabel : public GUIElement {
protected:
    std::string label = "[no data]";
    IInformative *informative = nullptr;
public:
    GUILabel(Controller *player);
    GUILabel(Controller *player, std::string label);
    GUILabel(Controller *player, IInformative *informative);

    // GUIElement interface
public:
    std::string getTitle();
    void update();
    void render(Renderer *renderer, Event *event);
};

#endif // GUILABEL_H
