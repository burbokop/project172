#include "arenaworld.h"


#include "capabilities/player.h"
#include "capabilities/aggressive.h"

#include <engine/context.h>


ArenaWorld::ArenaWorld() {

}

WorldPreset::GenerationResult ArenaWorld::generate(e172::Context *context) {
    GenerationResult result;

    //player1
    Player *player1 = static_cast<Player*>(context->assetProvider()->createLoadable("player1"));
    Ship *playerArmor = static_cast<Ship*>(context->assetProvider()->createLoadable("bsh1"));
    ModuleHandler *playerArmorModules = new ModuleHandler();
    playerArmorModules->addModule(static_cast<Module*>(context->assetProvider()->createLoadable("engine2")));
    playerArmorModules->addModule(static_cast<Module*>(context->assetProvider()->createLoadable("plasma-launcher")));
    playerArmor->addCapability(playerArmorModules);
    static_cast<Player*>(player1)->setArmor(playerArmor);
    result.controllers.push_back(player1);

    //player2
    Player *player2 = static_cast<Player*>(context->assetProvider()->createLoadable("player2"));
    Ship *playerArmor2 = static_cast<Ship*>(context->assetProvider()->createLoadable("bsh2"));
    ModuleHandler *playerArmorModules2 = new ModuleHandler();
    playerArmorModules2->addModule(static_cast<Module*>(context->assetProvider()->createLoadable("engine1")));
    playerArmorModules2->addModule(static_cast<Module*>(context->assetProvider()->createLoadable("mega-launcher")));
    playerArmor2->addCapability(playerArmorModules2);
    player2->setArmor(playerArmor2);
    result.controllers.push_back(player2);


    //player1 ship
    Unit *playerShip = static_cast<Unit*>(context->assetProvider()->createLoadable("sh1"));
    playerShip->place(e172::Vector(100, 100), -0.7);
    playerShip->addCapability(player1);
    ModuleHandler *playerModuleHandler = new ModuleHandler();
    playerModuleHandler->addModule(static_cast<Module*>(context->assetProvider()->createLoadable("pistol")));
    playerModuleHandler->addModule(static_cast<Module*>(context->assetProvider()->createLoadable("engine2")));
    playerModuleHandler->addModule(static_cast<Module*>(context->assetProvider()->createLoadable("warp-drive1")));
    playerShip->addCapability(playerModuleHandler);
    result.entities.push_back(playerShip);

    //player2 ship
    Unit *player2ship = static_cast<Unit*>(context->assetProvider()->createLoadable("sh2"));
    player2ship->place(e172::Vector(0, 100), -0.7);
    ModuleHandler *player2ModuleHandler = new ModuleHandler();
    player2ModuleHandler->addModule(static_cast<Module*>(context->assetProvider()->createLoadable("plasma-launcher")));
    player2ModuleHandler->addModule(static_cast<Module*>(context->assetProvider()->createLoadable("engine1")));
    player2ModuleHandler->addModule(static_cast<Module*>(context->assetProvider()->createLoadable("warp-drive1")));
    player2ship->addCapability(player2ModuleHandler);
    player2ship->addCapability(player2);
    result.entities.push_back(player2ship);



    Movable *unit = dynamic_cast<Movable*>(context->assetProvider()->createLoadable("sh1"));
    unit->place(e172::Vector(), e172::Vector(), e172::Vector(), 0);
    unit->addCapability(new Aggressive(context->entities()));
    ModuleHandler *mh = new ModuleHandler();
    mh->addModule(static_cast<Module*>(context->assetProvider()->createLoadable("pistol")));
    mh->addModule(static_cast<Module*>(context->assetProvider()->createLoadable("engine1")));
    mh->addModule(static_cast<Module*>(context->assetProvider()->createLoadable("warp-drive1")));
    unit->addCapability(mh);
    result.entities.push_back(unit);



    return result;
}
