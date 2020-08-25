#ifndef GUIDEBUGVALUEINFO_H
#define GUIDEBUGVALUEINFO_H

#include <src/gui/base/guielement.h>


class GUIDebugValueInfo : public GUIElement {
    double coef = 6;
    e172::ElapsedTimer timer;
public:
    GUIDebugValueInfo();

    // Entity interface
public:
    virtual void proceed(e172::Context *, e172::AbstractEventHandler *eventHandler) override;
    virtual void render(e172::AbstractRenderer *renderer) override;
};

#endif // GUIDEBUGVALUEINFO_H
