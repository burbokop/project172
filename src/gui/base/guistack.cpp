#include "guistack.h"

#include "guicontainer.h"
#include "guilistview.h"
#include <src/abstracteventprovider.h>
#include <src/eventhandler.h>
#include <src/gameapplication.h>

namespace proj172::core {

GUIStack::GUIStack(e172::FactoryMeta &&meta)
    : GUIElement(std::move(meta))
{}

void GUIStack::push(const e172::ptr<GUIElement> &element) {
    if(m_elements.size() > 0) {
        removeChildElement(m_elements.front());
    }

    addChildElement(element);
    if(auto listView = e172::smart_cast<GUIListView>(element))
        listView->setStack(this);

    m_elements.push_back(element);
}

void GUIStack::pop() {
    if(m_elements.size() > 0) {
        if(m_elements.size() == 1) {
            m_reserved = m_elements[0];
        }
        removeChildElement(m_elements.front());
        m_elements.pop_back();
        if(m_elements.size() > 0) {
            addChildElement(m_elements.front());
        }
    }
}

e172::ptr<GUIStack> GUIStack::withFirstElement(const e172::ptr<GUIElement> &element) {
    push(element);
    return this;
}

void GUIStack::proceed(e172::Context *context, e172::EventHandler *eventHandler)
{
    UNUSED(context);
    if(m_elements.size() > 0) {
        m_current = m_elements[m_elements.size() - 1];
    } else {
        m_current = nullptr;
        if(eventHandler->keySinglePressed(e172::ScancodeReturn) && m_reserved) {
            push(m_reserved);
        }
    }

    e172::GameApplication::proceed(m_current, context, eventHandler);
}

void GUIStack::render(e172::Context *context, e172::AbstractRenderer *renderer)
{
    e172::GameApplication::render(m_current, context, renderer);
}

} // namespace proj172::core
