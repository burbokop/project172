#include "guimenuelement.h"

namespace proj172::core {

std::string GUIMenuElement::title() {
    return m_informative ? m_informative->info() : m_label;
}

} // namespace proj172::core
