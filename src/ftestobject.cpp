#include "ftestobject.h"

#include <src/engine/abstracteventhandler.h>
#include <src/engine/context.h>

#include <src/engine/graphics/abstractrenderer.h>

#include <src/engine/math/math.h>
#include <src/engine/math/matrix.h>

#include <src/engine/utility/ptr.h>




e172::Vector FTestObject::cOffset() const {
    return m_cOffset;
}

void FTestObject::setCOffset(const e172::Vector &cOffset) {
    m_cOffset = cOffset;
}

double FTestObject::cAngle() const {
    return m_cAngle;
}

void FTestObject::setCAngle(double cAngle) {
    m_cAngle = cAngle;
}

void FTestObject::setColiderVertices(const std::vector<e172::Vector> &vertices) {
    colider.setVertices(vertices);
}

e172::ptr2<e172::ltd> FTestObject::someData() const {
    return m_someData;
}

FTestObject::FTestObject(FTestObject *object) {
    m_targetObject = object;
}

void FTestObject::proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler) {
    static id_t ee = entityId();

    if(ee == entityId()) {
        if(eventHandler->keyHolded(e172::ScancodeKp4)) {
            addRotationForce(-1);
        } else if(eventHandler->keyHolded(e172::ScancodeKp6)) {
            addRotationForce(1);
        }

        if(eventHandler->keyHolded(e172::ScancodeKp8)) {
            addForwardForce(100);
        }
    }

    if(m_targetObject) {
        if(eventHandler->keyHolded(e172::Scancode1)) {
            const auto node0 = connectionNode(m_cOffset, m_cAngle);
            const auto node1 = m_targetObject->connectionNode(m_targetObject->m_cOffset, m_targetObject->m_cAngle);

            e172::PhysicalObject::dockNodes(node0, node1, 20, 2);
        }
        m_targetObject->colider.setMatrix(m_targetObject->rotationMatrix());
        m_targetObject->colider.setPosition(m_targetObject->position());
        colider.setMatrix(rotationMatrix());
        colider.setPosition(position());
        const auto vp = e172::Colider::narrowCollision(&colider, &m_targetObject->colider);
        escapeVector = vp.first;
        m_targetObject->escapeVector = vp.second;
    }

    if(escapeVector.vector.cheapModule()) {
        //resetPhysicsProperties(position(), rotation(), velocity() + escapeVector.vector, rotationVelocity());
        addForce(escapeVector.vector);
        escapeVector = {};
    }

    proceedPhysics(context->deltaTime());
}

void FTestObject::render(e172::AbstractRenderer *renderer) {
    const auto r0 = 8;
    const auto r1 = 4;

    const auto rotatedCOffset = rotationMatrix() * m_cOffset;
    const auto rotatedCAngle = e172::Math::constrainRadians(rotation() + m_cAngle);


    const auto d = (r0 + r1) / 2;
    renderer->drawCircleShifted(position() - e172::Vector::createByAngle(d, rotation()), r0, 0xff0000);
    renderer->drawCircleShifted(position() + e172::Vector::createByAngle(d, rotation()), r1, 0xff0000);

    renderer->drawLineShifted(position(), position() + velocity(), 0x00ff00);
    renderer->drawLineShifted(position(), position() + acceleration(), 0x0000ff);

    renderer->drawCircleShifted(position() + rotatedCOffset, 4, 0xff00ff);
    renderer->drawLineShifted(position() + rotatedCOffset, position() + rotatedCOffset + e172::Vector::createByAngle(8, rotatedCAngle), 0xff00ff);



    //const auto vertices = colider.vertices();
    //if(vertices.size() > 1) {
    //    size_t i = 0;
    //    e172::Vector lastVertex;
    //    bool hasLast = false;
    //    for(auto v : vertices) {
    //        if(hasLast) {
    //            renderer->drawLineShifted(lastVertex + position(), v + position(), 0xffffff);
    //        }
    //        hasLast = true;
    //        lastVertex = v;
    //        ++i;
    //    }
    //    renderer->drawLineShifted(vertices[vertices.size() - 1] + position(), vertices[0] + position(), 0xffffff);
    //}

    const auto edges = e172::Colider::transformed(colider.edges(), rotationMatrix());
    for(auto e : edges) {
        renderer->drawLineShifted(e.position + position(), e.position + e.vector + position(), 0xffffff);
        renderer->drawCircleShifted(e.position + e.vector + position(), 2, 0xffffff);
    }

    const auto projections = colider.projections();
    int i = 0;
    for(auto p : projections) {
        renderer->drawLineShifted(p.position, p.position + p.vector, p.colided ? 0x888888 : 0xff00ff);
        renderer->drawCircleShifted(p.position + p.vector, 2, p.colided ? 0x888888 : 0xff00ff);
        ++i;
    }
    renderer->drawStringShifted(std::to_string(colider.significantNormalCount()) + " : " + std::to_string(colider.collisionCount()), position(), e172::randomColor(i));

    const auto rc = e172::randomColor(reinterpret_cast<uintptr_t>(this));

    const auto escape = colider.escapeVectors();
    for(auto p : escape) {
        renderer->drawLineShifted(p.position, p.position + p.vector, rc);
        renderer->drawCircleShifted(p.position + p.vector, 2, 0x000000);
    }

    renderer->drawCircleShifted(position(), 4, rc);
    renderer->drawCircleShifted(escapeVector.position, 8, 0x000000);

    renderer->drawLineShifted(escapeVector.position, escapeVector.position + escapeVector.vector, rc);
}
