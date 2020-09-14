#include "modulehandler.h"


ModuleHandler::ModuleHandler() {

}

bool ModuleHandler::setParentUnit(Unit *parent) {
    if(this->Capability::setParentUnit(parent)) {
        if(parent != nullptr) {
            for(Module *module : m_modules) {
                module->setParentUnit(parent);
            }
        }
        return true;
    }
    return false;
}


void ModuleHandler::addModule(Module *module) {
    if(module->setParentUnit(this->parentUnit())) {
        m_modules.push_back(module);
    }
}

void ModuleHandler::removeModule(Module *module) {
    const auto it = std::find(m_modules.begin(), m_modules.end(), module);
    if(it != m_modules.end()) {
        module->setParentUnit(nullptr);
        m_modules.erase(it);
    }
}

std::vector<Module *> ModuleHandler::modules() {
    return m_modules;
}

std::vector<Module *> ModuleHandler::modulesOfClass(std::string moduleClass) {
    std::vector<Module *> result;
    for(Module *module : m_modules) {
        if(module->className() == moduleClass) {
            result.push_back(module);
        }
    }
    return result;
}

bool ModuleHandler::hasModuleOfClass(std::string moduleClass) {
    for(Module *module : m_modules) {
        if(module->className() == moduleClass) {
            return true;
        }
    }
    return false;
}


void ModuleHandler::proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler) {
    for(Module *module : m_modules) {
        module->proceed(context, eventHandler);
    }
}

void ModuleHandler::render(e172::AbstractRenderer *renderer) {
    for(Module *module : m_modules) {
        module->render(renderer);
    }
}

