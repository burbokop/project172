#include "world.h"

World::World()
{

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
}

Camera *World::getCamera() {
    return this->camera;
}
