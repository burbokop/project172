#include "unitsamountinfo.h"
#include <list>
#include <src/engine/context.h>

UnitsAmountInfo::UnitsAmountInfo(e172::Context *context) {
    m_context = context;
}

std::string UnitsAmountInfo::getInfo() {
    if(m_context)
        return "Units amount: " + std::to_string(m_context->entities().size()) + '\n';
    return "Context missing\n";
}
