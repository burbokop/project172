#ifndef GUIELEMENT_H
#define GUIELEMENT_H


#include "capabilities/controller.h"

#include <gui/base/guibaseelement.h>

class GUIElement : public GUIBaseElement {
    int m_margin = 24;
protected:
    enum {
        DefaultColor = 0xC97878,
        SelectedColor = 0xD2BB5F
    };

    void setMargin(int margin);
public:
    GUIElement();

    int margin() const;
};

#endif // GUIELEMENT_H
