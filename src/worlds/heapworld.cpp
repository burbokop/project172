#include "heapworld.h"


#include "capabilities/player.h"
#include "capabilities/aggressive.h"


HeapWorld::HeapWorld()
{

}

std::vector<Controller *> HeapWorld::generate(AssetManager *assets, std::vector<Worker *> *units) {
    std::vector<Controller*> result;

    //player1
    Player *player1 = static_cast<Player*>(assets->copyAsset("player1"));
    Ship *playerArmor = static_cast<Ship*>(assets->copyAsset("astro"));
    ModuleHandler *playerArmorModules = new ModuleHandler();
    playerArmorModules->addModule(static_cast<Module*>(assets->copyAsset("mini-engine")));
    playerArmorModules->addModule(static_cast<Module*>(assets->copyAsset("repair-laser")));
    playerArmor->addCapability(playerArmorModules);
    static_cast<Player*>(player1)->setArmor(playerArmor);
    result.push_back(player1);


    Unit *playerShip = static_cast<Unit*>(assets->copyAsset("sh1"));
    playerShip->place(Vector(), -0.7);
    playerShip->addCapability(player1);
    ModuleHandler *playerModuleHandler = new ModuleHandler();
    playerModuleHandler->addModule(static_cast<Module*>(assets->copyAsset("pistol")));
    playerModuleHandler->addModule(static_cast<Module*>(assets->copyAsset("engine2")));
    playerModuleHandler->addModule(static_cast<Module*>(assets->copyAsset("warp-drive1")));
    playerShip->addCapability(playerModuleHandler);
    units->push_back(playerShip);


    std::vector<std::string> assetKeys = assets->getKeys();
    unsigned int i = 0;
    for (std::string key : assetKeys) {
        for(int j = 0; j < 3; j++) {
            Movable *unit = dynamic_cast<Movable*>(assets->copyAsset(key));
            if(unit) {
                unit->place(Vector::createByAngle(10000, rand()), Vector(), Vector(), 0);

                unit->addCapability(new Aggressive(units));
                ModuleHandler *playerModuleHandler = new ModuleHandler();
                int mul = static_cast<int>(i) * j;
                if(mul % 2 == 0) {
                    playerModuleHandler->addModule(static_cast<Module*>(assets->copyAsset("plasma-launcher")));
                } else if (mul % 3 == 0) {
                    playerModuleHandler->addModule(static_cast<Module*>(assets->copyAsset("mega-launcher")));
                } else {
                    playerModuleHandler->addModule(static_cast<Module*>(assets->copyAsset("pistol")));
                }
                playerModuleHandler->addModule(static_cast<Module*>(assets->copyAsset("engine1")));
                playerModuleHandler->addModule(static_cast<Module*>(assets->copyAsset("warp-drive1")));

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
