#include "chartview.h"

#include <src/graphics/abstractrenderer.h>

namespace proj172::core {

void ChartView::render(e172::Context *context, e172::AbstractRenderer *renderer)
{
    if(m_function) {
        e172::Vector<double> last;
        renderer->drawSquare(m_offset, 2, 0xffffff);
        renderer->drawSquare(m_offset + e172::Vector<double>{m_coeficient, 0}, 2, 0xffffff);
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

} // namespace proj172::core
