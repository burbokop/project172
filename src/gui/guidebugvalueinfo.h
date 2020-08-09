#ifndef GUIDEBUGVALUEINFO_H
#define GUIDEBUGVALUEINFO_H

#include "guielement.h"

class GUIDebugValueInfo : public GUIElement {
    Controller *m_player = nullptr;
    bool first = true;
    double coef = 6;
    e172::AbstractRenderer::Lens lens;
public:
    GUIDebugValueInfo(Controller *player, std::vector<Worker*> *units);

    // Worker interface
public:
    virtual void tick(Context *context, Event *event) override;
    virtual void render(e172::AbstractRenderer *renderer) override;
};

#endif // GUIDEBUGVALUEINFO_H
