#ifndef CHARTVIEW_H
#define CHARTVIEW_H

#include <src/engine/entity.h>

#include <src/engine/math/vector.h>



class ChartView : public e172::Entity {
    double (*m_function)(double, double);
    double m_coeficient = 0;
    e172::Vector m_offset;
    size_t m_pointCount = 0;
public:
    ChartView();
    void setFunction(double (*function)(double, double)) {
        m_function = function;
    }

    // Entity interface
public:
    virtual void proceed(e172::Context *, e172::AbstractEventHandler *) override {};
    virtual void render(e172::AbstractRenderer *renderer) override;
    double coeficient() const;
    void setCoeficient(double coeficient);
    e172::Vector offset() const;
    void setOffset(const e172::Vector &offset);
    size_t pointCount() const;
    void setPointCount(const size_t &pointCount);
};

#endif // CHARTVIEW_H
