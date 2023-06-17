#include "modulehandler.h"

namespace proj172::core {

ModuleHandler::ModuleHandler(e172::FactoryMeta &&meta)
    : Capability(std::move(meta))
{}

bool ModuleHandler::setParentUnit(const e172::ptr<Unit> &parent) {
    if(this->Capability::setParentUnit(parent)) {
        if(parent) {
            for (const auto &module : m_modules) {
                module->setParentUnit(parent);
            }
        }
        return true;
    }
    return false;
}


void ModuleHandler::addModule(const e172::ptr<Module> &module) {
    if(module->setParentUnit(this->parentUnit())) {
        m_modules.push_back(module);
    }
}

void ModuleHandler::removeModule(const e172::ptr<Module> &module) {
    const auto it = std::find(m_modules.begin(), m_modules.end(), module);
    if(it != m_modules.end()) {
        module->setParentUnit(nullptr);
        m_modules.erase(it);
    }
}

void ModuleHandler::proceed(e172::Context *context, e172::EventHandler *eventHandler)
{
    for (const auto &module : m_modules) {
        module->proceed(context, eventHandler);
    }
}

void ModuleHandler::render(e172::AbstractRenderer *renderer) {
    for (const auto &module : m_modules) {
        module->render(renderer);
    }
}

} // namespace proj172::core
