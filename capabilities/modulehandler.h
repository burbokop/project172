#ifndef MODULEHANDLER_H
#define MODULEHANDLER_H

#include <iterator>
#include <algorithm>

#include "capabilities/modules/module.h"

class ModuleHandler : public Capability {
protected:
    std::vector<Module*> modules;
    std::map<std::string, std::vector<Module*>*> *categories;

public:
    ModuleHandler();

    bool setParent(Unit *parent) override;
    void unsetParent() override;

    void addModule(Module *module);
    void removeModule(Module *module);

    std::vector<Module *> *getModulesByClass(std::string moduleClass);
    bool hasModuleOfClass(std::string moduleClass);

    // Worker interface
public:
    void loop(Context *context, Event *event);
    void render(Renderer *renderer, Vector offset);
};

#endif // MODULEHANDLER_H
