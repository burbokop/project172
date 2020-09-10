#ifndef NEAR_H
#define NEAR_H


#include <src/engine/entity.h>

class Capability;
class Unit;
class Near : public e172::Entity {
private:
    static const double DEFAULT_RADIUS_DELTA;
    static const double DEFAULT_RADIUS;
    static const double WARP_RADIUS_MILTIPLIER;

    std::vector<e172::Entity*> m_entitiesInFocus;
    Capability *m_center = nullptr;

    size_t removingIterator = 0;

    double m_radius = 0;
    double m_delta = 0;

    void removeEntities(e172::Context *);
    void addEntities(e172::Context *context);

    double localRadius(Unit *center);

public:

    Near(double radius = DEFAULT_RADIUS, double delta = DEFAULT_RADIUS_DELTA);
    Near(Capability *center, double radius = DEFAULT_RADIUS, double delta = DEFAULT_RADIUS_DELTA);


    int entityInFocusCount() const;
    e172::Entity* entityInFocus(int index) const;
    bool containsEntity(e172::Entity* entity) const;

    // Entity interface
public:
    virtual void proceed(e172::Context *context, e172::AbstractEventHandler *) override;
    virtual void render(e172::AbstractRenderer *) override {};
    Capability *center() const;
    void setCenter(Capability *center);
};

#endif // NEAR_H
