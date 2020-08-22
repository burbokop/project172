#ifndef GUISETUP_H
#define GUISETUP_H

#include "world.h"

#include <units/camera.h>

#include <near.h>

#include <gui/guimain.h>



class GuiSetup {
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
public:
    GuiSetup(e172::Context *context);
    GUIMain *gui() const;
};

#endif // GUISETUP_H
