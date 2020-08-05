#ifndef GUILIST_H
#define GUILIST_H


#include "gui/guicontainer.h"


class GUIList : public GUIContainer {
private:
    std::vector<Worker*> *array;

    virtual GUIMenuElement *forEach(Unit *unit);

    std::vector<GUIMenuElement*> *informativeToElement(std::vector<Worker*> *array);

    void onChoice(Variant value);

public:
    GUIList(Controller *player);
    GUIList(Controller *player, std::string label);
    GUIList(Controller *player, IInformative *informative);

    void addArray(std::vector<Worker*> *array);

    // GUIElement interface
public:
    void render(e172::AbstractRenderer *renderer);
};

#endif // GUILIST_H
