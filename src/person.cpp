#include "person.h"

std::string Person::name() const {
    return m_name;
}

void Person::setName(const std::string &name)
{
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

bool Person::isJuridicalPerson() const
{
    return m_isJuridicalPerson;
}

void Person::setIsJuridicalPerson(bool isJuridicalPerson)
{
    m_isJuridicalPerson = isJuridicalPerson;
}

size_t Person::money() const
{
    return m_money;
}

void Person::setMoney(const size_t &money)
{
    m_money = money;
}

Person::Person() {

}
