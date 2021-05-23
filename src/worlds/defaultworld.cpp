#include "defaultworld.h"


#include <src/capabilities/player.h>
#include <src/capabilities/ai.h>
#include <src/capabilities/docker.h>
#include <src/capabilities/modulehandler.h>
#include <src/ftestobject.h>
#include <src/math/math.h>
#include <src/units/ship.h>
#include <src/units/unit.h>
#include <src/additional/segmentpaiter.h>
#include <src/capabilities/modules/weapon.h>

#include <src/context.h>
#include <src/math/physicalobject.h>


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





    /*
    SegmentPaiter *segmentPaiter = new SegmentPaiter();
    segmentPaiter->resetPhysicsProperties({ 100, 0 }, 0);
    result.entities.push_back(segmentPaiter);


    auto ffo = new FTestObject();
    result.entities.push_back(ffo);
    auto sfo = new FTestObject(ffo);
    result.entities.push_back(sfo);

    ffo->setCOffset({ 0, -50 });
    ffo->setCAngle(-e172::Math::Pi / 2);
    ffo->setColiderVertices({ { -100, 50 }, { 0, -50 }, { 100, 50 } });

    sfo->setCOffset({ 0, 50 });
    sfo->setCAngle(e172::Math::Pi / 2);
    sfo->setColiderVertices({ { -100, 50 }, { 0, -50 }, { 100, 50 } });
    */



    Unit *playerShip = static_cast<Unit*>(context->assetProvider()->createLoadable("sh1"));
    playerShip->resetPhysicsProperties(e172::Vector(100, 100), -0.7);

    auto playerDocker = new Docker();
    playerDocker->addNode({ 0, -20 }, -e172::Math::Pi / 2);
    playerDocker->addNode({ 0, 20 }, e172::Math::Pi / 2);
    playerShip->addCapability(playerDocker);
    playerShip->addCapability(context->assetProvider()->createLoadable<Capability>("ore_reciept"));

    playerShip->addCapability(player1);
    ModuleHandler *playerModuleHandler = new ModuleHandler();
    playerModuleHandler->addModule(context->assetProvider()->createLoadable<Module>("engine2"));
    playerModuleHandler->addModule(context->assetProvider()->createLoadable<Module>("warp-drive1"));
    playerModuleHandler->addModule(context->assetProvider()->createLoadable<Module>("thruster1"));
    const auto pp0 = context->assetProvider()->createLoadable<Weapon>("pistol");
    const auto pp1 = context->assetProvider()->createLoadable<Weapon>("pistol");
    pp0->setOffset({ 0, -4 });
    pp1->setOffset({ 0, 4 });
    playerModuleHandler->addModule(pp0);
    playerModuleHandler->addModule(pp1);

    playerShip->addCapability(playerModuleHandler);

    result.entities.push_back(playerShip);

    /*empty ship*/{
        Unit *someShip = static_cast<Unit*>(context->assetProvider()->createLoadable("sh1"));

        auto someShipDocker = new Docker();
        someShipDocker->addNode({ 0, -20 }, -e172::Math::Pi / 2);
        someShipDocker->addNode({ 0, 20 }, e172::Math::Pi / 2);
        someShip->addCapability(someShipDocker);
        someShip->addCapability(new AI());

        ModuleHandler *someShipModules = new ModuleHandler();
        someShipModules->addModule(context->assetProvider()->createLoadable<Module>("engine2"));
        someShip->addCapability(someShipModules);

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

            auto docker = new Docker();
            docker->addNode({ 0, -20 }, -e172::Math::Pi / 2);
            docker->addNode({ 0, 20 }, e172::Math::Pi / 2);
            s->addCapability(docker);

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
            if(key != "st1") {
                auto unit = dynamic_cast<Unit*>(context->assetProvider()->createLoadable(key));
                if(unit) {
                    unit->resetPhysicsProperties(e172::Vector(static_cast<int>((i + 4) * 64), -200), 0);

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
    }

    /* station 1 */{
        Unit *s = static_cast<Unit*>(context->assetProvider()->createLoadable("st1"));

        auto docker = new Docker();
        docker->addNode({ -50, 0 }, -e172::Math::Pi);
        docker->addNode({ 0, 50 }, 0);
        s->addCapability(docker);

        s->resetPhysicsProperties(e172::Vector(450, -150), 0);
        result.entities.push_back(s);
    }

    /* station 1 */{
        Unit *s = static_cast<Unit*>(context->assetProvider()->createLoadable("st2"));

        auto docker = new Docker();
        docker->addNode({ -40, 0 }, -e172::Math::Pi);
        docker->addNode({ 0, 40 }, 0);
        s->addCapability(docker);

        s->resetPhysicsProperties(e172::Vector(50, 150), 0);
        result.entities.push_back(s);
    }


    return result;
}

