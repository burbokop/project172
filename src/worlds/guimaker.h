#pragma once

#include "world.h"
#include <config/project.h>
#include <src/additional/taskconsole.h>
#include <src/gui/guicombobox.h>
#include <src/near.h>
#include <src/units/camera.h>
#include <src/worldpresetstrategy.h>

namespace proj172::core {

class GUIMaker {
    static inline const std::string manual = "\
            \n---info---\
            \n   --project:\
            \n      name: project172\
            \n      version: " PROJECT_VER "\
            \n      autor: burbokop\
            \n   --control:\
            \n      WASD = fly\
            \n      {\
            \n         arrows,\
            \n         enter,\
            \n         backspace\
            \n      } = menu navigation\
            \n      space = fire\
            \n      F = warp drive\
            ";

    e172::ptr<GUIElement> m_rootElement = nullptr;
    GUIComboBox<std::string> *m_worldComboBox = nullptr;

    e172::ptr<Unit> m_currentOppositeUnit;
public:
    GUIMaker(e172::Context *context,
             Near *radarNear = nullptr,
             const std::shared_ptr<TaskConsole> &console = nullptr);

    void setWorldPresetStrategy(WorldPresetStrategy *worldPresetStrategy);
    e172::ptr<GUIElement> rootElement() const;
};

} // namespace proj172::core
