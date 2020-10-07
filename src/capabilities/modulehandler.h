#ifndef MODULEHANDLER_H
#define MODULEHANDLER_H

#include <iterator>
#include <algorithm>


#include "modules/module.h"


class ModuleHandler : public Capability {
    std::vector<e172::ptr<Module>> m_modules;
protected:

    bool setParentUnit(const e172::ptr<Unit> &parent) override;
public:
    ModuleHandler();


    void addModule(const e172::ptr<Module> &module);
    void removeModule(const e172::ptr<Module> &module);

    std::vector<e172::ptr<Module>> modules();
    std::vector<e172::ptr<Module>> modulesOfClass(std::string moduleClass);
    bool hasModuleOfClass(std::string moduleClass);

    // Entity interface
public:
    void proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler) override;
    void render(e172::AbstractRenderer *renderer) override;
};

#endif // MODULEHANDLER_H
