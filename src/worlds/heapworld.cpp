#include "heapworld.h"


#include <src/capabilities/player.h>
#include <src/capabilities/aggressive.h>

#include <src/engine/context.h>


HeapWorld::HeapWorld() {}

WorldPreset::GenerationResult HeapWorld::generate(e172::Context *context) {
    GenerationResult result;

    //player1
    Player *player1 = static_cast<Player*>(context->assetProvider()->createLoadable("player1"));
    Ship *playerArmor = static_cast<Ship*>(context->assetProvider()->createLoadable("astro"));
    ModuleHandler *playerArmorModules = new ModuleHandler();
    playerArmorModules->addModule(static_cast<Module*>(context->assetProvider()->createLoadable("mini-engine")));
    playerArmorModules->addModule(static_cast<Module*>(context->assetProvider()->createLoadable("repair-laser")));
    playerArmor->addCapability(playerArmorModules);
    static_cast<Player*>(player1)->setArmor(playerArmor);
    result.controllers.push_back(player1);


    Unit *playerShip = static_cast<Unit*>(context->assetProvider()->createLoadable("sh1"));
    playerShip->place(e172::Vector(), -0.7);
    playerShip->addCapability(player1);
    ModuleHandler *playerModuleHandler = new ModuleHandler();
    playerModuleHandler->addModule(static_cast<Module*>(context->assetProvider()->createLoadable("pistol")));
    playerModuleHandler->addModule(static_cast<Module*>(context->assetProvider()->createLoadable("engine2")));
    playerModuleHandler->addModule(static_cast<Module*>(context->assetProvider()->createLoadable("warp-drive1")));
    playerShip->addCapability(playerModuleHandler);
    result.entities.push_back(playerShip);


    std::vector<std::string> assetKeys = context->assetProvider()->loadableNames();
    unsigned int i = 0;
    for (std::string key : assetKeys) {
        for(int j = 0; j < 32; j++) {
            Movable *unit = dynamic_cast<Movable*>(context->assetProvider()->createLoadable(key));
            if(unit) {
                unit->place(e172::Vector::createByAngle(10000, rand()), e172::Vector(), e172::Vector(), 0);

                unit->addCapability(new Aggressive(context->entities()));
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

std::string HeapWorld::getName() {
    return "heap world";
}
