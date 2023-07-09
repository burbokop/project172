#include "heapworld.h"

#include "../capabilities/aggressive.h"
#include "../capabilities/modulehandler.h"
#include "../capabilities/modules/weapon.h"
#include "../capabilities/player.h"
#include "../units/ship.h"
#include <e172/context.h>

namespace proj172::core {

HeapWorld::HeapWorld() {}

WorldPreset::GenerationResult HeapWorld::generate(e172::Context *context) {
    GenerationResult result;

    //player1
    const auto player1 = context->assetProvider()->createLoadable<Player>("player1").unwrap();
    const auto playerArmor = context->assetProvider()->createLoadable<Ship>("astro").unwrap();
    ModuleHandler *playerArmorModules = e172::FactoryMeta::make<ModuleHandler>();
    playerArmorModules->addModule(
        context->assetProvider()->createLoadable<Module>("mini-engine").unwrap());
    playerArmorModules->addModule(
        context->assetProvider()->createLoadable<Module>("repair-laser").unwrap());
    playerArmor->addCapability(playerArmorModules);
    player1->setArmor(playerArmor);
    result.controllers.push_back(player1);

    const auto playerShip = context->assetProvider()->createLoadable<Unit>("sh1").unwrap();
    playerShip->resetPhysicsProperties(e172::Vector<double>(), -0.7);
    playerShip->addCapability(player1);
    ModuleHandler *playerModuleHandler = e172::FactoryMeta::make<ModuleHandler>();
    playerModuleHandler->addModule(
        context->assetProvider()->createLoadable<Module>("pistol").unwrap());
    playerModuleHandler->addModule(
        context->assetProvider()->createLoadable<Module>("engine2").unwrap());
    playerModuleHandler->addModule(
        context->assetProvider()->createLoadable<Module>("warp-drive1").unwrap());
    const auto pp0 = context->assetProvider()->createLoadable<Weapon>("pistol").unwrap();
    const auto pp1 = context->assetProvider()->createLoadable<Weapon>("pistol").unwrap();
    pp0->setOffset({ -4, -6 });
    pp1->setOffset({ -4, 6 });
    playerModuleHandler->addModule(pp0);
    playerModuleHandler->addModule(pp1);

    playerShip->addCapability(playerModuleHandler);
    result.entities.push_back(playerShip);


    std::vector<std::string> assetKeys = context->assetProvider()->loadableNames();
    unsigned int i = 0;
    for (const std::string &key : assetKeys) {
        for(int j = 0; j < 8; j++) {
            const auto unit = context->assetProvider()->createLoadable<Unit>(key).unwrap();
            if(unit) {
                unit->resetPhysicsProperties(e172::Vector<double>::createByAngle(10000, rand()), 0);
                unit->addCapability(e172::FactoryMeta::make<Aggressive>());
                ModuleHandler *playerModuleHandler = e172::FactoryMeta::make<ModuleHandler>();
                int mul = static_cast<int>(i) * j;
                if(mul % 2 == 0) {
                    playerModuleHandler->addModule(
                        context->assetProvider()->createLoadable<Module>("plasma-launcher").unwrap());
                } else if (mul % 3 == 0) {
                    playerModuleHandler->addModule(
                        context->assetProvider()->createLoadable<Module>("mega-launcher").unwrap());
                } else {
                    playerModuleHandler->addModule(
                        context->assetProvider()->createLoadable<Module>("pistol").unwrap());
                }
                playerModuleHandler->addModule(
                    context->assetProvider()->createLoadable<Module>("engine1").unwrap());
                playerModuleHandler->addModule(
                    context->assetProvider()->createLoadable<Module>("warp-drive1").unwrap());

                unit->addCapability(playerModuleHandler);

                result.entities.push_back(unit);
                i++;
            }
        }
    }

    return result;
}

} // namespace proj172::core
