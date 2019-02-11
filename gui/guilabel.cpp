#include "guilabel.h"



GUILabel::GUILabel(Controller *player) : GUIElement (player) {
}

GUILabel::GUILabel(Controller *player, std::string label) : GUIElement (player) {
    this->label = label;
}

GUILabel::GUILabel(Controller *player, IInformative *informative) : GUIElement (player) {
    this->informative = informative;
}

std::string GUILabel::getTitle() {
    return informative ? informative->getInfo() : label;
}

void GUILabel::update() {

}

void GUILabel::render(Renderer *renderer, Event *event) {
}
