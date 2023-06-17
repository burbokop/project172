#pragma once

#include <src/entity.h>
#include <src/math/physicalobject.h>
#include <memory>
#include <iostream>
#include <src/math/colider.h>

namespace e172 {

class ltd {
    std::function<void()> f;
public:
    ltd(std::function<void()> f) { this->f = f; }
    ~ltd() { if(f) f(); }


    void foo() { }
    void bar() const { }
};

template <typename T>
class ptr2 {
protected:
    T* m_data = nullptr;
    std::shared_ptr<bool> m_alive;
public:
    T *operator->() { return m_data; }
    T *operator->() const { return m_data; }
    operator bool() const { return m_alive ? *m_alive : false; }

};

template<typename T>
class destroyeble_ptr : public ptr2<T> {
public:
    template<typename ...Args>
    static destroyeble_ptr<T> create_ptr(Args&&... args) {
        destroyeble_ptr<T> p;
        p.m_data = new T(args...);
        p.m_alive = std::make_shared<bool>(true);
        return p;
    }

    operator ptr2<T>() {
        return { this->m_data, this->m_alive };
    }

    ~destroyeble_ptr() {
        if(this->m_data) {
            delete this->m_data;
            if(this->m_alive) {
                *this->m_alive = false;
            }
        }
    }
};

}

class FTestObject : public e172::Entity, public e172::PhysicalObject
{
public:
    FTestObject(e172::FactoryMeta &&meta, FTestObject *object = nullptr)
        : e172::Entity(std::move(meta))
        , m_targetObject(object)
    {}

    // Entity interface
public:
    virtual void proceed(e172::Context *context, e172::EventHandler *eventHandler) override;
    virtual void render(e172::AbstractRenderer *renderer) override;
    e172::Vector<double> cOffset() const { return m_cOffset; }
    void setCOffset(const e172::Vector<double> &cOffset);
    double cAngle() const { return m_cAngle; }
    void setCAngle(double cAngle);
    void setColiderVertices(const std::vector<e172::Vector<double>> &vertices);
    e172::ptr2<e172::ltd> someData() const { return m_someData; }

private:
    FTestObject *m_targetObject = nullptr;
    e172::Vector<double> m_cOffset;
    double m_cAngle = 0;
    double ra = 0;
    e172::Colider m_colider;
    e172::destroyeble_ptr<e172::ltd> m_someData = e172::destroyeble_ptr<e172::ltd>::create_ptr(
        []() { std::cout << "ltd dead\n"; });
    e172::Colider::PositionalVector m_escapeVector;
};
