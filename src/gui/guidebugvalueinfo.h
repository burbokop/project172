#ifndef GUIDEBUGVALUEINFO_H
#define GUIDEBUGVALUEINFO_H

#include <gui/base/guielement.h>


class GUIDebugValueInfo : public GUIElement {
    double coef = 6;
    e172::ElapsedTimer timer;
public:
    GUIDebugValueInfo(std::list<Entity*> *);

    // Entity interface
public:
    virtual void proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler) override;
    virtual void render(e172::AbstractRenderer *renderer) override;
};

#endif // GUIDEBUGVALUEINFO_H
