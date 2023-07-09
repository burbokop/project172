#pragma once

#include <e172/entity.h>
#include <e172/math/averagecalculator.h>
#include <e172/math/differentiator.h>
#include <e172/time/elapsedtimer.h>

namespace proj172::core {

class MemStatEarner : public e172::Entity {
    e172::Differentiator vm_size_differentiator;
    e172::Differentiator rss_differentiator;
    e172::AverageCalculator vm_diff_ac;
    e172::AverageCalculator rss_diff_ac;

    e172::AverageCalculator proceed_delay_ac;
    e172::AverageCalculator render_delay_ac;
    double proceed_delay = 0;
    double render_delay = 0;
    double proceed_delay_avrg = 0;
    double render_delay_avrg = 0;

    long vm = 0;
    long rss = 0;
    double vm_d = 0;
    double rss_d = 0;
    double vm_d_average = 0;
    double rss_d_average = 0;

    bool enabled = false;
public:
    MemStatEarner(e172::FactoryMeta &&meta);

    // Entity interface
public:
    virtual void proceed(e172::Context *context, e172::EventHandler *e) override;
    virtual void render(e172::Context *context, e172::AbstractRenderer *renderer) override;
};

} // namespace proj172::core
