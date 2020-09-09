#ifndef GUIMAKER_H
#define GUIMAKER_H

#include "world.h"

#include <src/units/camera.h>

#include <src/near.h>
#include <src/worldpresetstrategy.h>

#include <src/gui/guicombobox.h>
#include <src/gui/guimain.h>



class GUIMaker {
    static inline const std::string manual = "\
            \n---info---\
            \n   --project:\
            \n      name: project172\
            \n      version: 0.004\
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

    GUIMain *m_gui = nullptr;
    GUIComboBox<std::string> *m_worldComboBox = nullptr;
public:
    GUIMaker(e172::Context *context, Near *radarNear = nullptr);
    GUIMain *gui() const;
    void setWorldPresetStrategy(WorldPresetStrategy *worldPresetStrategy);
};

#endif // GUIMAKER_H
