#include "person.h"

#include <src/units/unit.h>

#include <src/capabilities/controller.h>

#include <src/math/math.h>

std::string Person::name() const {
    return m_name;
}

void Person::setName(const std::string &name) {
    m_name = name;
}

e172::ptr<Person> Person::hostPerson() const {
    return m_hostPerson;
}

std::set<e172::ptr<Person> > Person::employees() const {
    return m_employees;
}

bool Person::addEmployee(const e172::ptr<Person> &employee) {
    if(employee != this) {
        if(m_employees.insert(employee).second) {
            employee->m_hostPerson = this;
            return true;
        }
    }
    return false;
}

bool Person::removeEmployee(const e172::ptr<Person> &employee) {
    if(m_employees.erase(employee)) {
        employee->m_hostPerson = nullptr;
        return true;
    }
    return false;
}

bool Person::isJuridicalPerson() const {
    return m_isJuridicalPerson;
}

void Person::setIsJuridicalPerson(bool isJuridicalPerson) {
    m_isJuridicalPerson = isJuridicalPerson;
}

int64_t Person::money() const {
    return m_money;
}

void Person::setMoney(const int64_t &money) {
    m_money = money;
}

bool Person::isOwnerOfWare(const WareStorage::WareRef &wareRef) {
    return wareRef.storage().fold<bool>([this](WareStorage* storage) {
        return storage->parentUnit().fold<bool>([this](Unit *unit) {
            return unit->capability<Controller>().fold<bool>([this](Controller* controller) {
                return controller->person() == this;
            });
        });
    });
}

Person::BuyStatus Person::buyWare(const WareStorage::WareRef &wareRef, const e172::ptr<WareStorage> &destination, size_t count) {
    return wareRef.storage().fold<BuyStatus>([&](WareStorage* sellerStorage){
        return sellerStorage->parentUnit().fold<BuyStatus>([&](Unit *sellerUnit){
            return sellerUnit->capability<Controller>().fold<BuyStatus>([&](Controller* sellerController){
                return sellerController->person().fold<BuyStatus>([&](Person* seller){
                    if(seller != this) {
                        const auto wareInfo = wareRef.info();
                        if(wareInfo.isValid()) {
                        const auto price = sellerStorage->priceTable()->price(wareInfo.wareName()).buyPrice();
                            if(price.has_value()) {
                                if(price.value() != 0) {                                    
                                    count = std::min(count, wareInfo.count());
                                    auto totalPrice = std::min(m_money, int64_t(count * price.value()));
                                    const size_t finalCount = totalPrice / price.value();
                                    totalPrice = finalCount * price.value();
                                    if(finalCount != 0) {
                                        wareRef.storage()->transferWareTo(wareRef.index(), destination, finalCount);
                                        m_money -= totalPrice;
                                        seller->m_money += totalPrice;
                                        return BuyingSuccess;
                                    } else {
                                        return NotEnoughMoney;
                                    }
                                } else {
                                    return PriceIsZero;
                                }
                            } else {
                                return BuePriceNotDefined;
                            }
                        } else {
                            return SellerDoNotHaveWare;
                        }
                    } else {
                        return CanNotBuyOwnWare;
                    }
                }, []{ return SellerIsNull; });
            }, []{ return SellerControllerIsNull; });
        }, []{ return SellerUnitIsNull; });
    }, []{ return SellerStorageIsNull; });
}

Person::SellStatus Person::sellWare(const WareStorage::WareRef &wareRef, const e172::ptr<WareStorage> &buyerStorage, size_t count) {
    return buyerStorage.fold<SellStatus>([&](WareStorage* buyerStorage){
        return buyerStorage->parentUnit().fold<SellStatus>([&](Unit *buyerUnit){
            return buyerUnit->capability<Controller>().fold<SellStatus>([&](Controller* buyerController){
                return buyerController->person().fold<SellStatus>([&](Person* buyer){
                    if(buyer != this) {
                        if(isOwnerOfWare(wareRef)) {
                            const auto wareInfo = wareRef.storage()->wareInfo(wareRef.index());
                            if(wareInfo.isValid()) {
                                const auto price = buyerStorage->priceTable()->price(wareInfo.wareName()).sellPrice();
                                if(price.has_value()) {
                                    if(price.value() != 0) {
                                        auto totalPrice = std::min(buyer->m_money, int64_t(count * price.value()));
                                        const int64_t finalCount = totalPrice / price.value();
                                        totalPrice = totalPrice * finalCount;
                                        wareRef.storage()->transferWareTo(wareRef.index(), buyerStorage, finalCount);
                                        buyer->m_money -= totalPrice;
                                        m_money += totalPrice;
                                        return SellingSuccess;
                                    } else {
                                        return SellPriceIsZero;
                                    }
                                } else {
                                    return SellPriceNotDefined;
                                }
                            } else {
                                return WareDoNotExist;
                            }
                        } else {
                            return WareNotBelongToSeller;
                        }
                    } else {
                        return CanNotSellWareToSelf;
                    }
                }, []{ return BuyerIsNull; });
            }, []{ return BuyerControllerIsNull; });
        }, []{ return BuyerUnitIsNull; });
    }, []{ return BuyerStorageIsNull; });
}

Person::Person(const std::string &name) {
    m_name = name;
}
