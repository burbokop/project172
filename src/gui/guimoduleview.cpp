#include "guimoduleview.h"

GUIModuleView::GUIModuleView(const std::string &label) : GUIListView(label) {

}

int GUIModuleView::rowCount() const {
    if(controller()) {
        if(const auto unit = controller()->parentUnit()) {
            if(const auto moduleHandler = unit->getModuleHandler()) {
                if(const auto modules = moduleHandler->getAllModules()) {
                    return modules->size();
                }
            }
        }
    }
    return 0;
}

std::string GUIModuleView::rowText(int index) const {
    if(controller()) {
        if(const auto unit = controller()->parentUnit()) {
            if(const auto moduleHandler = unit->getModuleHandler()) {
                if(const auto modules = moduleHandler->getAllModules()) {
                    if(const auto module = modules->at(index)) {
                        const auto info = module->info();
                        if(info.size() > 0)
                            return info;

                        return module->loadableId();
                    }
                }
            }
        }
    }
    return "[error]";
}

GUIMenuElement *GUIModuleView::rowElement(int) const {
    return nullptr;
}

//void GUIModuleView::proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler) {
//    if(controller()) {
//        const auto parentUnit = controller()->parentUnit();
//        if(parentUnit && updateTimer.check()) {
//            clearElements();
//            for(Module *module : *parentUnit->getModuleHandler()->getAllModules()) {
//                addMenuElement(new GUIMenuElement(module));
//            }
//        }
//    }
//
//    GUIContainer::proceed(context, eventHandler);
//}
