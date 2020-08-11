#ifndef GUILIST_H
#define GUILIST_H


#include "gui/guicontainer.h"

#include <additional/e_variant.h>


class GUIList : public GUIContainer {
private:
    std::list<Entity*> *array;

    virtual GUIMenuElement *forEach(Unit *unit);

    std::vector<GUIMenuElement*> *informativeToElement(std::list<Entity*> *array);

    void onChoice(old::Variant value);

public:
    GUIList(Controller *player);
    GUIList(Controller *player, std::string label);
    GUIList(Controller *player, IInformative *informative);

    void addArray(std::list<Entity*> *array);

    // GUIElement interface
public:
    void render(e172::AbstractRenderer *renderer);
};

#endif // GUILIST_H
