#include "defaultworld.h"

DefaultWorld::DefaultWorld() {

}

std::vector<Controller *> DefaultWorld::generate(AssetManager *assets, std::vector<Worker *> *units) {
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

    //player2
    Player *player2 = static_cast<Player*>(assets->copyAsset("player2"));
    Ship *playerArmor2 = static_cast<Ship*>(assets->copyAsset("astro"));
    ModuleHandler *playerArmorModules2 = new ModuleHandler();
    playerArmorModules2->addModule(static_cast<Module*>(assets->copyAsset("mini-engine")));
    playerArmorModules2->addModule(static_cast<Module*>(assets->copyAsset("repair-laser")));
    playerArmor2->addCapability(playerArmorModules2);
    player2->setArmor(playerArmor2);
    result.push_back(player2);



    Unit *playerShip = static_cast<Unit*>(assets->copyAsset("sh1"));
    playerShip->place(Vector(100, 100), -0.7);

    playerShip->addCapability(player1);
    ModuleHandler *playerModuleHandler = new ModuleHandler();
    playerModuleHandler->addModule(static_cast<Module*>(assets->copyAsset("pistol")));
    playerModuleHandler->addModule(static_cast<Module*>(assets->copyAsset("engine2")));
    playerModuleHandler->addModule(static_cast<Module*>(assets->copyAsset("warp-drive1")));

    playerShip->addCapability(playerModuleHandler);

    units->push_back(playerShip);

    /*empty ship*/{
        Unit *someShip = static_cast<Unit*>(assets->copyAsset("sh1"));
        dynamic_cast<Movable*>(someShip)->place(Vector(-200, -100), Vector(-2, -1), Vector(), -0.7);
        units->push_back(someShip);
    }

    /*ships with ai type 1*/ {
        for(int i = 0; i < 3; i++) {
            Unit *s = nullptr;
            switch (i) {
                case 0:
                    s = static_cast<Unit*>(assets->copyAsset("sh1"));
                    break;
                case 1:
                    s = static_cast<Unit*>(assets->copyAsset("sh2"));
                    break;
                case 2:
                    s = static_cast<Unit*>(assets->copyAsset("sh3"));
                    break;
            }

            s->place(Vector(-50 + i * 50, 100), -0.7);

            s->addCapability(new AI());
            ModuleHandler *playerModuleHandler = new ModuleHandler();
            playerModuleHandler->addModule(static_cast<Module*>(assets->copyAsset((i == 1) ? "plasma-launcher" : "pistol")));
            playerModuleHandler->addModule(static_cast<Module*>(assets->copyAsset("engine1")));
            playerModuleHandler->addModule(static_cast<Module*>(assets->copyAsset("warp-drive1")));

            s->addCapability(playerModuleHandler);

            if(i == 1) s->addCapability(player2);
            units->push_back(s);
        }
    }


    /*all units 1*/ {
        std::vector<std::string> assetKeys = assets->getKeys();
        unsigned int i = 0;
        for (std::string key : assetKeys) {
            std::cout << "Default world: loading key: " << key << "\n";
            Movable *unit = dynamic_cast<Movable*>(assets->copyAsset(key));
            if(unit) {
                unit->place(Vector(static_cast<int>((i + 4) * 64), -200), Vector(), Vector(), 0);

                unit->addCapability(new AI());
                ModuleHandler *playerModuleHandler = new ModuleHandler();
                playerModuleHandler->addModule(static_cast<Module*>(assets->copyAsset((i == 1) ? "plasma-launcher" : "pistol")));
                playerModuleHandler->addModule(static_cast<Module*>(assets->copyAsset("engine1")));
                playerModuleHandler->addModule(static_cast<Module*>(assets->copyAsset("warp-drive1")));

                unit->addCapability(playerModuleHandler);

                units->push_back(unit);
                i++;
            }
        }
    }

    /* station 1 */{
        Unit *s = static_cast<Unit*>(assets->copyAsset("st1"));
        s->place(Vector(50, -150), 0);
        units->push_back(s);
    }

    /* station 1 */{
        Unit *s = static_cast<Unit*>(assets->copyAsset("st2"));
        s->place(Vector(50, 150), 0);
        units->push_back(s);
    }
    return result;
}

std::string DefaultWorld::getName() {
    return "gogadoda world";
}
