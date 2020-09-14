#ifndef MODULEHANDLER_H
#define MODULEHANDLER_H

#include <iterator>
#include <algorithm>


#include "modules/module.h"


class ModuleHandler : public Capability {
    std::vector<Module*> modules;
    std::map<std::string, std::vector<Module*>*> *categories = nullptr;
protected:

    bool setParentUnit(Unit *parent) override;
public:
    ModuleHandler();


    void addModule(Module *module);
    void removeModule(Module *module);

    std::vector<Module*> *getAllModules();
    std::vector<Module*> *getModulesByClass(std::string moduleClass);
    bool hasModuleOfClass(std::string moduleClass);

    // Entity interface
public:
    void proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler) override;
    void render(e172::AbstractRenderer *renderer) override;
};

#endif // MODULEHANDLER_H
