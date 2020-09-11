#ifndef LKINEMATICS_H
#define LKINEMATICS_H

#include <type_traits>
#include <functional>

#include "../sfinae.h"

namespace e172 {

template<typename T>
class Kinematics {
    template<typename VT>
    static constexpr VT initValue() {
        if constexpr(std::is_integral<VT>::value) {
            return 0;
        } else {
            return T();
        }
    }

    T m_value = initValue<T>();
    T m_velocity = initValue<T>();
    T m_acceleration = initValue<T>();

    std::function<T(const T&)> m_differentialProcessor;

    E172_SFINAE_METHOD_CHECKER(length)
    E172_SFINAE_METHOD_CHECKER(module)

public:
    Kinematics();
    void addAcceleration(T value);
    void addLimitedAcceleration(T value, double maxVelocity);
    void addFriction(double coeficient);
    void accept(double deltaTime);
    T value() const;
    T velocity() const;
    T acceleration() const;
    std::function<T (const T&)> differentialProcessor() const;
    void setDifferentialProcessor(const std::function<T (const T&)> &differentialProcessor);
};

template<typename T>
T Kinematics<T>::velocity() const { return m_velocity; }
template<typename T>
T Kinematics<T>::acceleration() const { return m_acceleration; }
template<typename T>
T Kinematics<T>::value() const { return m_value; }

template<typename T>
Kinematics<T>::Kinematics() {}

template<typename T>
void Kinematics<T>::addAcceleration(T value) {
    m_acceleration += value;
}

template<typename T>
void Kinematics<T>::addLimitedAcceleration(T value, double maxVelocity) {
    if constexpr (std::is_integral<T>::value) {
        addAcceleration((maxVelocity - m_velocity) * value);
    } else if constexpr (has_length_method<T>::value) {
        addAcceleration((maxVelocity - m_velocity.length()) * value);
    } else if constexpr (has_module_method<T>::value) {
        addAcceleration((maxVelocity - m_velocity.module()) * value);
    } else {
        static_assert ("Kinematics<T>::addLimitedForce: T must be integral or have 'length' or 'module' method.");
    }
}

template<typename T>
void Kinematics<T>::addFriction(double coeficient) {
    addAcceleration(m_velocity * coeficient * (-1));
}

template<typename T>
void Kinematics<T>::accept(double deltaTime) {
    m_velocity += m_acceleration * deltaTime;
    if(m_differentialProcessor) {
        m_value += m_differentialProcessor(m_velocity * deltaTime);
    } else {
        m_value += m_velocity * deltaTime;
    }
    m_acceleration = initValue<T>();
}


template<typename T>
std::function<T (const T&)> Kinematics<T>::differentialProcessor() const {
    return m_differentialProcessor;
}

template<typename T>
void Kinematics<T>::setDifferentialProcessor(const std::function<T (const T&)> &differentialProcessor) {
    m_differentialProcessor = differentialProcessor;
}


}

#endif // LKINEMATICS_H
