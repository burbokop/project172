#include "arenaworld.h"

ArenaWorld::ArenaWorld() {

}

std::vector<Controller *> ArenaWorld::generate(AssetManager *assets, std::vector<Worker *> *units) {
    std::vector<Controller*> result;

    //player1
    Player *player1 = static_cast<Player*>(assets->copyAsset("player1"));
    Ship *playerArmor = static_cast<Ship*>(assets->copyAsset("bsh1"));
    ModuleHandler *playerArmorModules = new ModuleHandler();
    playerArmorModules->addModule(static_cast<Module*>(assets->copyAsset("engine2")));
    playerArmorModules->addModule(static_cast<Module*>(assets->copyAsset("plasma-launcher")));
    playerArmor->addCapability(playerArmorModules);
    static_cast<Player*>(player1)->setArmor(playerArmor);
    result.push_back(player1);

    //player2
    Player *player2 = static_cast<Player*>(assets->copyAsset("player2"));
    Ship *playerArmor2 = static_cast<Ship*>(assets->copyAsset("bsh2"));
    ModuleHandler *playerArmorModules2 = new ModuleHandler();
    playerArmorModules2->addModule(static_cast<Module*>(assets->copyAsset("engine1")));
    playerArmorModules2->addModule(static_cast<Module*>(assets->copyAsset("mega-launcher")));
    playerArmor2->addCapability(playerArmorModules2);
    player2->setArmor(playerArmor2);
    result.push_back(player2);


    //player1 ship
    Unit *playerShip = static_cast<Unit*>(assets->copyAsset("sh1"));
    playerShip->place(Vector(100, 100), -0.7);
    playerShip->addCapability(player1);
    ModuleHandler *playerModuleHandler = new ModuleHandler();
    playerModuleHandler->addModule(static_cast<Module*>(assets->copyAsset("pistol")));
    playerModuleHandler->addModule(static_cast<Module*>(assets->copyAsset("engine2")));
    playerModuleHandler->addModule(static_cast<Module*>(assets->copyAsset("warp-drive1")));
    playerShip->addCapability(playerModuleHandler);
    units->push_back(playerShip);

    //player2 ship
    Unit *player2ship = static_cast<Unit*>(assets->copyAsset("sh2"));
    player2ship->place(Vector(0, 100), -0.7);
    ModuleHandler *player2ModuleHandler = new ModuleHandler();
    player2ModuleHandler->addModule(static_cast<Module*>(assets->copyAsset("plasma-launcher")));
    player2ModuleHandler->addModule(static_cast<Module*>(assets->copyAsset("engine1")));
    player2ModuleHandler->addModule(static_cast<Module*>(assets->copyAsset("warp-drive1")));
    player2ship->addCapability(playerModuleHandler);
    player2ship->addCapability(player2);
    units->push_back(player2ship);


    return result;
}

std::string ArenaWorld::getName() {
    return "arena world";
}
