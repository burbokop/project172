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

    long vm;
    long rss;
    double vm_d;
    double rss_d;
    double vm_d_average;
    double rss_d_average;
public:
    MemStatEarner();

    // Entity interface
public:
    virtual void proceed(e172::Context *, e172::AbstractEventHandler *) override;
    virtual void render(e172::AbstractRenderer *renderer) override;
};

#endif // MEMSTATEARNER_H
