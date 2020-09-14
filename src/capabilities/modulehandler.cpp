#include "modulehandler.h"


ModuleHandler::ModuleHandler() {

}

bool ModuleHandler::setParentUnit(Unit *parent) {
    if(this->Capability::setParentUnit(parent)) {
        if(parent != nullptr) {
            for(Module *module : modules) {
                module->setParentUnit(parent);
            }
        }
        return true;
    }
    return false;
}


void ModuleHandler::addModule(Module *module) {
    if(module->setParentUnit(this->parentUnit())) {
        modules.push_back(module);
        categories = nullptr;
    }
}

void ModuleHandler::removeModule(Module *module) {
    std::vector<Module*>::iterator pos = std::find(modules.begin(), modules.end(), module);
    if(pos != modules.end()) {
        module->setParentUnit(nullptr);
        modules.erase(pos);
        categories = nullptr;
    }
}

std::vector<Module *> *ModuleHandler::getAllModules() {
    return &this->modules;
}

std::vector<Module *> *ModuleHandler::getModulesByClass(std::string moduleClass) {
    if(categories != nullptr && categories->find(moduleClass) != categories->end()) {
        return categories->at(moduleClass);
    } else {
        std::vector<Module *> *result = new std::vector<Module *>();
        for(Module *module : modules) {
            if(module->className() == moduleClass) {
                result->push_back(module);
            }
        }
        if(result->size() > 0) {
            if(categories == nullptr) categories = new std::map<std::string, std::vector<Module*>*>();
            categories->insert(std::pair<std::string, std::vector<Module*>*>(moduleClass, result));
            return result;
        } else {
            delete result;
            return nullptr;
        }
    }
}

bool ModuleHandler::hasModuleOfClass(std::string moduleClass) {
    for(Module *module : modules) {
        if(module->className() == moduleClass) {
            return true;
        }
    }
    return false;
}


void ModuleHandler::proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler) {
    for(Module *module : modules) {
        module->proceed(context, eventHandler);
    }
}

void ModuleHandler::render(e172::AbstractRenderer *renderer) {
    for(Module *module : modules) {
        module->render(renderer);
    }
}

