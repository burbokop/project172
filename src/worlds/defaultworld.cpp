#include "defaultworld.h"


#include <src/capabilities/player.h>
#include <src/capabilities/ai.h>
#include <src/capabilities/docker.h>
#include <src/capabilities/modulehandler.h>
#include <src/capabilities/warestorage.h>
#include <src/ftestobject.h>
#include <src/math/math.h>
#include <src/units/ship.h>
#include <src/units/station.h>
#include <src/units/unit.h>
#include <src/additional/segmentpaiter.h>
#include <src/capabilities/modules/weapon.h>

#include <src/context.h>
#include <src/debug.h>
#include <src/math/physicalobject.h>


DefaultWorld::DefaultWorld() {}

WorldPreset::GenerationResult DefaultWorld::generate(e172::Context *context) {
    GenerationResult result;

    result += generatePlayer(context, "player1", new Person("burbokop"));

    auto corp = new Person("corp");
    corp->setIsJuridicalPerson(true);
    result += generateSomeShips(context, 10, corp);
    result += generateSomeStations(context, 10, corp);


    auto merchantGuild = new Person("merchant guild");
    merchantGuild->setIsJuridicalPerson(true);
    result += generateSomeShips(context, 10, merchantGuild);
    result += generateSomeStations(context, 10, merchantGuild);


    return result;
}

WorldPreset::GenerationResult DefaultWorld::generatePlayer(e172::Context *context, const std::string &templateId, const e172::ptr<Person> &person) {
    GenerationResult result;
    auto player = context->assetProvider()->createLoadable<Player>(templateId);
    player->setPerson(person);
    auto playerArmor = context->assetProvider()->createLoadable<Ship>("astro");
    ModuleHandler *playerArmorModules = new ModuleHandler();
    playerArmorModules->addModule(context->assetProvider()->createLoadable<Module>("mini-engine"));
    playerArmorModules->addModule(context->assetProvider()->createLoadable<Module>("repair-laser"));
    playerArmor->addCapability(playerArmorModules);
    player->setArmor(playerArmor);
    result.controllers.push_back(player);

    auto playerShip = context->assetProvider()->createLoadable<Unit>("sh1");
    playerShip->resetPhysicsProperties(e172::Vector::createRandom(500), e172::Math::randDouble() * e172::Math::Pi * 2);
    playerShip->setOwnerPerson(person);
    playerShip->addCapability(player);
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
    playerShip->addCapability(new DebugTransportWareStorage(100, { { "goga", 12 }, { "aaa", 32 } }));

    result.entities.push_back(playerShip);
    return result;
}

WorldPreset::GenerationResult DefaultWorld::generateSomeShips(e172::Context *context, size_t cnt, const e172::ptr<Person> &person) {
    GenerationResult result;
    const auto names = context->assetProvider()->loadableNames();
    size_t i = 0;
    for(const auto& id : names) {
        if(i >= cnt)
            return result;

        if(const auto ship = context->assetProvider()->createLoadable<Ship>(id)) {
            auto controller = new AI();
            controller->setPerson(person);
            ship->setOwnerPerson(person);
            ship->addCapability(controller);
            ModuleHandler *someShipModules = new ModuleHandler();
            someShipModules->addModule(context->assetProvider()->createLoadable<Module>("engine2"));
            ship->addCapability(someShipModules);
            ship->resetPhysicsProperties(e172::Vector::createRandom(500), e172::Math::randDouble() * e172::Math::Pi * 2);
            result.entities.push_back(ship);
            ++i;
        }
    }
    return result;
}

WorldPreset::GenerationResult DefaultWorld::generateSomeStations(e172::Context *context, size_t cnt, const e172::ptr<Person> &person) {
    GenerationResult result;
    const auto names = context->assetProvider()->loadableNames();
    size_t i = 0;
    for(const auto& id : names) {
        if(i >= cnt)
            return result;

        auto station = context->assetProvider()->createLoadable<Station>(id);
        if(station) {
            station->setOwnerPerson(person);
            station->addCapability(context->assetProvider()->createLoadable<Capability>("ore_reciept"));
            station->resetPhysicsProperties(e172::Vector::createRandom(500), e172::Math::randDouble() * e172::Math::Pi * 2);
            result.entities.push_back(station);
            ++i;
        }
    }
    return result;
}

