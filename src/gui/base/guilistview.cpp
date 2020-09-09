#include "guilistview.h"

#include <src/engine/abstracteventhandler.h>

#include <src/engine/graphics/abstractrenderer.h>

GUIStack *GUIListView::stack() const {
    return m_stack;
}

void GUIListView::setStack(GUIStack *stack) {
    m_stack = stack;
}

int GUIListView::verticalInterval() const {
    return m_verticalInterval;
}

void GUIListView::setVerticalInterval(int verticalInterval) {
    m_verticalInterval = verticalInterval;
}

GUIListView::GUIListView(const std::string &title) : GUIMenuElement(title) {}

void GUIListView::proceed(e172::Context *, e172::AbstractEventHandler *eventHandler) {
    if(eventHandler->keySinglePressed(e172::ScancodeDown)) {
        if(++m_selectedIndex >= rowCount()) {
            m_selectedIndex = 0;
        }
    } else if(eventHandler->keySinglePressed(e172::ScancodeUp)) {
        if(--m_selectedIndex < 0) {
            m_selectedIndex = rowCount() - 1;
        }
    } else if(eventHandler->keySinglePressed(e172::ScancodeReturn)) {
        if(m_selectedIndex >= 0 && m_selectedIndex < rowCount()) {
            if(const auto element = rowElement(m_selectedIndex)) {
                element->onEnter();
                if(element->hasSubElements() && m_stack) {
                    m_stack->push(element);
                }
            }
        }
    } else if(m_stack && eventHandler->keySinglePressed(e172::ScancodeBackSpace)) {
        m_stack->pop();
    }
}

void GUIListView::render(e172::AbstractRenderer *renderer) {
    e172::Vector pointer = e172::Vector(margin(), margin());
    std::string title = getTitle();
    auto textSize = renderer->drawString(title, pointer, DefaultColor);
    pointer += e172::Vector(0, textSize.intY() * 2);
    renderer->drawLine(pointer, pointer + e172::Vector(textSize.intX(), 0.0), DefaultColor);
    pointer += e172::Vector(0, textSize.intY());

    for(auto i = 0, count = rowCount(); i < count; ++i) {
        const auto text = rowText(i);
        if(i == m_selectedIndex)
            renderer->enableEffect(0);

        renderer->drawString(text, pointer, (i == m_selectedIndex) ? SelectedColor : DefaultColor);
        renderer->disableEffect(0);
        pointer += e172::Vector(4, m_verticalInterval);
    }
}

bool GUIListView::isSelectable() {
    return true;
}

bool GUIListView::hasSubElements() {
    return true;
}
