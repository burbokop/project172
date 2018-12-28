#include "guilabel.h"



GUILabel::GUILabel(Controller *player) : GUIElement (player) {
}

GUILabel::GUILabel(Controller *player, std::string label) : GUIElement (player) {
    this->label = label;
}


std::string GUILabel::getTitle() {
    return label;
}

void GUILabel::update() {

}

void GUILabel::render(Renderer *renderer, Vector *resolution, Event *event) {
}
