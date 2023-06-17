#include "guilistview.h"

#include "src/abstracteventprovider.h"
#include "src/eventhandler.h"
#include <src/graphics/abstractrenderer.h>

namespace proj172::core {

e172::ptr<GUIStack> GUIListView::stack() const {
    return m_stack;
}

void GUIListView::setStack(const e172::ptr<GUIStack> &stack) {
    m_stack = stack;
}

int GUIListView::verticalInterval() const {
    return m_verticalInterval;
}

void GUIListView::setVerticalInterval(int verticalInterval) {
    m_verticalInterval = verticalInterval;
}

void GUIListView::proceed(e172::Context *context, e172::EventHandler *eventHandler) {
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
                element->enter(context);
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
    e172::Vector<double> pointer;

    if(textFormat().alignment() & e172::TextFormat::AlignLeft) {
        pointer += e172::Vector<double>(margin(), 0);
    } else if(textFormat().alignment() & e172::TextFormat::AlignRight) {
        pointer += e172::Vector<double>(renderer->resolution().x() - margin(), 0);
        m_xOffsets.resize(row_c);
    }

    if(textFormat().alignment() & e172::TextFormat::AlignTop) {
        pointer += e172::Vector<double>(0, margin());
    } else if(textFormat().alignment() & e172::TextFormat::AlignBottom) {
        pointer += e172::Vector<double>(0, renderer->resolution().y() - margin());
    }

    auto textSize = renderer->drawString(title(),
                                         textFormat().alignment() & e172::TextFormat::AlignRight
                                             ? pointer - e172::Vector<double>(m_titleXOffset, 0)
                                             : pointer,
                                         DefaultColor);

    m_titleXOffset = textSize.x();
    pointer += e172::Vector<double>(0, textSize.intY() * 2);
    if(textFormat().alignment() & e172::TextFormat::AlignRight) {
        renderer->drawLine(pointer - e172::Vector(m_titleXOffset, 0.0), pointer, DefaultColor);
    } else {
        renderer->drawLine(pointer, pointer + e172::Vector(m_titleXOffset, 0.0), DefaultColor);
    }
    pointer += e172::Vector<double>(0, textSize.intY());

    for(auto i = 0; i < row_c; ++i) {
        const auto text = rowText(i);
        bool highlite = i == m_selectedIndex && inFocus();
        if(highlite)
            renderer->enableEffect(0);

        const auto xOffset = renderer
                                 ->drawString(text,
                                              textFormat().alignment() & e172::TextFormat::AlignRight
                                                  ? pointer - e172::Vector<double>(m_xOffsets[i], 0)
                                                  : pointer,
                                              highlite ? SelectedColor : DefaultColor)
                                 .x();

        if(textFormat().alignment() & e172::TextFormat::AlignRight) {
            m_xOffsets[i] = xOffset;
        }
        renderer->disableEffect(0);
        pointer += e172::Vector<double>(4, m_verticalInterval);
    }
}

bool GUIListView::isSelectable() {
    return true;
}

bool GUIListView::hasSubElements() {
    return true;
}

} // namespace proj172::core
