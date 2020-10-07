#include "modulehandler.h"


ModuleHandler::ModuleHandler() {}

bool ModuleHandler::setParentUnit(const e172::ptr<Unit> &parent) {
    if(this->Capability::setParentUnit(parent)) {
        if(parent) {
            for(const auto module : m_modules) {
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

std::vector<e172::ptr<Module> > ModuleHandler::modules() {
    return m_modules;
}

std::vector<e172::ptr<Module> > ModuleHandler::modulesOfClass(std::string moduleClass) {
    std::vector<e172::ptr<Module>> result;
    for(const auto module : m_modules) {
        if(module->className() == moduleClass) {
            result.push_back(module);
        }
    }
    return result;
}

bool ModuleHandler::hasModuleOfClass(std::string moduleClass) {
    for(const auto module : m_modules) {
        if(module->className() == moduleClass) {
            return true;
        }
    }
    return false;
}


void ModuleHandler::proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler) {
    for(const auto module : m_modules) {
        module->proceed(context, eventHandler);
    }
}

void ModuleHandler::render(e172::AbstractRenderer *renderer) {
    for(const auto module : m_modules) {
        module->render(renderer);
    }
}

