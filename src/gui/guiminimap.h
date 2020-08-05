#ifndef GUIMINIMAP_H
#define GUIMINIMAP_H

#include "gui/guielement.h"

class GUIMiniMap : public GUIElement {
private:
    unsigned sizeRelation = 6;
    unsigned range = 4098;

    std::vector<Worker*> *units;

public:
    GUIMiniMap(Controller *player, std::vector<Worker*> *units);


    // Worker interface
public:
    void tick(Context *context, Event *event);
    void render(e172::AbstractRenderer *renderer);
};

#endif // GUIMINIMAP_H
