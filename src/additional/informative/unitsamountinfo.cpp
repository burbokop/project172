#include "unitsamountinfo.h"

#include <e172/context.h>
#include <list>

namespace proj172::core {

UnitsAmountInfo::UnitsAmountInfo(e172::Context *context) {
    m_context = context;
}

std::string UnitsAmountInfo::info() const {
    if(m_context)
        return "Units amount: " + std::to_string(m_context->entities().size()) + '\n';
    return "Context missing\n";
}

} // namespace proj172::core
