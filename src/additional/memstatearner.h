#ifndef MEMSTATEARNER_H
#define MEMSTATEARNER_H

#include <src/engine/entity.h>

#include <src/engine/math/averagecalculator.h>
#include <src/engine/math/differentiator.h>

#include <src/engine/time/elapsedtimer.h>



class MemStatEarner : public e172::Entity {
    Differentiator vm_size_differentiator;
    Differentiator rss_differentiator;
    AverageCalculator vm_diff_ac;
    AverageCalculator rss_diff_ac;

    AverageCalculator proceed_delay_ac;
    AverageCalculator render_delay_ac;
    double proceed_delay;
    double render_delay;

    long vm;
    long rss;
    double vm_d;
    double rss_d;
    double vm_d_average;
    double rss_d_average;

    bool enabled = false;
public:
    MemStatEarner();

    // Entity interface
public:
    virtual void proceed(e172::Context *context, e172::AbstractEventHandler *e) override;
    virtual void render(e172::AbstractRenderer *renderer) override;
};

#endif // MEMSTATEARNER_H
