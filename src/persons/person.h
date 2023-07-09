#pragma once

#include "../capabilities/warestorage.h"
#include <e172/object.h>
#include <e172/smartenum.h>
#include <e172/utility/ptr.h>
#include <set>
#include <string>

namespace proj172::core {

class Person : public e172::Object {
    std::string m_name;
    e172::ptr<Person> m_hostPerson;
    std::set<e172::ptr<Person>> m_employees;

    bool m_isJuridicalPerson = false;
    int64_t m_money = 0;

    e172_enum(BuyStatus,
                           BuyingSuccess,
                           CanNotBuyOwnWare,
                           SellerDoNotHaveWare,
                           BuePriceNotDefined,
                           PriceIsZero,
                           SellerIsNull,
                           SellerControllerIsNull,
                           SellerUnitIsNull,
                           SellerStorageIsNull,
                           NotEnoughMoney
                           )

    e172_enum(SellStatus,
                           SellingSuccess,
                           CanNotSellWareToSelf,
                           WareNotBelongToSeller,
                           WareDoNotExist,
                           SellPriceNotDefined,
                           SellPriceIsZero,
                           BuyerIsNull,
                           BuyerControllerIsNull,
                           BuyerUnitIsNull,
                           BuyerStorageIsNull
                           )

public:
    Person(const std::string& name = std::string());
    std::string name() const;
    void setName(const std::string &name);
    e172::ptr<Person> hostPerson() const;
    std::set<e172::ptr<Person> > employees() const;
    bool addEmployee(const e172::ptr<Person>& employee);
    bool removeEmployee(const e172::ptr<Person>& employee);
    bool isJuridicalPerson() const;
    void setIsJuridicalPerson(bool isJuridicalPerson);
    int64_t money() const;
    void setMoney(const int64_t &money);

    bool isOwnerOfWare(const WareStorage::WareRef &wareRef);

    BuyStatus buyWare(
            const WareStorage::WareRef &wareRef,
            const e172::ptr<WareStorage> &destination,
            size_t count = std::numeric_limits<size_t>::max()
            );

    SellStatus sellWare(
            const WareStorage::WareRef &wareRef,
            const e172::ptr<WareStorage> &buyerStorage,
            size_t count = std::numeric_limits<size_t>::max()
            );
};

} // namespace proj172::core
