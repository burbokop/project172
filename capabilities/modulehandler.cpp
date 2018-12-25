#include "modulehandler.h"


ModuleHandler::ModuleHandler() {

}

void ModuleHandler::setParent(Unit *parent) {
    for(Module *module : modules) {
        module->setParent(parent);
    }
    this->Capability::setParent(parent);
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

#include <iostream>
std::vector<Module *> *ModuleHandler::getModulesByClass(std::string moduleClass) {
    std::cout << "part1\n";
    if(categories != nullptr && categories->find(moduleClass) != categories->end()) {
        std::cout << "part2\n";
        return categories->at(moduleClass);
    } else {
        std::cout << "part3\n";
        std::vector<Module *> *result = new std::vector<Module *>();
        std::cout << "part3.1\n";
        for(Module *module : modules) {
            if(module->getClass() == moduleClass) {
                result->push_back(module);
            }
        }
        std::cout << "part4\n";
        if(result->size() > 0) {
            std::cout << "part4.1\n";
            if(categories == nullptr) categories = new std::map<std::string, std::vector<Module*>*>();
            std::cout << "part4.2\n";
            //categories->at(moduleClass) = result;
            categories->insert(std::pair<std::string, std::vector<Module*>*>(moduleClass, result));
            std::cout << "part5\n";
            return result;
        } else {
            delete result;
            return nullptr;
        }
    }
}


void ModuleHandler::loop(Context *context, Event *event)
{

}

void ModuleHandler::render(Renderer *renderer, Vector offset)
{

}



