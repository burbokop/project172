#include "speedindicator.h"

namespace proj172::core {

void SpeedIndicator::render(e172::AbstractRenderer *renderer)
{
    if (m_lastNumber != m_number) {
        auto top = std::to_string(m_number);
        auto bottom = std::to_string(m_lastNumber);

        renderer->drawString(top, e172::Vector<double>(), 0);
    }
}

} // namespace proj172::core
