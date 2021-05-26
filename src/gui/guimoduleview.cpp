#include "guimoduleview.h"

#include <src/capabilities/modulehandler.h>
#include <src/units/unit.h>
#include <src/capabilities/controller.h>

GUIModuleView::GUIModuleView(const std::string &label) : GUIListView(label) {

}

int GUIModuleView::rowCount() const {
    if(controller()) {
        if(const auto unit = controller()->parentUnit()) {
            if(const auto moduleHandler = unit->capability<ModuleHandler>()) {
                return moduleHandler->modules().size();
            }
        }
    }
    return 0;
}

std::string GUIModuleView::rowText(int index) const {
    if(controller()) {
        if(const auto unit = controller()->parentUnit()) {
            if(const auto& moduleHandler = unit->capability<ModuleHandler>()) {
                const auto modules = moduleHandler->modules();
                if(const auto& module = modules.at(index)) {
                    const auto info = module->info();
                    if(info.size() > 0)
                        return info;

                    return module->loadableId();
                }
            }
        }
    }
    return "[error]";
}

e172::ptr<GUIMenuElement> GUIModuleView::rowElement(int) const {
    return nullptr;
}

e172::Variant GUIModuleView::rowModelData(int) const {
    return e172::Variant();
}
