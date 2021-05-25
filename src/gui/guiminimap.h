#ifndef GUIMINIMAP_H
#define GUIMINIMAP_H

#include <src/gui/base/guielement.h>

#include <src/utility/ptr.h>

namespace e172 {
    class Entity;
}

class GUIMiniMap : public GUIElement {
private:
    unsigned sizeRelation = 6;
    unsigned range = 4098;

    std::list<e172::ptr<e172::Entity>> m_entities;

public:
    GUIMiniMap();


    // Entity interface
public:
    void proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler);
    void render(e172::AbstractRenderer *renderer);
};

#endif // GUIMINIMAP_H
