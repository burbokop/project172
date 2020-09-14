#include "physicalobject.h"
#include "math.h"
#include <src/engine/math/math.h>

double e172::PhysicalObject::mass() const {
    return m_mass;
}

void e172::PhysicalObject::setMass(double mass) {
    m_mass = mass;
}

double e172::PhysicalObject::friction() const {
    return m_friction;
}

void e172::PhysicalObject::setFriction(double friction) {
    m_friction = friction;
}

e172::Matrix e172::PhysicalObject::rotationMatrix() const
{
    return m_rotationMatrix;
}

e172::PhysicalObject::ConnectionNode e172::PhysicalObject::connectionNode(const e172::Vector &offset, double rotation) {
    ConnectionNode node;
    node.m_object = this;
    node.m_offset = offset;
    node.m_rotation = rotation;
    return node;
}

void e172::PhysicalObject::resetPhysicsProperties(e172::Vector position, double rotation, e172::Vector velocity, double rotationVelocity) {
    positionKinematics.setValue(position);
    positionKinematics.setVelocity(velocity);
    rotationKinematics.setValue(rotation);
    rotationKinematics.setVelocity(rotationVelocity);
}

e172::PhysicalObject::PhysicalObject() {
    rotationKinematics.setValueProcessor(&Math::constrainRadians);
}

void e172::PhysicalObject::addRotationForce(double value) {
    if(!Math::cmpf(m_mass, 0)) {
        rotationKinematics.addAcceleration(value / m_mass);
    }
}

void e172::PhysicalObject::addRotationGravityForce(double destiantionRotation, double coeficient) {
    const auto direction = Math::radiansDifference(destiantionRotation, rotation());
    if(direction != Math::null) {
        addRotationForce(coeficient / direction);
    }
}

void e172::PhysicalObject::addRotationPursuitForce(const e172::PhysicalObject *object, double deltaTime) {
    if(deltaTime != Math::null) {
        const auto direction = Math::radiansDifference(object->rotation(), rotation());
        addRotationForce((direction - rotationVelocity()) / deltaTime);
    }
}

void e172::PhysicalObject::addRotationFollowForce(double destiantionRotation, double maxAngleDistance, double coeficient) {
    if(maxAngleDistance != Math::null) {
        const auto direction = Math::radiansDifference(destiantionRotation, rotation());
        const auto a = (1 - direction / maxAngleDistance);
        if(a != Math::null) {
            const auto x = (1 / a - 1);
            addRotationForce(std::abs(x) * coeficient);
        }
    }
}

void e172::PhysicalObject::addRotationRestoringForce(double destiantionRotation, double coeficient) {
    const auto direction = Math::radiansDifference(destiantionRotation, rotation());
    addRotationForce(direction * coeficient);
}

void e172::PhysicalObject::addTargetRotationForse(double destinationAngle, double rotationForceModule, double maxRotationVelocity) {
    addLimitedRotationForce(static_cast<double>(Math::radiansDirection(destinationAngle, rotation())) * rotationForceModule, maxRotationVelocity);
}

void e172::PhysicalObject::addForce(const Vector& value) {
    if(!Math::cmpf(m_mass, 0)) {
        positionKinematics.addAcceleration(value / m_mass);
    }
}

void e172::PhysicalObject::addForwardForce(double module) {
    addForce(m_rotationMatrix * e172::Vector { module, 0 });
}

void e172::PhysicalObject::addLeftForce(double module) {
    addForce(Vector::createByAngle(module, rotation() - Math::Pi / 2));
}

void e172::PhysicalObject::addRightForce(double module) {
    addForce(Vector::createByAngle(module, rotation() + Math::Pi / 2));
}

void e172::PhysicalObject::addLimitedForce(const e172::Vector &value, double maxVelocity) {
    if(!Math::cmpf(m_mass, 0)) {
        positionKinematics.addLimitedAcceleration(value / m_mass, maxVelocity);
    }
}

void e172::PhysicalObject::addLimitedForwardForce(double module, double maxVelocity) {
    addLimitedForce(Vector::createByAngle(module, rotation()), maxVelocity);
}

void e172::PhysicalObject::addLimitedLeftForce(double module, double maxVelocity) {
    addLimitedForce(Vector::createByAngle(module, rotation() - Math::Pi / 2), maxVelocity);
}

void e172::PhysicalObject::addLimitedRightForce(double module, double maxVelocity) {
    addLimitedForce(Vector::createByAngle(module, rotation() + Math::Pi / 2), maxVelocity);
}

void e172::PhysicalObject::addLimitedRotationForce(double value, double maxAngleVelocity) {
    if(!Math::cmpf(m_mass, 0)) {
        rotationKinematics.addLimitedAcceleration(value / m_mass, maxAngleVelocity);
    }
}

void e172::PhysicalObject::addPursuitForce(const e172::PhysicalObject *object, double deltaTime) {
    if(deltaTime != Math::null) {
        addForce((object->position() - position() - velocity()) / deltaTime);
    }
}

void e172::PhysicalObject::addGravityForce(const e172::Vector &gravityCenter, double coeficient) {
    const auto direction = gravityCenter - position();
    const auto r2 = direction * direction;
    addForce(direction * coeficient / r2);
}

void e172::PhysicalObject::addFollowForce(const e172::Vector &targetPoint, double maxDistance, double coeficient) {
    if(maxDistance != Math::null) {
        const auto direction = targetPoint - position();
        const auto a = (1 - direction.module() / maxDistance);
        if(a != Math::null) {
            const auto x = (1 / a - 1);
            addForce(direction.normalized() * std::abs(x) * coeficient);
        }
    }
}

void e172::PhysicalObject::addRestoringForce(const e172::Vector &destiantionPosition, double coeficient) {
    addForce((destiantionPosition - position()) * coeficient);
}

void e172::PhysicalObject::connectNodes(e172::PhysicalObject::ConnectionNode node0, e172::PhysicalObject::ConnectionNode node1, double coeficient, double rotationCoeficient) {
    if(node0.m_object && node1.m_object) {
        const auto point0 = node0.m_object->m_rotationMatrix * node0.m_offset;
        const auto point1 = node1.m_object->m_rotationMatrix * node1.m_offset;

        node0.m_rotation = Math::constrainRadians(node0.m_rotation + Math::Pi);

        node0.m_object->addRestoringForce(node1.m_object->position() + point1 - point0, coeficient);
        node1.m_object->addRestoringForce(node0.m_object->position() + point0 - point1, coeficient);

        node0.m_object->addRotationRestoringForce(Math::radiansDifference(Math::constrainRadians(node1.m_object->rotation() + node1.m_rotation), node0.m_rotation), rotationCoeficient);
        node1.m_object->addRotationRestoringForce(Math::radiansDifference(Math::constrainRadians(node0.m_object->rotation() + node0.m_rotation), node1.m_rotation), rotationCoeficient);
    }
}

void e172::PhysicalObject::proceedPhysics(double deltaTime) {
    if(m_mass != Math::null) {
        rotationKinematics.addFriction(m_friction / m_mass);
        positionKinematics.addFriction(m_friction / m_mass);
    }

    rotationKinematics.accept(deltaTime);
    m_rotationMatrix = e172::Matrix::fromRadians(rotation());
    positionKinematics.accept(deltaTime);

}

