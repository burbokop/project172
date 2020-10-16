#ifndef GUIBASEELEMENT_H
#define GUIBASEELEMENT_H

#include <src/entity.h>

class Controller;
class GUIBaseElement : public e172::Entity {
    GUIBaseElement *m_parentElement = nullptr;
    Controller *m_controller = nullptr;
    std::list<GUIBaseElement*> m_children;
public:
    GUIBaseElement();
    bool addChildElement(GUIBaseElement *element);
    bool removeChildElement(GUIBaseElement *element);
    void clearChildren();
    void terminateChildren();
    void setController(Controller *controller);

    GUIBaseElement *parentElement() const;
    GUIBaseElement *rootElement() const;
    Controller *controller() const;
    std::list<GUIBaseElement *> children() const;
};

#endif // GUIBASEELEMENT_H
