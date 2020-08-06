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
    Player *player1 = static_cast<Player*>(assets->createLoadable("player1"));
    Ship *playerArmor = static_cast<Ship*>(assets->createLoadable("astro"));
    ModuleHandler *playerArmorModules = new ModuleHandler();
    playerArmorModules->addModule(static_cast<Module*>(assets->createLoadable("mini-engine")));
    playerArmorModules->addModule(static_cast<Module*>(assets->createLoadable("repair-laser")));
    playerArmor->addCapability(playerArmorModules);
    static_cast<Player*>(player1)->setArmor(playerArmor);
    result.push_back(player1);

    //player2
    Player *player2 = static_cast<Player*>(assets->createLoadable("player2"));
    Ship *playerArmor2 = static_cast<Ship*>(assets->createLoadable("astro"));
    ModuleHandler *playerArmorModules2 = new ModuleHandler();
    playerArmorModules2->addModule(static_cast<Module*>(assets->createLoadable("mini-engine")));
    playerArmorModules2->addModule(static_cast<Module*>(assets->createLoadable("repair-laser")));
    playerArmor2->addCapability(playerArmorModules2);
    player2->setArmor(playerArmor2);
    result.push_back(player2);



    Unit *playerShip = static_cast<Unit*>(assets->createLoadable("sh1"));
    playerShip->place(e172::Vector(100, 100), -0.7);

    playerShip->addCapability(new Docker());
    playerShip->addCapability(player1);
    ModuleHandler *playerModuleHandler = new ModuleHandler();
    playerModuleHandler->addModule(static_cast<Module*>(assets->createLoadable("pistol")));
    playerModuleHandler->addModule(static_cast<Module*>(assets->createLoadable("engine2")));
    playerModuleHandler->addModule(static_cast<Module*>(assets->createLoadable("warp-drive1")));
    playerModuleHandler->addModule(static_cast<Module*>(assets->createLoadable("thruster1")));

    playerShip->addCapability(playerModuleHandler);

    units->push_back(playerShip);

    /*empty ship*/{
        Unit *someShip = static_cast<Unit*>(assets->createLoadable("sh1"));
        dynamic_cast<Movable*>(someShip)->place(e172::Vector(-200, -100), e172::Vector(-2, -1), e172::Vector(), -0.7);
        units->push_back(someShip);
    }

    /*ships with ai type 1*/ {
        for(int i = 0; i < 3; i++) {
            Unit *s = nullptr;
            switch (i) {
                case 0:
                    s = static_cast<Unit*>(assets->createLoadable("sh1"));
                    break;
                case 1:
                    s = static_cast<Unit*>(assets->createLoadable("sh2"));
                    break;
                case 2:
                    s = static_cast<Unit*>(assets->createLoadable("sh3"));
                    break;
            }

            s->place(e172::Vector(-50 + i * 50, 100), -0.7);

            s->addCapability(new AI());
            ModuleHandler *mx = new ModuleHandler();
            if(i == 1) {
                mx->addModule(static_cast<Module*>(assets->createLoadable("pistol")));
                mx->addModule(static_cast<Module*>(assets->createLoadable("mega-launcher")));
            } else {
                mx->addModule(static_cast<Module*>(assets->createLoadable("pistol")));
            }
            mx->addModule(static_cast<Module*>(assets->createLoadable("engine1")));
            mx->addModule(static_cast<Module*>(assets->createLoadable("warp-drive1")));

            s->addCapability(mx);

            s->addCapability(new Docker());

            if(i == 1) s->addCapability(player2);
            units->push_back(s);
        }
    }


    /*all units 1*/ {
        std::vector<std::string> assetKeys = assets->loadableNames();
        unsigned int i = 0;
        for (std::string key : assetKeys) {
            Debug::out("DefaultWorld::generate(assets, units): loading key ( key" + key + " )");
            Movable *unit = dynamic_cast<Movable*>(assets->createLoadable(key));
            if(unit) {
                unit->place(e172::Vector(static_cast<int>((i + 4) * 64), -200), e172::Vector(), e172::Vector(), 0);

                unit->addCapability(new AI());
                ModuleHandler *mhx = new ModuleHandler();
                mhx->addModule(static_cast<Module*>(assets->createLoadable((i == 1) ? "plasma-launcher" : "pistol")));
                mhx->addModule(static_cast<Module*>(assets->createLoadable("engine1")));
                mhx->addModule(static_cast<Module*>(assets->createLoadable("warp-drive1")));

                unit->addCapability(mhx);
                unit->addCapability(new Docker());

                units->push_back(unit);
                i++;
            }
        }
    }

    /* station 1 */{
        Unit *s = static_cast<Unit*>(assets->createLoadable("st1"));
        s->place(e172::Vector(50, -150), 0);
        units->push_back(s);
    }

    /* station 1 */{
        Unit *s = static_cast<Unit*>(assets->createLoadable("st2"));
        s->place(e172::Vector(50, 150), 0);
        units->push_back(s);
    }
    return result;
}

std::string DefaultWorld::getName() {
    return "gogadoda world";
}
