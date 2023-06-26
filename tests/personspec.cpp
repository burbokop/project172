#include "personspec.h"

#include <src/persons/person.h>
#include <src/units/unit.h>
#include <src/capabilities/controller.h>
#include <src/additional/ware/warecontainer.h>

namespace proj172::core::tests {

void PersonSpec::buyWareTest() {
    Person person0;
    auto controller0 = e172::FactoryMeta::makeUniq<Controller>();
    controller0->setPerson(&person0);
    auto unit0 = e172::FactoryMeta::makeUniq<Unit>();
    unit0->addCapability(std::move(controller0));
    auto storage0 = e172::FactoryMeta::makeUniq<TestWareStorage>(
        128, std::map<std::string, std::size_t>{{"ware0", 32}, {"ware1", 32}});
    const auto wareRef0 = storage0->findRef("ware0");
    person0.setMoney(100);
    storage0->priceTable()->setBuyPrice("ware0", 2);
    unit0->addCapability(std::move(storage0));

    Person person1;
    auto controller1 = e172::FactoryMeta::makeUniq<Controller>();
    controller1->setPerson(&person1);
    auto unit1 = e172::FactoryMeta::makeUniq<Unit>();
    unit1->addCapability(std::move(controller1));
    auto storage1 = e172::FactoryMeta::make<TestWareStorage>(
        128, std::map<std::string, std::size_t>{{"ware0", 32}, {"ware1", 32}});
    const auto wareRef1 = storage1->findRef("ware0");
    unit1->addCapability(storage1);
    person1.setMoney(100);

    e172_shouldBeDefined(wareRef0);
    e172_shouldBeDefined(wareRef1);
    e172_shouldEqual(person1.buyWare(wareRef0.value(), storage1, 16), Person::BuyingSuccess);
    e172_shouldEqual(wareRef0.value().info().count(), 16);
    e172_shouldEqual(wareRef1.value().info().count(), 48);
    e172_shouldEqual(person0.money(), 132);
    e172_shouldEqual(person1.money(), 68);
}

void PersonSpec::sellWareTest() {
    Person person0;
    auto controller0 = e172::FactoryMeta::makeShared<Controller>();
    controller0->setPerson(&person0);
    auto unit0 = e172::FactoryMeta::makeUniq<Unit>();
    unit0->addCapability(controller0);
    auto storage0 = e172::FactoryMeta::makeShared<TestWareStorage>(
        128, std::map<std::string, std::size_t>{{"ware0", 32}, {"ware1", 32}});
    unit0->addCapability(storage0);
    const auto wareRef0 = storage0->findRef("ware0");
    person0.setMoney(100);
    storage0->priceTable()->setSellPrice("ware0", 2);

    Person person1;
    auto controller1 = e172::FactoryMeta::makeShared<Controller>();
    controller1->setPerson(&person1);
    auto unit1 = e172::FactoryMeta::makeUniq<Unit>();
    unit1->addCapability(controller1);
    auto storage1 = e172::FactoryMeta::makeShared<TestWareStorage>(
        128, std::map<std::string, std::size_t>{{"ware0", 32}, {"ware1", 32}});
    unit1->addCapability(storage1);
    const auto wareRef1 = storage1->findRef("ware0");
    person1.setMoney(100);

    e172_shouldBeDefined(wareRef0);
    e172_shouldBeDefined(wareRef1);
    e172_shouldEqual(person1.sellWare(wareRef1.value(), storage0, 16), Person::SellingSuccess);
    e172_shouldEqual(wareRef1.value().info().count(), 16);
    e172_shouldEqual(wareRef0.value().info().count(), 48);
    e172_shouldEqual(person1.money(), 132);
    e172_shouldEqual(person0.money(), 68);
}

size_t PersonSpec::TestWareStorage::setCapacity(size_t capacity)
{
    return e172::smart_cast<WareContainer>(wareContainer())->setCapacity(capacity);
}

e172::ptr<AbstractWareContainer> PersonSpec::TestWareStorage::__wareContainer() const {
    return wareContainer();
}

e172::ptr<AbstractWareContainer> PersonSpec::TestWareStorage::createWareContainer() const {
    auto wc = new WareContainer(m_initialCapacity);
    wc->setAllowedInput(WareContainer::AllAllowed);
    wc->setAllowedOutput(WareContainer::AllAllowed);
    for(const auto& w : m_initialWares) {
        wc->addWare(w.first, w.second);
    }
    return wc;
}

} // namespace proj172::core::tests
