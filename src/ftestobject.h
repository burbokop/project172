#ifndef FTESTOBJECT_H
#define FTESTOBJECT_H

#include <src/engine/entity.h>
#include <src/engine/physicalobject.h>



class FTestObject : public e172::Entity, public e172::PhysicalObject {
    FTestObject *m_targetObject = nullptr;

    e172::Vector m_cOffset;
    double m_cAngle = 0;

    double ra = 0;
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
};

#endif // FTESTOBJECT_H
