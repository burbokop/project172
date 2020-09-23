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
                auto md = rowModelData(m_selectedIndex);
                if(md.isNull())
                    md = modelData();
                element->setModelData(md);
                element->enter();
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
    const auto row_c = rowCount();
    e172::Vector pointer;

    if(textFormat().alignment() & e172::TextFormat::AlignLeft) {
        pointer += e172::Vector(margin(), 0);
    } else if(textFormat().alignment() & e172::TextFormat::AlignRight) {
        pointer += e172::Vector(renderer->resolution().x() - margin(), 0);
        xOffsets.resize(row_c);
    }

    if(textFormat().alignment() & e172::TextFormat::AlignTop) {
        pointer += e172::Vector(0, margin());
    } else if(textFormat().alignment() & e172::TextFormat::AlignBottom) {
        pointer += e172::Vector(0, renderer->resolution().y() - margin());
    }

    auto textSize = renderer->drawString(title(), textFormat().alignment() & e172::TextFormat::AlignRight ? pointer - e172::Vector(titleXOffset, 0) : pointer, DefaultColor);
    titleXOffset = textSize.x();
    pointer += e172::Vector(0, textSize.intY() * 2);
    if(textFormat().alignment() & e172::TextFormat::AlignRight) {
        renderer->drawLine(pointer - e172::Vector(titleXOffset, 0.0), pointer, DefaultColor);
    } else {
        renderer->drawLine(pointer, pointer + e172::Vector(titleXOffset, 0.0), DefaultColor);
    }
    pointer += e172::Vector(0, textSize.intY());

    for(auto i = 0; i < row_c; ++i) {
        const auto text = rowText(i);
        if(i == m_selectedIndex)
            renderer->enableEffect(0);

        const auto xOffset = renderer->drawString(text, textFormat().alignment() & e172::TextFormat::AlignRight ? pointer - e172::Vector(xOffsets[i], 0) : pointer, (i == m_selectedIndex) ? SelectedColor : DefaultColor).x();
        if(textFormat().alignment() & e172::TextFormat::AlignRight) {
            xOffsets[i] = xOffset;
        }
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
