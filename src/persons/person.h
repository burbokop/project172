#ifndef PERSON_H
#define PERSON_H

#include <set>
#include <string>
#include <src/object.h>
#include <src/utility/ptr.h>
#include <src/capabilities/warestorage.h>
#include <src/smartenum.h>

class Person : public e172::Object {
    std::string m_name;
    e172::ptr<Person> m_hostPerson;
    std::set<e172::ptr<Person>> m_employees;

    bool m_isJuridicalPerson = false;
    size_t m_money = 0;


    E172_SMART_ENUM_RESULT(BuyStatus,
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

    E172_SMART_ENUM_RESULT(SellStatus,
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
    size_t money() const;
    void setMoney(const size_t &money);

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

#endif // PERSON_H
