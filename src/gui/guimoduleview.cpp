#include "guimoduleview.h"

GUIModuleView::GUIModuleView(const std::string &label) : GUIContainer(label) {

}

void GUIModuleView::proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler) {
    if(controller()) {
        const auto parentUnit = controller()->parentUnit();
        if(parentUnit && updateTimer.check()) {
            clearElements();
            for(Module *module : *parentUnit->getModuleHandler()->getAllModules()) {
                addMenuElement(new GUIMenuElement(module));
            }
        }
    }

    GUIContainer::proceed(context, eventHandler);
}
