#ifndef GUIDEBUGVALUEINFO_H
#define GUIDEBUGVALUEINFO_H

#include "guielement.h"

class GUIDebugValueInfo : public GUIElement {
    Controller *m_player = nullptr;
    double coef = 6;
    Timer timer;
public:
    GUIDebugValueInfo(Controller *player, std::vector<Worker*> *units);

    // Worker interface
public:
    virtual void tick(Context *context, e172::AbstractEventHandler *eventHandler) override;
    virtual void render(e172::AbstractRenderer *renderer) override;
};

#endif // GUIDEBUGVALUEINFO_H
