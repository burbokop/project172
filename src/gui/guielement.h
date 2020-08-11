#ifndef GUIELEMENT_H
#define GUIELEMENT_H


#include "capabilities/controller.h"


class GUIElement : public e172::Entity {
    Controller *m_controller = nullptr;
    int m_margin = 24;
protected:
    static constexpr uint32_t DefaultColor = 0xC97878;
    static constexpr uint32_t SelectedColor = 0xD2BB5F;

    void setMargin(int margin);
public:
    GUIElement();
    GUIElement(Controller *controller);

    virtual ~GUIElement();    
    Controller *controller() const;
    int margin() const;
};

#endif // GUIELEMENT_H
