#include "context.h"
#include "physicalobject.h"
#include "math.h"
#include "abstracteventhandler.h"
#include <src/engine/math/math.h>
#include <src/engine/graphics/abstractrenderer.h>

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

e172::PhysicalObject::ConnectionNode e172::PhysicalObject::connectionNode(const e172::Vector &offset, double rotation) {
    ConnectionNode node;
    node.m_object = this;
    node.m_offset = offset;
    node.m_rotation = rotation;
    return node;
}

e172::PhysicalObject::PhysicalObject(PhysicalObject *object) {
    to = object;
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

void e172::PhysicalObject::addRotationPursuitForce(const e172::Context *context, const e172::PhysicalObject *object) {
    const auto dt = context->deltaTime();
    if(dt != Math::null) {
        const auto direction = Math::radiansDifference(object->rotation(), rotation());
        addRotationForce((direction - rotationVelocity()) / dt);
    }
}

void e172::PhysicalObject::addRotationFollowForce(double destiantionRotation, double maxAngleDistance, double coeficient) {
    if(maxAngleDistance != Math::null) {
        const auto direction = Math::degreesDifference(destiantionRotation, rotation());
        const auto a = (1 - direction / maxAngleDistance);
        if(a != Math::null) {
            const auto x = (1 / a - 1);
            addRotationForce(std::abs(x) * coeficient);
        }
    }
}

void e172::PhysicalObject::addForce(const Vector& value) {
    if(!Math::cmpf(m_mass, 0)) {
        positionKinematics.addAcceleration(value / m_mass);
    }
}

void e172::PhysicalObject::addForwardForce(double module) {
    addForce(Vector::createByAngle(module, rotation()));
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

void e172::PhysicalObject::addPursuitForce(const Context *context, const e172::PhysicalObject *object) {
    const auto dt = context->deltaTime();
    if(dt != Math::null) {
        addForce((object->position() - position() - velocity()) / dt);
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

void e172::PhysicalObject::connectNodes(e172::PhysicalObject::ConnectionNode node0, e172::PhysicalObject::ConnectionNode node1, double coeficient) {
    if(node0.m_object && node1.m_object) {
        node0.m_object->addGravityForce(node1.m_object->position() + node1.m_offset, coeficient);
        node1.m_object->addGravityForce(node0.m_object->position() + node0.m_offset, coeficient);
        node0.m_object->addRotationGravityForce(node1.m_object->rotation() + node1.m_rotation, coeficient);
        node1.m_object->addRotationGravityForce(node0.m_object->rotation() + node0.m_rotation, coeficient);
    }
}

void e172::PhysicalObject::proceed(e172::Context *context, e172::AbstractEventHandler *e) {
    static id_t ee = entityId();

    if(ee == entityId()) {
        if(e->keyHolded(e172::ScancodeKp4)) {
            addRotationForce(-1);
        } else if(e->keyHolded(e172::ScancodeKp6)) {
            addRotationForce(1);
        }

        if(e->keyHolded(e172::ScancodeKp8)) {
            addForwardForce(100);
        }
    }

    if(to) {
        if(e->keyHolded(e172::Scancode1)) {
            //addPursuitForce(context, to);
            //addGravityForce(to->position(), 1000);
            //to->addGravityForce(position(), 1000);
            addFollowForce(to->position(), 200);
        }
    }

    if(m_mass != Math::null) {
        rotationKinematics.addFriction(m_friction / m_mass);
        positionKinematics.addFriction(m_friction / m_mass);
    }

    rotationKinematics.accept(context->deltaTime());
    positionKinematics.accept(context->deltaTime());
}

void e172::PhysicalObject::render(e172::AbstractRenderer *renderer) {
    const auto r0 = 8;
    const auto r1 = 4;

    const auto d = (r0 + r1) / 2;
    renderer->drawCircleShifted(position() - Vector::createByAngle(d, rotation()), r0, 0xff0000);
    renderer->drawCircleShifted(position() + Vector::createByAngle(d, rotation()), r1, 0xff0000);

    renderer->drawLineShifted(position(), position() + velocity(), 0x00ff00);
    renderer->drawLineShifted(position(), position() + acceleration(), 0x0000ff);
}
