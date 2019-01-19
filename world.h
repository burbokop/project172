#ifndef WORLD_H
#define WORLD_H


#include "assetmanager.h"
#include "units/camera.h"
#include "capabilities/player.h"
#include "capabilities/modulehandler.h"
#include "gui/guicontainer.h"
#include "gui/guibutton.h"
#include "gui/guistack.h"

class World : public Object
{
private:
    Camera *camera;
    Controller *player;
    GUIElement *gui;

public:
    World();
    void init(AssetManager *assets, std::vector<Worker*> *units);
    Camera *getCamera();
    GUIElement *getGui() const;
};

#endif // WORLD_H
