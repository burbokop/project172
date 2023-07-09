#pragma once

#include "../gui/guicombobox.h"
#include <config/project.h>
#include <e172/utility/ptr.h>

namespace proj172::core {

class Unit;
class TaskConsole;
class WorldPresetStrategy;
class Near;

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
