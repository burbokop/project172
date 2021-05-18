#ifndef MEMSTATEARNER_H
#define MEMSTATEARNER_H

#include <src/entity.h>

#include <src/math/averagecalculator.h>
#include <src/math/differentiator.h>

#include <src/time/elapsedtimer.h>



class MemStatEarner : public e172::Entity {
    e172::Differentiator vm_size_differentiator;
    e172::Differentiator rss_differentiator;
    AverageCalculator vm_diff_ac;
    AverageCalculator rss_diff_ac;

    AverageCalculator proceed_delay_ac;
    AverageCalculator render_delay_ac;
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
    MemStatEarner();

    // Entity interface
public:
    virtual void proceed(e172::Context *context, e172::AbstractEventHandler *e) override;
    virtual void render(e172::AbstractRenderer *renderer) override;
};

#endif // MEMSTATEARNER_H
