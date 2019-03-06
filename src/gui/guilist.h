#ifndef GUILIST_H
#define GUILIST_H


#include "gui/guicontainer.h"


class GUIList : public GUIContainer {
private:
    std::vector<Worker*> *array;

    std::vector<GUIElement*> *informativeToElement(std::vector<Worker*> *array);

    void onChoice(Variant value);

public:
    GUIList(Controller *player);
    GUIList(Controller *player, std::string label);
    GUIList(Controller *player, IInformative *informative);

    void addArray(std::vector<Worker*> *array);

    // GUIElement interface
public:
    void render(Renderer *renderer, Event *event);
};

#endif // GUILIST_H
