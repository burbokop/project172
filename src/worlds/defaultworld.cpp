#include "defaultworld.h"


#include "capabilities/player.h"
#include "capabilities/ai.h"
#include "capabilities/docker.h"
#include "debug.h"


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
    playerShip->place(e172::Vector(100, 100), -0.7);

    playerShip->addCapability(new Docker());
    playerShip->addCapability(player1);
    ModuleHandler *playerModuleHandler = new ModuleHandler();
    playerModuleHandler->addModule(static_cast<Module*>(assets->copyAsset("pistol")));
    playerModuleHandler->addModule(static_cast<Module*>(assets->copyAsset("engine2")));
    playerModuleHandler->addModule(static_cast<Module*>(assets->copyAsset("warp-drive1")));
    playerModuleHandler->addModule(static_cast<Module*>(assets->copyAsset("thruster1")));

    playerShip->addCapability(playerModuleHandler);

    units->push_back(playerShip);

    /*empty ship*/{
        Unit *someShip = static_cast<Unit*>(assets->copyAsset("sh1"));
        dynamic_cast<Movable*>(someShip)->place(e172::Vector(-200, -100), e172::Vector(-2, -1), e172::Vector(), -0.7);
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

            s->place(e172::Vector(-50 + i * 50, 100), -0.7);

            s->addCapability(new AI());
            ModuleHandler *mx = new ModuleHandler();
            if(i == 1) {
                mx->addModule(static_cast<Module*>(assets->copyAsset("pistol")));
                mx->addModule(static_cast<Module*>(assets->copyAsset("mega-launcher")));
            } else {
                mx->addModule(static_cast<Module*>(assets->copyAsset("pistol")));
            }
            mx->addModule(static_cast<Module*>(assets->copyAsset("engine1")));
            mx->addModule(static_cast<Module*>(assets->copyAsset("warp-drive1")));

            s->addCapability(mx);

            s->addCapability(new Docker());

            if(i == 1) s->addCapability(player2);
            units->push_back(s);
        }
    }


    /*all units 1*/ {
        std::vector<std::string> assetKeys = assets->getKeys();
        unsigned int i = 0;
        for (std::string key : assetKeys) {
            Debug::out("DefaultWorld::generate(assets, units): loading key ( key" + key + " )");
            Movable *unit = dynamic_cast<Movable*>(assets->copyAsset(key));
            if(unit) {
                unit->place(e172::Vector(static_cast<int>((i + 4) * 64), -200), e172::Vector(), e172::Vector(), 0);

                unit->addCapability(new AI());
                ModuleHandler *mhx = new ModuleHandler();
                mhx->addModule(static_cast<Module*>(assets->copyAsset((i == 1) ? "plasma-launcher" : "pistol")));
                mhx->addModule(static_cast<Module*>(assets->copyAsset("engine1")));
                mhx->addModule(static_cast<Module*>(assets->copyAsset("warp-drive1")));

                unit->addCapability(mhx);
                unit->addCapability(new Docker());

                units->push_back(unit);
                i++;
            }
        }
    }

    /* station 1 */{
        Unit *s = static_cast<Unit*>(assets->copyAsset("st1"));
        s->place(e172::Vector(50, -150), 0);
        units->push_back(s);
    }

    /* station 1 */{
        Unit *s = static_cast<Unit*>(assets->copyAsset("st2"));
        s->place(e172::Vector(50, 150), 0);
        units->push_back(s);
    }
    return result;
}

std::string DefaultWorld::getName() {
    return "gogadoda world";
}
