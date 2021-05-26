#ifndef NEAR_H
#define NEAR_H


#include <src/entity.h>
#include <src/utility/ptr.h>

class Capability;
class Unit;
class Near : public e172::Entity {
private:
    static const double DEFAULT_RADIUS_DELTA;
    static const double DEFAULT_RADIUS;
    static const double WARP_RADIUS_MILTIPLIER;

    std::vector<e172::ptr<e172::Entity>> m_entitiesInFocus;
    e172::ptr<Capability> m_center;

    size_t removingIterator = 0;

    double m_radius = 0;
    double m_delta = 0;

    void removeEntities(e172::Context *);
    void addEntities(e172::Context *context);

    double localRadius(const e172::ptr<Unit> &center);

    auto findEntityInFocus(const e172::ptr<e172::Entity>& entity) {
        return std::find_if(m_entitiesInFocus.begin(), m_entitiesInFocus.end(), [entity](auto a){
            return a == entity;
        });
    }
public:

    Near(double radius = DEFAULT_RADIUS, double delta = DEFAULT_RADIUS_DELTA);
    Near(Capability *center, double radius = DEFAULT_RADIUS, double delta = DEFAULT_RADIUS_DELTA);


    int entityInFocusCount() const;
    e172::ptr<Entity> entityInFocus(int index) const;
    bool containsEntity(const e172::ptr<Entity> &entity) const;

    // Entity interface
public:
    virtual void proceed(e172::Context *context, e172::AbstractEventHandler *) override;
    virtual void render(e172::AbstractRenderer *) override {};
    e172::ptr<Capability> center() const;
    void setCenter(const e172::ptr<Capability> &center);
};

#endif // NEAR_H
