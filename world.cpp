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


    gui = new GUIContainer(player);
    static_cast<GUIContainer*>(gui)->addElement(new GUILabel(player, "buffalo"));
    static_cast<GUIContainer*>(gui)->addElement(new GUILabel(player, "buffalo2"));
    static_cast<GUIContainer*>(gui)->addElement(new GUILabel(player, "buffalo"));
    static_cast<GUIContainer*>(gui)->addElement(new GUIButton(player, "bufkjhy"));
    static_cast<GUIContainer*>(gui)->addElement(new GUILabel(player, "buf353"));
    static_cast<GUIContainer*>(gui)->addElement(new GUIButton(player, "gog"));
}

Camera *World::getCamera() {
    return this->camera;
}
