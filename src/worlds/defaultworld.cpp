#include "defaultworld.h"


#include <src/capabilities/player.h>
#include <src/capabilities/ai.h>
#include <src/capabilities/docker.h>
#include <src/debug.h>

#include <src/engine/context.h>


DefaultWorld::DefaultWorld() {

}

WorldPreset::GenerationResult DefaultWorld::generate(e172::Context *context) {
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

    //player2
    Player *player2 = static_cast<Player*>(context->assetProvider()->createLoadable("player2"));
    Ship *playerArmor2 = static_cast<Ship*>(context->assetProvider()->createLoadable("astro"));
    ModuleHandler *playerArmorModules2 = new ModuleHandler();
    playerArmorModules2->addModule(static_cast<Module*>(context->assetProvider()->createLoadable("mini-engine")));
    playerArmorModules2->addModule(static_cast<Module*>(context->assetProvider()->createLoadable("repair-laser")));
    playerArmor2->addCapability(playerArmorModules2);
    player2->setArmor(playerArmor2);
    result.controllers.push_back(player2);



    Unit *playerShip = static_cast<Unit*>(context->assetProvider()->createLoadable("sh1"));
    playerShip->place(e172::Vector(100, 100), -0.7);

    playerShip->addCapability(new Docker());
    playerShip->addCapability(player1);
    ModuleHandler *playerModuleHandler = new ModuleHandler();
    playerModuleHandler->addModule(static_cast<Module*>(context->assetProvider()->createLoadable("pistol")));
    playerModuleHandler->addModule(static_cast<Module*>(context->assetProvider()->createLoadable("engine2")));
    playerModuleHandler->addModule(static_cast<Module*>(context->assetProvider()->createLoadable("warp-drive1")));
    playerModuleHandler->addModule(static_cast<Module*>(context->assetProvider()->createLoadable("thruster1")));

    playerShip->addCapability(playerModuleHandler);

    result.entities.push_back(playerShip);

    /*empty ship*/{
        Unit *someShip = static_cast<Unit*>(context->assetProvider()->createLoadable("sh1"));
        dynamic_cast<Movable*>(someShip)->place(e172::Vector(-200, -100), e172::Vector(-2, -1), e172::Vector(), -0.7);
        result.entities.push_back(someShip);
    }

    /*ships with ai type 1*/ {
        for(int i = 0; i < 3; i++) {
            Unit *s = nullptr;
            switch (i) {
                case 0:
                    s = static_cast<Unit*>(context->assetProvider()->createLoadable("sh1"));
                    break;
                case 1:
                    s = static_cast<Unit*>(context->assetProvider()->createLoadable("sh2"));
                    break;
                case 2:
                    s = static_cast<Unit*>(context->assetProvider()->createLoadable("sh3"));
                    break;
            }

            s->place(e172::Vector(-50 + i * 50, 100), -0.7);

            s->addCapability(new AI());
            ModuleHandler *mx = new ModuleHandler();
            if(i == 1) {
                mx->addModule(static_cast<Module*>(context->assetProvider()->createLoadable("pistol")));
                mx->addModule(static_cast<Module*>(context->assetProvider()->createLoadable("mega-launcher")));
            } else {
                mx->addModule(static_cast<Module*>(context->assetProvider()->createLoadable("pistol")));
            }
            mx->addModule(static_cast<Module*>(context->assetProvider()->createLoadable("engine1")));
            mx->addModule(static_cast<Module*>(context->assetProvider()->createLoadable("warp-drive1")));

            s->addCapability(mx);

            s->addCapability(new Docker());

            if(i == 1) s->addCapability(player2);
            result.entities.push_back(s);
        }
    }


    /*all units 1*/ {
        std::vector<std::string> assetKeys = context->assetProvider()->loadableNames();
        unsigned int i = 0;
        for (std::string key : assetKeys) {
            old::Debug::out("DefaultWorld::generate(assets, units): loading key ( key" + key + " )");
            Movable *unit = dynamic_cast<Movable*>(context->assetProvider()->createLoadable(key));
            if(unit) {
                unit->place(e172::Vector(static_cast<int>((i + 4) * 64), -200), e172::Vector(), e172::Vector(), 0);

                unit->addCapability(new AI());
                ModuleHandler *mhx = new ModuleHandler();
                mhx->addModule(static_cast<Module*>(context->assetProvider()->createLoadable((i == 1) ? "plasma-launcher" : "pistol")));
                mhx->addModule(static_cast<Module*>(context->assetProvider()->createLoadable("engine1")));
                mhx->addModule(static_cast<Module*>(context->assetProvider()->createLoadable("warp-drive1")));

                unit->addCapability(mhx);
                unit->addCapability(new Docker());

                result.entities.push_back(unit);
                i++;
            }
        }
    }

    /* station 1 */{
        Unit *s = static_cast<Unit*>(context->assetProvider()->createLoadable("st1"));
        s->place(e172::Vector(50, -150), 0);
        result.entities.push_back(s);
    }

    /* station 1 */{
        Unit *s = static_cast<Unit*>(context->assetProvider()->createLoadable("st2"));
        s->place(e172::Vector(50, 150), 0);
        result.entities.push_back(s);
    }
    return result;
}

