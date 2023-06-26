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

namespace proj172::core {

WorldPreset::GenerationResult DefaultWorld::generate(e172::Context *context) {
    GenerationResult result;

    auto burbokop = new Person("burbokop");
    burbokop->setMoney(500);
    result += generatePlayer(context, "player1", burbokop);

    auto corp = new Person("corp");
    corp->setMoney(1000);
    corp->setIsJuridicalPerson(true);
    result += generateSomeShips(context, 10, corp);
    result += generateSomeStations(context, 10, corp);

    auto merchantGuild = new Person("merchant guild");
    corp->setMoney(2000);
    merchantGuild->setIsJuridicalPerson(true);
    result += generateSomeShips(context, 10, merchantGuild);
    result += generateSomeStations(context, 10, merchantGuild);


    return result;
}

WorldPreset::GenerationResult DefaultWorld::generatePlayer(e172::Context *context, const std::string &templateId, const e172::ptr<Person> &person) {
    GenerationResult result;
    auto player = context->assetProvider()->createLoadable<Player>(templateId).unwrap();
    player->setPerson(person);
    auto playerArmor = context->assetProvider()->createLoadable<Ship>("astro").unwrap();
    ModuleHandler *playerArmorModules = e172::FactoryMeta::make<ModuleHandler>();
    playerArmorModules->addModule(
        context->assetProvider()->createLoadable<Module>("mini-engine").unwrap());
    playerArmorModules->addModule(
        context->assetProvider()->createLoadable<Module>("repair-laser").unwrap());
    playerArmor->addCapability(playerArmorModules);
    player->setArmor(playerArmor);
    result.controllers.push_back(player);

    auto playerShip = context->assetProvider()->createLoadable<Unit>("sh1").unwrap();
    playerShip->resetPhysicsProperties(e172::Vector<double>::createRandom(m_random, 200, 500),
                                       m_random.nextInRange(0., e172::Math::Pi * 2));
    playerShip->setOwnerPerson(person);
    playerShip->addCapability(player);
    ModuleHandler *playerModuleHandler = e172::FactoryMeta::make<ModuleHandler>();
    playerModuleHandler->addModule(
        context->assetProvider()->createLoadable<Module>("engine2").unwrap());
    playerModuleHandler->addModule(
        context->assetProvider()->createLoadable<Module>("warp-drive1").unwrap());
    playerModuleHandler->addModule(
        context->assetProvider()->createLoadable<Module>("thruster1").unwrap());
    const auto pp0 = context->assetProvider()->createLoadable<Weapon>("pistol").unwrap();
    const auto pp1 = context->assetProvider()->createLoadable<Weapon>("pistol").unwrap();
    pp0->setOffset({ 0, -4 });
    pp1->setOffset({ 0, 4 });
    playerModuleHandler->addModule(pp0);
    playerModuleHandler->addModule(pp1);

    playerShip->addCapability(playerModuleHandler);
    playerShip->addCapability(e172::FactoryMeta::make<DebugTransportWareStorage>(
        5000, std::map<std::string, std::size_t>{{"ore", 4000}, {"aaa", 32}}));

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

        if (const auto ship = dynamic_cast<Ship *>(
                context->assetProvider()->createLoadable(id).unwrap())) {
            auto controller = e172::FactoryMeta::make<AI>();
            controller->setPerson(person);
            ship->setOwnerPerson(person);
            ship->addCapability(controller);
            ModuleHandler *someShipModules = e172::FactoryMeta::make<ModuleHandler>();
            someShipModules->addModule(
                context->assetProvider()->createLoadable<Module>("engine2").unwrap());
            ship->addCapability(someShipModules);
            ship->resetPhysicsProperties(e172::Vector<double>::createRandom(m_random, 0, 500),
                                         m_random.nextInRange(0., e172::Math::Pi * 2));
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

        if (const auto station = dynamic_cast<Station *>(
                context->assetProvider()->createLoadable(id).unwrap())) {
            station->setOwnerPerson(person);
            station->addCapability(
                context->assetProvider()->createLoadable<Capability>("ore_reciept").unwrap());
            const auto controller = e172::FactoryMeta::make<Controller>();
            controller->setPerson(person);
            station->addCapability(controller);
            station->resetPhysicsProperties(e172::Vector<double>::createRandom(m_random, 0, 1000),
                                            m_random.nextInRange(0., e172::Math::Pi * 2));
            result.entities.push_back(station);
            ++i;
        }
    }
    return result;
}

} // namespace proj172::core
