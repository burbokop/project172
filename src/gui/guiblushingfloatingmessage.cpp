#include "guiblushingfloatingmessage.h"

#include "../units/unit.h"
#include <e172/graphics/abstractrenderer.h>
#include <e172/math/math.h>

namespace proj172::core {

void GUIBlushingFloatingMessage::render(e172::AbstractRenderer *renderer) {
    const std::uint32_t color = m_value < 0
                                    ? 0xff0000
                                    : (0xff0000
                                       | static_cast<uint32_t>(
                                           e172::Math::map<std::uint32_t>(m_value, 0, 80, 0, 0xff)
                                           << 8));

    renderer->drawString(
                title(),
                m_parent->position() + renderer->offset() + e172::Vector(0.0, horisontalOffset()),
                color,
                e172::TextFormat(e172::TextFormat::AlignDefault, DEFAULT_FONT_SIZE)
                );
}

} // namespace proj172::core
