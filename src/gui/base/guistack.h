#ifndef GUISTACK_H
#define GUISTACK_H

#include "guielement.h"

namespace proj172::core {

class GUIStack : public GUIElement {
private:
    std::vector<e172::ptr<GUIElement>> m_elements;
    e172::ptr<GUIElement> m_reserved = nullptr;
    e172::ptr<GUIElement> m_current = nullptr;

public:
    GUIStack(e172::FactoryMeta &&meta);

    void push(const e172::ptr<GUIElement> &element);
    void pop();

    e172::ptr<GUIStack> withFirstElement(const e172::ptr<GUIElement> &element);

    // Entity interface
public:
    void proceed(e172::Context *context, e172::EventHandler *eventHandler);
    void render(e172::Context *context, e172::AbstractRenderer *renderer);
};

} // namespace proj172::core

#endif // GUISTACK_H
