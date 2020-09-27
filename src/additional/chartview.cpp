#include "chartview.h"

#include <src/engine/graphics/abstractrenderer.h>

double ChartView::coeficient() const {
    return m_coeficient;
}

void ChartView::setCoeficient(double coeficient) {
    m_coeficient = coeficient;
}

e172::Vector ChartView::offset() const {
    return m_offset;
}

void ChartView::setOffset(const e172::Vector &offset) {
    m_offset = offset;
}

size_t ChartView::pointCount() const {
    return m_pointCount;
}

void ChartView::setPointCount(const size_t &pointCount) {
    m_pointCount = pointCount;
}

ChartView::ChartView() {

}

void ChartView::render(e172::AbstractRenderer *renderer) {
    if(m_function) {
        e172::Vector last;
        renderer->drawSquare(m_offset, 2, 0xffffff);
        renderer->drawSquare(m_offset + e172::Vector { m_coeficient, 0 }, 2, 0xffffff);
        for(size_t i = 0; i < m_pointCount; ++i) {
            const double x = i;
            const double y = m_function(x, m_coeficient);
            const e172::Vector pos = { x, -y };

            if((pos - last).cheapModule() < 600) {
                renderer->drawLine(m_offset + last, m_offset + pos, 0xffffff);
            }
            last = pos;
        }
    }
}
