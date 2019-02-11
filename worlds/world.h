#ifndef WORLD_H
#define WORLD_H

#include <functional>

#include "assetmanager.h"
#include "units/camera.h"
#include "capabilities/player.h"
#include "capabilities/modulehandler.h"
#include "gui/guicontainer.h"
#include "gui/guibutton.h"
#include "gui/guiswitch.h"
#include "gui/guichoice.h"
#include "gui/guistack.h"
#include "gui/guimain.h"

#include "capabilities/ai.h"
#include "additional/effects/anaglyph.h"
#include "additional/fpsmonitor.h"

#include "additional/controllerfinder.h"

class World : public Object {
private:

public:
    World();
    virtual std::vector<Controller*> generate(AssetManager *assets, std::vector<Worker*> *units) = 0;
    virtual std::string getName() = 0;

    virtual ~World();
};

#endif // WORLD_H
