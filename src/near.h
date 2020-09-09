#ifndef NEAR_H
#define NEAR_H

#include <vector>


#include <src/capabilities/controller.h>


class Near : public e172::Entity {
private:
    static const double RADIUS_DELTA;
    static const double DEFAULT_RADIUS;
    static const double WARP_RADIUS_MILTIPLIER;

    std::vector<e172::Entity*> m_entitiesInFocus;
    Controller *m_center = nullptr;

    size_t removingIterator = 0;

    double radius = 0;

    void removeEntities(e172::Context *);
    void addEntities(e172::Context *context);

    double localRadius(Unit *center);

public:

    Near(double radius = DEFAULT_RADIUS);
    Near(Controller *center, double radius = DEFAULT_RADIUS);


    int entityInFocusCount() const;
    e172::Entity* entityInFocus(int index) const;

    // Entity interface
public:
    virtual void proceed(e172::Context *context, e172::AbstractEventHandler *) override;
    virtual void render(e172::AbstractRenderer *) override {};
    Controller *center() const;
    void setCenter(Controller *center);
};

#endif // NEAR_H
