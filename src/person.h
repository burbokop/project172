#ifndef PERSON_H
#define PERSON_H

#include <set>
#include <string>
#include <src/object.h>
#include <src/utility/ptr.h>

class Person : public e172::Object {
    std::string m_name;
    e172::ptr<Person> m_hostPerson;
    std::set<e172::ptr<Person>> m_employees;

    bool m_isJuridicalPerson = false;
    size_t m_money = 0;
public:
    Person();
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
};

#endif // PERSON_H
