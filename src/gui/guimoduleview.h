#ifndef GUIMODULEVIEW_H
#define GUIMODULEVIEW_H

#include "base/guicontainer.h"

class GUIModuleView : public GUIContainer {


    e172::ElapsedTimer updateTimer = e172::ElapsedTimer(2000);
public:
    GUIModuleView(const std::string &label);

    // Entity interface
public:
    virtual void proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler) override;
};

#endif // GUIMODULEVIEW_H
