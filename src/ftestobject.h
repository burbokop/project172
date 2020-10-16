#ifndef FTESTOBJECT_H
#define FTESTOBJECT_H

#include <src/entity.h>
#include <src/physicalobject.h>
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

class FTestObject : public e172::Entity, public e172::PhysicalObject {
    FTestObject *m_targetObject = nullptr;

    e172::Vector m_cOffset;
    double m_cAngle = 0;

    double ra = 0;

    e172::Colider colider;

    e172::destroyeble_ptr<e172::ltd> m_someData = e172::destroyeble_ptr<e172::ltd>::create_ptr([](){ std::cout << "ltd dead\n"; });

    e172::Colider::PositionalVector escapeVector;
public:
    FTestObject(FTestObject *object = nullptr);

    // Entity interface
public:
    virtual void proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler) override;
    virtual void render(e172::AbstractRenderer *renderer) override;
    e172::Vector cOffset() const;
    void setCOffset(const e172::Vector &cOffset);
    double cAngle() const;
    void setCAngle(double cAngle);
    void setColiderVertices(const std::vector<e172::Vector> &vertices);


    e172::ptr2<e172::ltd> someData() const;
};

#endif // FTESTOBJECT_H
