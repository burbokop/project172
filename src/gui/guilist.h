#ifndef GUILIST_H
#define GUILIST_H

#include "guicontainer.h"
#include "guichoice.h"
#include "../units/projectile.h"

class GUIList : public GUIContainer {
private:
    std::vector<Worker*> *array;

    bool isArrayChanged (std::vector<Worker *> *array);
    std::vector<GUIElement*> *informativeToElement(std::vector<Worker *> *array);

    void onChoice(Auto value);

public:
    GUIList(Controller *player);
    GUIList(Controller *player, std::string label);
    GUIList(Controller *player, IInformative *informative);

    void addArray(std::vector<Worker *> *array);

    // GUIElement interface
public:
    void render(Renderer *renderer, Event *event);
};

#endif // GUILIST_H
