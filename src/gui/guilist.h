#ifndef GUILIST_H
#define GUILIST_H


#include <src/gui/base/guicontainer.h>


class GUIList : public GUIContainer {
private:
    std::list<Entity*> *array;

    virtual GUIMenuElement *forEach(Unit *unit);

    std::vector<GUIMenuElement *> informativeToElement(std::list<Entity*> *array);

    void onChoice(e172::Variant value);

public:
    GUIList(std::string label);
    GUIList(IInformative *informative);

    void addArray(std::list<Entity*> *array);

    // GUIElement interface
public:
    void render(e172::AbstractRenderer *renderer);
};

#endif // GUILIST_H
