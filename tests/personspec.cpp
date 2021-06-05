#include "personspec.h"

#include <src/persons/person.h>

#include <src/units/unit.h>

#include <src/capabilities/controller.h>

#include <src/additional/ware/warecontainer.h>


void PersonSpec::buyWareTest() {
    Person person0;
    Controller controller0;
    controller0.setPerson(&person0);
    Unit unit0;
    unit0.addCapability(&controller0);
    TestWareStorage storage0(128, { { "ware0", 32 }, { "ware1", 32 } });
    unit0.addCapability(&storage0);
    const auto wareRef0 = storage0.findRef("ware0");
    person0.setMoney(100);
    storage0.priceTable()->setBuyPrice("ware0", 2);

    Person person1;
    Controller controller1;
    controller1.setPerson(&person1);
    Unit unit1;
    unit1.addCapability(&controller1);
    TestWareStorage storage1(128, { { "ware0", 32 }, { "ware1", 32 } });
    unit1.addCapability(&storage1);
    const auto wareRef1 = storage1.findRef("ware0");
    person1.setMoney(100);

    e172_shouldBeDefined(wareRef0);
    e172_shouldBeDefined(wareRef1);
    e172_shouldEqual(person1.buyWare(wareRef0.value(), &storage1, 16), Person::BuyingSuccess);
    e172_shouldEqual(wareRef0.value().info().count(), 16);
    e172_shouldEqual(wareRef1.value().info().count(), 48);
    e172_shouldEqual(person0.money(), 132);
    e172_shouldEqual(person1.money(), 68);
}

void PersonSpec::sellWareTest() {
    Person person0;
    Controller controller0;
    controller0.setPerson(&person0);
    Unit unit0;
    unit0.addCapability(&controller0);
    TestWareStorage storage0(128, { { "ware0", 32 }, { "ware1", 32 } });
    unit0.addCapability(&storage0);
    const auto wareRef0 = storage0.findRef("ware0");
    person0.setMoney(100);
    storage0.priceTable()->setSellPrice("ware0", 2);

    Person person1;
    Controller controller1;
    controller1.setPerson(&person1);
    Unit unit1;
    unit1.addCapability(&controller1);
    TestWareStorage storage1(128, { { "ware0", 32 }, { "ware1", 32 } });
    unit1.addCapability(&storage1);
    const auto wareRef1 = storage1.findRef("ware0");
    person1.setMoney(100);

    e172_shouldBeDefined(wareRef0);
    e172_shouldBeDefined(wareRef1);
    e172_shouldEqual(person1.sellWare(wareRef1.value(), &storage0, 16), Person::SellingSuccess);
    e172_shouldEqual(wareRef1.value().info().count(), 16);
    e172_shouldEqual(wareRef0.value().info().count(), 48);
    e172_shouldEqual(person1.money(), 132);
    e172_shouldEqual(person0.money(), 68);
}

PersonSpec::TestWareStorage::TestWareStorage(size_t capacity, const std::map<std::string, size_t> &initialWares) {
    m_initialCapacity = capacity;
    m_initialWares = initialWares;
}

size_t PersonSpec::TestWareStorage::setCapacity(size_t capacity) {
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
