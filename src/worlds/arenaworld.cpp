#include "arenaworld.h"


#include "capabilities/player.h"
#include "capabilities/aggressive.h"


ArenaWorld::ArenaWorld() {

}

std::vector<Controller *> ArenaWorld::generate(AssetProvider *assets, std::vector<Worker *> *units) {
    std::vector<Controller*> result;

    //player1
    Player *player1 = static_cast<Player*>(assets->createLoadable("player1"));
    Ship *playerArmor = static_cast<Ship*>(assets->createLoadable("bsh1"));
    ModuleHandler *playerArmorModules = new ModuleHandler();
    playerArmorModules->addModule(static_cast<Module*>(assets->createLoadable("engine2")));
    playerArmorModules->addModule(static_cast<Module*>(assets->createLoadable("plasma-launcher")));
    playerArmor->addCapability(playerArmorModules);
    static_cast<Player*>(player1)->setArmor(playerArmor);
    result.push_back(player1);

    //player2
    Player *player2 = static_cast<Player*>(assets->createLoadable("player2"));
    Ship *playerArmor2 = static_cast<Ship*>(assets->createLoadable("bsh2"));
    ModuleHandler *playerArmorModules2 = new ModuleHandler();
    playerArmorModules2->addModule(static_cast<Module*>(assets->createLoadable("engine1")));
    playerArmorModules2->addModule(static_cast<Module*>(assets->createLoadable("mega-launcher")));
    playerArmor2->addCapability(playerArmorModules2);
    player2->setArmor(playerArmor2);
    result.push_back(player2);


    //player1 ship
    Unit *playerShip = static_cast<Unit*>(assets->createLoadable("sh1"));
    playerShip->place(e172::Vector(100, 100), -0.7);
    playerShip->addCapability(player1);
    ModuleHandler *playerModuleHandler = new ModuleHandler();
    playerModuleHandler->addModule(static_cast<Module*>(assets->createLoadable("pistol")));
    playerModuleHandler->addModule(static_cast<Module*>(assets->createLoadable("engine2")));
    playerModuleHandler->addModule(static_cast<Module*>(assets->createLoadable("warp-drive1")));
    playerShip->addCapability(playerModuleHandler);
    units->push_back(playerShip);

    //player2 ship
    Unit *player2ship = static_cast<Unit*>(assets->createLoadable("sh2"));
    player2ship->place(e172::Vector(0, 100), -0.7);
    ModuleHandler *player2ModuleHandler = new ModuleHandler();
    player2ModuleHandler->addModule(static_cast<Module*>(assets->createLoadable("plasma-launcher")));
    player2ModuleHandler->addModule(static_cast<Module*>(assets->createLoadable("engine1")));
    player2ModuleHandler->addModule(static_cast<Module*>(assets->createLoadable("warp-drive1")));
    player2ship->addCapability(player2ModuleHandler);
    player2ship->addCapability(player2);
    units->push_back(player2ship);



    Movable *unit = dynamic_cast<Movable*>(assets->createLoadable("sh1"));
    unit->place(e172::Vector(), e172::Vector(), e172::Vector(), 0);
    unit->addCapability(new Aggressive(units));
    ModuleHandler *mh = new ModuleHandler();
    mh->addModule(static_cast<Module*>(assets->createLoadable("pistol")));
    mh->addModule(static_cast<Module*>(assets->createLoadable("engine1")));
    mh->addModule(static_cast<Module*>(assets->createLoadable("warp-drive1")));
    unit->addCapability(mh);
    units->push_back(unit);



    return result;
}

std::string ArenaWorld::getName() {
    return "arena world";
}
