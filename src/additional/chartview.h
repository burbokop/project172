#pragma once

#include <e172/entity.h>
#include <e172/math/vector.h>

namespace proj172::core {

class ChartView : public e172::Entity {
    double (*m_function)(double, double);
    double m_coeficient = 0;
    e172::Vector<double> m_offset;
    size_t m_pointCount = 0;
public:
    ChartView(e172::FactoryMeta &&meta)
        : e172::Entity(std::move(meta))
    {}

    void setFunction(double (*function)(double, double)) { m_function = function; }
    double coeficient() const { return m_coeficient; }
    void setCoeficient(double coeficient) { m_coeficient = coeficient; }
    e172::Vector<double> offset() const { return m_offset; }
    void setOffset(const e172::Vector<double> &offset) { m_offset = offset; }
    size_t pointCount() const { return m_pointCount; }
    void setPointCount(const size_t &pointCount) { m_pointCount = pointCount; }

    // Entity interface
public:
    virtual void proceed(e172::Context *, e172::EventHandler *) override{};
    virtual void render(e172::Context *context, e172::AbstractRenderer *renderer) override;
};

} // namespace proj172::core
