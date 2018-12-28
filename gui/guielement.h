#ifndef GUIELEMENT_H
#define GUIELEMENT_H

#include "renderer.h"
#include "capabilities/controller.h"

class GUIElement : public Object {
protected:
    static const Uint32 DEFAULT_COLOR = 0xC97878;
    static const Uint32 SELECTED_COLOR = 0xD2BB5F;


    Controller *player;
    int margin = 24;
public:
    GUIElement();
    GUIElement(Controller *player);

    virtual std::string getTitle() = 0;

    virtual void update() = 0;
    virtual void render(Renderer *renderer, Vector *resolution, Event *event) = 0;
    virtual ~GUIElement();
};

#endif // GUIELEMENT_H
