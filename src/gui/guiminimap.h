#ifndef GUIMINIMAP_H
#define GUIMINIMAP_H

#include "gui/guielement.h"

class GUIMiniMap : public GUIElement {
private:
    Vector size = Vector(100, 60);

    unsigned range = 4098;

    std::vector<Worker*> *units;

public:
    GUIMiniMap(Controller *player, std::vector<Worker*> *units);

    // GUIElement interface
public:
    std::string getTitle();
    void update();
    void render(Renderer *renderer, Event *event);
};

#endif // GUIMINIMAP_H
