#ifndef GUIBLUSHINGFLOATINGMESSAGE_H
#define GUIBLUSHINGFLOATINGMESSAGE_H


#include <src/gui/guifloatingmessage.h>


class GUIBlushingFloatingMessage : public GUIFloatingMessage {
private:
    int value;

public:
    GUIBlushingFloatingMessage(const e172::ptr<Unit> &parent);
    GUIBlushingFloatingMessage(const e172::ptr<Unit> &parent, int value);
    GUIBlushingFloatingMessage(const e172::ptr<Unit> &parent, IInformative *informative);


    // GUIElement interface
public:
    void render(e172::AbstractRenderer *renderer);
};

#endif // GUIBLUSHINGFLOATINGMESSAGE_H
