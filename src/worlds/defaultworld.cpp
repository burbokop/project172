#include "defaultworld.h"


#include <src/capabilities/player.h>
#include <src/capabilities/ai.h>
#include <src/capabilities/docker.h>
#include <src/capabilities/modulehandler.h>
#include <src/ftestobject.h>
#include <src/old_debug.h>
#include <src/engine/math/math.h>
#include <src/units/ship.h>
#include <src/units/unit.h>

#include <src/engine/context.h>
#include <src/engine/physicalobject.h>
#include <src/engine/physicalobject.h>


DefaultWorld::DefaultWorld() {

}

WorldPreset::GenerationResult DefaultWorld::generate(e172::Context *context) {
    GenerationResult result;


    //player1
    Player *player1 = dynamic_cast<Player*>(context->assetProvider()->createLoadable("player1"));
    Ship *playerArmor = dynamic_cast<Ship*>(context->assetProvider()->createLoadable("astro"));
    ModuleHandler *playerArmorModules = new ModuleHandler();
    playerArmorModules->addModule(dynamic_cast<Module*>(context->assetProvider()->createLoadable("mini-engine")));
    playerArmorModules->addModule(dynamic_cast<Module*>(context->assetProvider()->createLoadable("repair-laser")));
    playerArmor->addCapability(playerArmorModules);
    static_cast<Player*>(player1)->setArmor(playerArmor);
    result.controllers.push_back(player1);

    //player2
    Player *player2 = dynamic_cast<Player*>(context->assetProvider()->createLoadable("player2"));
    Ship *playerArmor2 = dynamic_cast<Ship*>(context->assetProvider()->createLoadable("astro"));
    ModuleHandler *playerArmorModules2 = new ModuleHandler();
    playerArmorModules2->addModule(dynamic_cast<Module*>(context->assetProvider()->createLoadable("mini-engine")));
    playerArmorModules2->addModule(dynamic_cast<Module*>(context->assetProvider()->createLoadable("repair-laser")));
    playerArmor2->addCapability(playerArmorModules2);
    player2->setArmor(playerArmor2);
    result.controllers.push_back(player2);


    auto ffo = new FTestObject();
    result.entities.push_back(ffo);


    auto sfo = new FTestObject(ffo);
    result.entities.push_back(sfo);

    ffo->setCOffset({ 0, -20 });
    ffo->setCAngle(-e172::Math::Pi / 2);

    sfo->setCOffset({ 0, 20 });
    sfo->setCAngle(e172::Math::Pi / 2);


    Unit *playerShip = static_cast<Unit*>(context->assetProvider()->createLoadable("sh1"));
    playerShip->resetPhysicsProperties(e172::Vector(100, 100), -0.7);

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
        someShip->addCapability(new Docker());

        someShip->resetPhysicsProperties(e172::Vector(-200, -100), -0.7);
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

            s->resetPhysicsProperties(e172::Vector(-50 + i * 50, 100), -0.7);

            s->addCapability(new AI());
            s->addCapability(new Docker());

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

            //s->addCapability(new Docker());

            if(i == 1) s->addCapability(player2);
            result.entities.push_back(s);
        }
    }


    /*all units 1*/ {
        std::vector<std::string> assetKeys = context->assetProvider()->loadableNames();
        unsigned int i = 0;
        for (std::string key : assetKeys) {
            old::Debug::out("DefaultWorld::generate(assets, units): loading key ( key" + key + " )");
            auto unit = dynamic_cast<Unit*>(context->assetProvider()->createLoadable(key));
            if(unit) {
                unit->resetPhysicsProperties(e172::Vector(static_cast<int>((i + 4) * 64), -200), 0);

                unit->addCapability(new AI());
                ModuleHandler *mhx = new ModuleHandler();
                mhx->addModule(static_cast<Module*>(context->assetProvider()->createLoadable((i == 1) ? "plasma-launcher" : "pistol")));
                mhx->addModule(static_cast<Module*>(context->assetProvider()->createLoadable("engine1")));
                mhx->addModule(static_cast<Module*>(context->assetProvider()->createLoadable("warp-drive1")));

                unit->addCapability(mhx);
                //unit->addCapability(new Docker());

                result.entities.push_back(unit);
                i++;
            }
        }
    }

    /* station 1 */{
        Unit *s = static_cast<Unit*>(context->assetProvider()->createLoadable("st1"));
        s->resetPhysicsProperties(e172::Vector(50, -150), 0);
        result.entities.push_back(s);
    }

    /* station 1 */{
        Unit *s = static_cast<Unit*>(context->assetProvider()->createLoadable("st2"));
        s->resetPhysicsProperties(e172::Vector(50, 150), 0);
        result.entities.push_back(s);
    }


    return result;
}

