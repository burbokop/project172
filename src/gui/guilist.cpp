#include "guilist.h"


#include "units/projectile.h"
#include "gui/guichoice.h"


std::vector<GUIElement *> *GUIList::informativeToElement(std::vector<Worker *> *array) {
    std::vector<GUIElement *> *result = new std::vector<GUIElement *>();

    if(array && array->size() > 0) {
        for(Worker *worker : *array) {
            if(dynamic_cast<Unit*>(worker)) {
                IInformative *info = dynamic_cast<IInformative*>(worker);
                Projectile *proj = dynamic_cast<Projectile*>(worker);
                if(info && !proj) {
                    result->push_back(new GUIChoice(player, info, worker, std::bind(&GUIList::onChoice, this, std::placeholders::_1)));
                }
            }
        }
    }

    return result;
}

#include <iostream>
void GUIList::onChoice(Variant value) {
    std::cout << reinterpret_cast<Unit*>(value.toObject())->getInfo() << "\n";
}

GUIList::GUIList(Controller *player) : GUIContainer (player) {}

GUIList::GUIList(Controller *player, std::string label) : GUIContainer (player, label) {}

GUIList::GUIList(Controller *player, IInformative *informative) : GUIContainer (player, informative) {}

void GUIList::addArray(std::vector<Worker *> *array) {
    this->array = array;
}

void GUIList::render(Renderer *renderer, Event *event) {
    delete elements;
    elements = informativeToElement(array);
    this->GUIContainer::render(renderer, event);
}
