#include "worldpresetstrategy.h"


#include <src/engine/context.h>
#include <src/engine/gameapplication.h>

WorldPresetStrategy::WorldPresetStrategy() {}

std::list<std::string> WorldPresetStrategy::presetNames() const {
    return m_strategy.moduleNames();
}

void WorldPresetStrategy::activatePreset(const std::string &preset) {
    m_strategy.activate(preset);
}

void WorldPresetStrategy::controllersChanged(const std::function<void (const std::list<Controller *> &)> &callback) {
    controllersChangedCallback = callback;
}

void WorldPresetStrategy::proceed(e172::Context *context, e172::AbstractEventHandler *) {
    if(m_strategy.activeModule() != m_last) {
        m_last = m_strategy.activeModule();
        if(m_last) {
            context->emitMessage(e172::Context::DESTROY_ENTITIES_WITH_TAG, WORLD_TAG)
                ->onDone([context, this]() {
                const auto result = m_last->generate(context);

                for(auto r : result.entities) {
                    r->addTag(WORLD_TAG);
                    context->addEntity(r);
                }

                if(controllersChangedCallback)
                    controllersChangedCallback(result.controllers);
            });
        }
    }
}

void WorldPresetStrategy::render(e172::AbstractRenderer *) {}
