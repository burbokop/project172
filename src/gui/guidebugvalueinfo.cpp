#include "guidebugvalueinfo.h"
#include <math.h>

GUIDebugValueInfo::GUIDebugValueInfo(Controller *player, std::vector<Worker *> *units) {
    m_player = player;
}

void GUIDebugValueInfo::tick(Context *context, Event *event) {

}

void GUIDebugValueInfo::render(e172::AbstractRenderer *renderer) {
    auto res = renderer->resolution();


    const int module = std::round(m_player->parent()->getVelocity().module());

    renderer->drawString(std::to_string(module), e172::Vector(20, res.y() - 30), 0xff8000);
}
