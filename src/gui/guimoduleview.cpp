#include "guimoduleview.h"

#include "../capabilities/controller.h"
#include "../capabilities/modulehandler.h"
#include "../units/unit.h"

namespace proj172::core {

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

                    return module->templateId();
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

} // namespace proj172::core
