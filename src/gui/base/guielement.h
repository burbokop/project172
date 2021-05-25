#ifndef GUIELEMENT_H
#define GUIELEMENT_H

#include <src/entity.h>
#include <src/utility/ptr.h>

class Controller;
class GUIElement : public e172::Entity {
    e172::ptr<GUIElement> m_parentElement;
    e172::ptr<Controller> m_controller;
    std::list<e172::ptr<GUIElement>> m_children;

    int m_margin = 24;
    bool m_inFocus = true;
public:
    enum {
        DefaultColor = 0xC97878,
        SelectedColor = 0xD2BB5F
    };

    e172::ptr<GUIElement> withChildren(const std::list<e172::ptr<GUIElement>>& children);

    GUIElement();
    bool addChildElement(const e172::ptr<GUIElement> &element);
    bool removeChildElement(const e172::ptr<GUIElement> &element);
    void clearChildren();
    void terminateChildren();
    void setController(const e172::ptr<Controller> &controller);

    e172::ptr<GUIElement> parentElement() const;
    e172::ptr<GUIElement> rootElement() const;
    e172::ptr<Controller> controller() const;
    std::list<e172::ptr<GUIElement>> children() const;
    int margin() const;
    void setMargin(int margin);
    bool inFocus() const;
    void setInFocus(bool inFocus);

};

#endif // GUIELEMENT_H
