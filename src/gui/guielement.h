#ifndef GUIELEMENT_H
#define GUIELEMENT_H


#include "capabilities/controller.h"


class GUIElement : public Object {
protected:
    static const Uint32 DEFAULT_COLOR = 0xC97878;
    static const Uint32 SELECTED_COLOR = 0xD2BB5F;


    Controller *player = nullptr;
    int margin = 24;
public:
    GUIElement();
    GUIElement(Controller *player);

    virtual std::string getTitle() = 0;

    virtual void update() = 0;
    virtual void render(Renderer *renderer, Event *event) = 0;
    virtual ~GUIElement();
};

#endif // GUIELEMENT_H
