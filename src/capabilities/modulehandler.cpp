#include "modulehandler.h"


ModuleHandler::ModuleHandler() {

}

bool ModuleHandler::setParent(Unit *parent) {
    if(this->Capability::setParent(parent)) {
        for(Module *module : modules) {
            module->setParent(parent);
        }
        return true;
    }
    return false;
}

void ModuleHandler::unsetParent() {
    for(Module *module : modules) {
        module->unsetParent();
    }
    this->Capability::unsetParent();
}

void ModuleHandler::addModule(Module *module) {
    if(module->setParent(this->parent)) {
        modules.push_back(module);
        categories = nullptr;
    }
}

void ModuleHandler::removeModule(Module *module) {
    std::vector<Module*>::iterator pos = std::find(modules.begin(), modules.end(), module);
    if(pos != modules.end()) {
        module->unsetParent();
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
            if(module->getAssetClass() == moduleClass) {
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
        if(module->getAssetClass() == moduleClass) {
            return true;
        }
    }
    return false;
}


void ModuleHandler::tick(Context *context, Event *event) {
    for(Module *module : modules) {
        module->tick(context, event);
    }
}

void ModuleHandler::render(Renderer *renderer) {
    for(Module *module : modules) {
        module->render(renderer);
    }
}

