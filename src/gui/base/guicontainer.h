#ifndef GUICONTAINER_H
#define GUICONTAINER_H

#include "guielement.h"

class GUIContainer : public GUIElement {
public:
    GUIContainer();

    // Entity interface
public:
    virtual void proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler) override;
    virtual void render(e172::AbstractRenderer *renderer) override;
};

#endif // GUICONTAINER_H
