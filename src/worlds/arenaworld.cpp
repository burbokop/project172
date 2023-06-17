#include "arenaworld.h"


#include <src/capabilities/player.h>
#include <src/capabilities/aggressive.h>
#include <src/capabilities/modulehandler.h>

#include <src/context.h>

#include <src/units/ship.h>

namespace proj172::core {

ArenaWorld::ArenaWorld() {

}

WorldPreset::GenerationResult ArenaWorld::generate(e172::Context *context) {
    GenerationResult result;

    //player1
    auto player1 = context->assetProvider()->createLoadable<Player>("player1").unwrap();
    auto playerArmor = context->assetProvider()->createLoadable<Ship>("bsh1").unwrap();
    ModuleHandler *playerArmorModules = e172::FactoryMeta::make<ModuleHandler>();
    playerArmorModules->addModule(
        context->assetProvider()->createLoadable<Module>("engine2").unwrap());
    playerArmorModules->addModule(
        context->assetProvider()->createLoadable<Module>("plasma-launcher").unwrap());
    playerArmor->addCapability(playerArmorModules);
    player1->setArmor(playerArmor);
    result.controllers.push_back(player1);

    //player2
    auto player2 = context->assetProvider()->createLoadable<Player>("player2").unwrap();
    auto playerArmor2 = context->assetProvider()->createLoadable<Ship>("bsh2").unwrap();
    ModuleHandler *playerArmorModules2 = e172::FactoryMeta::make<ModuleHandler>();
    playerArmorModules2->addModule(
        context->assetProvider()->createLoadable<Module>("engine1").unwrap());
    playerArmorModules2->addModule(
        context->assetProvider()->createLoadable<Module>("mega-launcher").unwrap());
    playerArmor2->addCapability(playerArmorModules2);
    player2->setArmor(playerArmor2);
    result.controllers.push_back(player2);


    //player1 ship
    auto playerShip = context->assetProvider()->createLoadable<Unit>("sh1").unwrap();
    playerShip->resetPhysicsProperties({ 100, 100 }, -0.7);
    playerShip->addCapability(player1);
    ModuleHandler *playerModuleHandler = e172::FactoryMeta::make<ModuleHandler>();
    playerModuleHandler->addModule(
        context->assetProvider()->createLoadable<Module>("pistol").unwrap());
    playerModuleHandler->addModule(
        context->assetProvider()->createLoadable<Module>("engine2").unwrap());
    playerModuleHandler->addModule(
        context->assetProvider()->createLoadable<Module>("warp-drive1").unwrap());
    playerShip->addCapability(playerModuleHandler);
    result.entities.push_back(playerShip);

    //player2 ship
    auto player2ship = context->assetProvider()->createLoadable<Unit>("sh2").unwrap();
    player2ship->resetPhysicsProperties(e172::Vector<double>(0, 100), -0.7);
    ModuleHandler *player2ModuleHandler = e172::FactoryMeta::make<ModuleHandler>();
    player2ModuleHandler->addModule(
        context->assetProvider()->createLoadable<Module>("plasma-launcher").unwrap());
    player2ModuleHandler->addModule(
        context->assetProvider()->createLoadable<Module>("engine1").unwrap());
    player2ModuleHandler->addModule(
        context->assetProvider()->createLoadable<Module>("warp-drive1").unwrap());
    player2ship->addCapability(player2ModuleHandler);
    player2ship->addCapability(player2);
    result.entities.push_back(player2ship);

    auto unit = context->assetProvider()->createLoadable<Unit>("sh1").unwrap();
    unit->resetPhysicsProperties({}, 0);
    unit->addCapability(e172::FactoryMeta::make<Aggressive>());
    ModuleHandler *mh = e172::FactoryMeta::make<ModuleHandler>();
    mh->addModule(context->assetProvider()->createLoadable<Module>("pistol").unwrap());
    mh->addModule(context->assetProvider()->createLoadable<Module>("engine1").unwrap());
    mh->addModule(context->assetProvider()->createLoadable<Module>("warp-drive1").unwrap());
    unit->addCapability(mh);
    result.entities.push_back(unit);

    return result;
}

} // namespace proj172::core
