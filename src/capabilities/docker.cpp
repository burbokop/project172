#include "docker.h"

#include <src/units/unit.h>
#include <src/units/movable.h>

#include <src/engine/math/math.h>
#include <iostream>


bool Docker::enabled() const
{
    return m_enabled;
}

void Docker::setEnabled(bool enabled)
{
    m_enabled = enabled;
}

Docker::Docker() {}

Docker::State Docker::state() {
    return m_state;
}

void Docker::proceed(e172::Context *context, e172::AbstractEventHandler *eventHandler) {
    near.proceed(context, eventHandler);


    if(m_enabled && parentUnit()) {
        if(m_state == NotDocked) {
            for(int i = 0, count = near.entityInFocusCount(); i < count; ++i) {
                const auto t = near.entityInFocus(i);
                if(t == e172::Alive) {
                    m_target = dynamic_cast<Unit*>(t);
                    if(m_target && !m_target->containsTag("C")) {
                        const auto dd = e172::Math::radiansDistance(parentUnit()->angle(), e172::Math::constrainRadians(m_target->angle() - e172::Math::Pi));
                        std::cout << "n: " << dd << " : " << e172::Math::Pi / 16 << "\n";
                        if(dd < e172::Math::Pi / 16) {
                            m_state = InInterception;
                            break;
                        }
                    }
                }
            }
        } else if(m_state == InInterception) {

            const auto parent = parentUnit();
            const auto dd = e172::Math::radiansDistance(parent->angle(), e172::Math::constrainRadians(m_target->angle() - e172::Math::Pi));

            std::cout << "InInterception: " << dd << "\n";

            if(const auto movable = dynamic_cast<Movable*>(parent)) {
                movable->pursuit(context, m_target);
            }

            if(dd < e172::Math::Pi / 64 && (m_target->position() - parent->position()).cheapModule() < 2) {
                m_state = Docked;
                if(const auto movable = dynamic_cast<Movable*>(parent)) {
                    if(const auto movable2 = dynamic_cast<Movable*>(m_target)) {
                        movable2->physicallyAttachUnit(movable);
                    }
                }
            }

            if(!near.containsEntity(m_target) || dd > e172::Math::Pi / 16) {
                m_state = NotDocked;
            }
        } else if(m_state == Docked) {
            std::cout << "Docked\n";
        }
    } else {
        m_state = NotDocked;
    }

    //if(m_state == InInterception) {
    //
    //    double dst = (parentUnit()->position() - target->position()).module();
    //    if(dst < 64) {
    //        state = ATTRACTED;
    //    }
    //} else if(state == ATTRACTED) {
    //    double dst = (parentUnit()->position() - target->position()).module();
    //    double dstAngle = target->getAngle();
    //    if(dst < 4 && parentUnit()->isOnAngle(context, dstAngle)) {
    //        attach(target);
    //    }
    //    parentUnit()->rotateToAngle(context, dstAngle);
    //    Movable *movableParent = dynamic_cast<Movable*>(parentUnit());
    //    if(movableParent) {
    //        movableParent->place(parentUnit()->position(), (target->position() - parentUnit()->position()) / 100, e172::Vector(), parentUnit()->getAngle());
    //    }
    //} else if(state == DOCKED) {
    //    parentUnit()->place(target->position(), target->getAngle());
    //}
}

void Docker::render(e172::AbstractRenderer *renderer) {
    UNUSED(renderer);
}
