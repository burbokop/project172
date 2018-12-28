#ifndef GUILABEL_H
#define GUILABEL_H

#include "gui/guielement.h"

class GUILabel : public GUIElement {
protected:
    std::string label;
public:
    GUILabel(Controller *player);
    GUILabel(Controller *player, std::string label);

    // GUIElement interface
public:
    std::string getTitle();
    void update();
    void render(Renderer *renderer, Vector *resolution, Event *event);
};

#endif // GUILABEL_H
