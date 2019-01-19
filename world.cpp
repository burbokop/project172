#include "world.h"

GUIElement *World::getGui() const {
    return gui;
}

World::World() {
}

#include <iostream>
void World::init(AssetManager *assets, std::vector<Worker *> *units) {
    this->player = new Player();

    this->camera = new Camera();
    this->camera->setTarget(player);
    units->push_back(camera);


    Unit *playerShip = static_cast<Unit*>(assets->copyAsset("sh1"));
    playerShip->place(Vector(100, 100), 0.5);

    playerShip->addCapability(player);
    ModuleHandler *playerModuleHandler = new ModuleHandler();
    playerModuleHandler->addModule(static_cast<Module*>(assets->copyAsset("pistol")));
    playerModuleHandler->addModule(static_cast<Module*>(assets->copyAsset("engine1")));
    playerModuleHandler->addModule(static_cast<Module*>(assets->copyAsset("warp-drive1")));

    playerShip->addCapability(playerModuleHandler);

    units->push_back(playerShip);


    Unit *someShip = static_cast<Unit*>(assets->copyAsset("sh1"));
    someShip->place(Vector(-200, -100), -0.7);
    units->push_back(someShip);



    {
        gui = new GUIStack();
            GUIContainer *mainMenu = new GUIContainer(player, "main menu");
                GUIContainer *infoMenu = new GUIContainer(player, "info menu");
                infoMenu->addElement(new GUIButton(player, std::string("\
                    \n---info---\
                    \n   --project:\
                    \n      name: project172\
                    \n      version: 0.001\
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
                ")));

                GUIContainer *modulesMenu = new GUIContainer(player, "modules");
                for(Module *module : *playerShip->getModuleHandler()->getAllModules()) {
                    modulesMenu->addElement(new GUILabel(player, module));
                }
            mainMenu->addElement(infoMenu);
            mainMenu->addElement(modulesMenu);
        static_cast<GUIStack*>(gui)->push(mainMenu);
    }
}

Camera *World::getCamera() {
    return this->camera;
}
