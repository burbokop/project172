#include "heapworld.h"


#include "capabilities/player.h"
#include "capabilities/aggressive.h"


HeapWorld::HeapWorld()
{

}

std::vector<Controller *> HeapWorld::generate(e172::AssetProvider *assets, std::list<e172::Entity *> *units) {
    std::vector<Controller*> result;

    //player1
    Player *player1 = static_cast<Player*>(assets->createLoadable("player1"));
    Ship *playerArmor = static_cast<Ship*>(assets->createLoadable("astro"));
    ModuleHandler *playerArmorModules = new ModuleHandler();
    playerArmorModules->addModule(static_cast<Module*>(assets->createLoadable("mini-engine")));
    playerArmorModules->addModule(static_cast<Module*>(assets->createLoadable("repair-laser")));
    playerArmor->addCapability(playerArmorModules);
    static_cast<Player*>(player1)->setArmor(playerArmor);
    result.push_back(player1);


    Unit *playerShip = static_cast<Unit*>(assets->createLoadable("sh1"));
    playerShip->place(e172::Vector(), -0.7);
    playerShip->addCapability(player1);
    ModuleHandler *playerModuleHandler = new ModuleHandler();
    playerModuleHandler->addModule(static_cast<Module*>(assets->createLoadable("pistol")));
    playerModuleHandler->addModule(static_cast<Module*>(assets->createLoadable("engine2")));
    playerModuleHandler->addModule(static_cast<Module*>(assets->createLoadable("warp-drive1")));
    playerShip->addCapability(playerModuleHandler);
    units->push_back(playerShip);


    std::vector<std::string> assetKeys = assets->loadableNames();
    unsigned int i = 0;
    for (std::string key : assetKeys) {
        for(int j = 0; j < 32; j++) {
            Movable *unit = dynamic_cast<Movable*>(assets->createLoadable(key));
            if(unit) {
                unit->place(e172::Vector::createByAngle(10000, rand()), e172::Vector(), e172::Vector(), 0);

                unit->addCapability(new Aggressive(units));
                ModuleHandler *playerModuleHandler = new ModuleHandler();
                int mul = static_cast<int>(i) * j;
                if(mul % 2 == 0) {
                    playerModuleHandler->addModule(static_cast<Module*>(assets->createLoadable("plasma-launcher")));
                } else if (mul % 3 == 0) {
                    playerModuleHandler->addModule(static_cast<Module*>(assets->createLoadable("mega-launcher")));
                } else {
                    playerModuleHandler->addModule(static_cast<Module*>(assets->createLoadable("pistol")));
                }
                playerModuleHandler->addModule(static_cast<Module*>(assets->createLoadable("engine1")));
                playerModuleHandler->addModule(static_cast<Module*>(assets->createLoadable("warp-drive1")));

                unit->addCapability(playerModuleHandler);

                units->push_back(unit);
                i++;
            }
        }
    }

    return result;
}

std::string HeapWorld::getName() {
    return "heap world";
}
