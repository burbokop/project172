#include "heapworld.h"


#include <src/capabilities/player.h>
#include <src/capabilities/aggressive.h>
#include <src/capabilities/modulehandler.h>

#include <src/engine/context.h>

#include <src/units/ship.h>

#include <src/capabilities/modules/weapon.h>


HeapWorld::HeapWorld() {}

WorldPreset::GenerationResult HeapWorld::generate(e172::Context *context) {
    GenerationResult result;

    //player1
    Player *player1 = dynamic_cast<Player*>(context->assetProvider()->createLoadable("player1"));
    Ship *playerArmor = dynamic_cast<Ship*>(context->assetProvider()->createLoadable("astro"));
    ModuleHandler *playerArmorModules = new ModuleHandler();
    playerArmorModules->addModule(dynamic_cast<Module*>(context->assetProvider()->createLoadable("mini-engine")));
    playerArmorModules->addModule(dynamic_cast<Module*>(context->assetProvider()->createLoadable("repair-laser")));
    playerArmor->addCapability(playerArmorModules);
    dynamic_cast<Player*>(player1)->setArmor(playerArmor);
    result.controllers.push_back(player1);


    Unit *playerShip = static_cast<Unit*>(context->assetProvider()->createLoadable("sh1"));
    playerShip->resetPhysicsProperties(e172::Vector(), -0.7);
    playerShip->addCapability(player1);
    ModuleHandler *playerModuleHandler = new ModuleHandler();
    playerModuleHandler->addModule(context->assetProvider()->createLoadable<Module>("pistol"));
    playerModuleHandler->addModule(context->assetProvider()->createLoadable<Module>("engine2"));
    playerModuleHandler->addModule(context->assetProvider()->createLoadable<Module>("warp-drive1"));
    const auto pp0 = context->assetProvider()->createLoadable<Weapon>("pistol");
    const auto pp1 = context->assetProvider()->createLoadable<Weapon>("pistol");
    pp0->setOffset({ -4, -6 });
    pp1->setOffset({ -4, 6 });
    playerModuleHandler->addModule(pp0);
    playerModuleHandler->addModule(pp1);

    playerShip->addCapability(playerModuleHandler);
    result.entities.push_back(playerShip);


    std::vector<std::string> assetKeys = context->assetProvider()->loadableNames();
    unsigned int i = 0;
    for (std::string key : assetKeys) {
        for(int j = 0; j < 8; j++) {
            auto unit = dynamic_cast<Unit*>(context->assetProvider()->createLoadable(key));
            if(unit) {
                unit->resetPhysicsProperties(e172::Vector::createByAngle(10000, rand()), 0);

                unit->addCapability(new Aggressive());
                ModuleHandler *playerModuleHandler = new ModuleHandler();
                int mul = static_cast<int>(i) * j;
                if(mul % 2 == 0) {
                    playerModuleHandler->addModule(static_cast<Module*>(context->assetProvider()->createLoadable("plasma-launcher")));
                } else if (mul % 3 == 0) {
                    playerModuleHandler->addModule(static_cast<Module*>(context->assetProvider()->createLoadable("mega-launcher")));
                } else {
                    playerModuleHandler->addModule(static_cast<Module*>(context->assetProvider()->createLoadable("pistol")));
                }
                playerModuleHandler->addModule(static_cast<Module*>(context->assetProvider()->createLoadable("engine1")));
                playerModuleHandler->addModule(static_cast<Module*>(context->assetProvider()->createLoadable("warp-drive1")));

                unit->addCapability(playerModuleHandler);

                result.entities.push_back(unit);
                i++;
            }
        }
    }

    return result;
}
