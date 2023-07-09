#pragma once

#include <e172/entity.h>
#include <e172/utility/ptr.h>

namespace proj172::core {

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

    GUIElement(e172::FactoryMeta &&meta);
    bool addChildElement(const e172::ptr<GUIElement> &element);
    bool removeChildElement(const e172::ptr<GUIElement> &element);
    void clearChildren();
    void terminateChildren();
    void setController(const e172::ptr<Controller> &controller);

    e172::ptr<GUIElement> parentElement() const { return m_parentElement; }
    e172::ptr<GUIElement> rootElement() const;
    e172::ptr<Controller> controller() const { return m_controller; }
    const std::list<e172::ptr<GUIElement>> &children() const { return m_children; }
    int margin() const { return m_margin; }
    void setMargin(int margin) { m_margin = margin; }
    bool inFocus() const { return m_inFocus; }
    void setInFocus(bool inFocus);

};

} // namespace proj172::core

