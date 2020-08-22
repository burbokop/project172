#include "worldmanager.h"


#include <engine/context.h>
#include <engine/gameapplication.h>

WorldPresetStrategy::WorldPresetStrategy() {}

std::list<std::string> WorldPresetStrategy::presetNames() const {
    return m_strategy.moduleNames();
}

void WorldPresetStrategy::activatePreset(const std::string &preset) {
    m_strategy.activate(preset);
}

void WorldPresetStrategy::proceed(e172::Context *context, e172::AbstractEventHandler *) {
    if(m_strategy.activeModule() != m_last) {
        m_last = m_strategy.activeModule();
        if(m_last) {
            context->appliation()->clearEntities();
            const auto result = m_last->generate(context);

            for(auto r : result.entities)
                context->appliation()->addEntity(r);
        }
    }
}

void WorldPresetStrategy::render(e172::AbstractRenderer *) {
}
