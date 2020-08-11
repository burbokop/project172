#ifndef GUIMINIMAP_H
#define GUIMINIMAP_H

#include "gui/guielement.h"

class GUIMiniMap : public GUIElement {
private:
    unsigned sizeRelation = 6;
    unsigned range = 4098;

    std::list<e172::Entity*> *units;

public:
    GUIMiniMap(Controller *player, std::list<e172::Entity*> *units);


    // Entity interface
public:
    void proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler);
    void render(e172::AbstractRenderer *renderer);
};

#endif // GUIMINIMAP_H
