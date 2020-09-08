#ifndef NEAR_H
#define NEAR_H

#include <vector>


#include <src/capabilities/controller.h>


class Near : public e172::Entity {
private:
    static const double RADIUS_DELTA;
    static const double DEFAULT_RADIUS;
    static const double WARP_RADIUS_MILTIPLIER;

    std::list<e172::Entity*> m_entitiesInFocus;
    Controller *center = nullptr;

    std::list<e172::Entity*>::iterator removingIterator = m_entitiesInFocus.begin();

    double radius = 0;

    void removeEntities(e172::Context *);
    void addEntities(e172::Context *context);

    double localRadius(Unit *center);

public:


    Near(Controller *center, double radius = DEFAULT_RADIUS);



    std::list<e172::Entity*> entitiesInFocus();

    // Entity interface
public:
    virtual void proceed(e172::Context *context, e172::AbstractEventHandler *) override;
    virtual void render(e172::AbstractRenderer *) override {};
};

#endif // NEAR_H
