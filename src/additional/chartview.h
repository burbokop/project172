#ifndef CHARTVIEW_H
#define CHARTVIEW_H

#include <src/entity.h>
#include <src/math/vector.h>

class ChartView : public e172::Entity {
    double (*m_function)(double, double);
    double m_coeficient = 0;
    e172::Vector<double> m_offset;
    size_t m_pointCount = 0;
public:
    ChartView(e172::FactoryMeta &&meta);
    void setFunction(double (*function)(double, double)) {
        m_function = function;
    }

    // Entity interface
public:
    virtual void proceed(e172::Context *, e172::EventHandler *) override{};
    virtual void render(e172::AbstractRenderer *renderer) override;
    double coeficient() const;
    void setCoeficient(double coeficient);
    e172::Vector<double> offset() const;
    void setOffset(const e172::Vector<double> &offset);
    size_t pointCount() const;
    void setPointCount(const size_t &pointCount);
};

#endif // CHARTVIEW_H
