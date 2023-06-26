#include "ftestobject.h"

#include "src/eventhandler.h"
#include <src/context.h>
#include <src/graphics/abstractrenderer.h>
#include <src/math/math.h>
#include <src/math/matrix.h>
#include <src/utility/ptr.h>

void FTestObject::setCOffset(const e172::Vector<double> &cOffset)
{
    m_cOffset = cOffset;
}

void FTestObject::setCAngle(double cAngle)
{
    m_cAngle = cAngle;
}

void FTestObject::setColiderVertices(const std::vector<e172::Vector<double> > &vertices)
{
    m_colider.setVertices(vertices);
}

void FTestObject::proceed(e172::Context *context, e172::EventHandler *eventHandler)
{
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
        m_targetObject->m_colider.setMatrix(m_targetObject->rotationMatrix());
        m_targetObject->m_colider.setPosition(m_targetObject->position());
        m_colider.setMatrix(rotationMatrix());
        m_colider.setPosition(position());
        const auto vp = e172::Colider::narrowCollision(&m_colider, &m_targetObject->m_colider);
        m_escapeVector = vp.first;
        m_targetObject->m_escapeVector = vp.second;
    }

    if (m_escapeVector.vector.cheapModule()) {
        //resetPhysicsProperties(position(), rotation(), velocity() + escapeVector.vector, rotationVelocity());
        addForce(m_escapeVector.vector);
        m_escapeVector = {};
    }

    proceedPhysics(context->deltaTime());
}

void FTestObject::render(e172::Context *context, e172::AbstractRenderer *renderer)
{
    const auto r0 = 8;
    const auto r1 = 4;

    const auto rotatedCOffset = rotationMatrix() * m_cOffset;
    const auto rotatedCAngle = e172::Math::constrainRadians(rotation() + m_cAngle);


    const auto d = (r0 + r1) / 2;
    renderer->drawCircleShifted(position() - e172::Vector<double>::createByAngle(d, rotation()),
                                r0,
                                0xff0000);

    renderer->drawCircleShifted(position() + e172::Vector<double>::createByAngle(d, rotation()),
                                r1,
                                0xff0000);

    renderer->drawLineShifted(position(), position() + velocity(), 0x00ff00);
    renderer->drawLineShifted(position(), position() + acceleration(), 0x0000ff);

    renderer->drawCircleShifted(position() + rotatedCOffset, 4, 0xff00ff);
    renderer->drawLineShifted(position() + rotatedCOffset,
                              position() + rotatedCOffset
                                  + e172::Vector<double>::createByAngle(8, rotatedCAngle),
                              0xff00ff);

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

    const auto edges = e172::Colider::transformed(m_colider.edges(), rotationMatrix());
    for(auto e : edges) {
        renderer->drawLineShifted(e.position + position(), e.position + e.vector + position(), 0xffffff);
        renderer->drawCircleShifted(e.position + e.vector + position(), 2, 0xffffff);
    }

    const auto projections = m_colider.projections();
    int i = 0;
    for(auto p : projections) {
        renderer->drawLineShifted(p.position, p.position + p.vector, p.colided ? 0x888888 : 0xff00ff);
        renderer->drawCircleShifted(p.position + p.vector, 2, p.colided ? 0x888888 : 0xff00ff);
        ++i;
    }
    renderer->drawStringShifted(std::to_string(m_colider.significantNormalCount()) + " : "
                                    + std::to_string(m_colider.collisionCount()),
                                position(),
                                e172::randomColor(i));

    const auto rc = e172::randomColor(reinterpret_cast<uintptr_t>(this));

    const auto escape = m_colider.escapeVectors();
    for(auto p : escape) {
        renderer->drawLineShifted(p.position, p.position + p.vector, rc);
        renderer->drawCircleShifted(p.position + p.vector, 2, 0x000000);
    }

    renderer->drawCircleShifted(position(), 4, rc);
    renderer->drawCircleShifted(m_escapeVector.position, 8, 0x000000);

    renderer->drawLineShifted(m_escapeVector.position,
                              m_escapeVector.position + m_escapeVector.vector,
                              rc);
}
