#include "differentiator.h"
#include "math.h"

Differentiator::Differentiator() {

}

double Differentiator::proceed(double value) {
    if(last != value) {
        const auto dt = c.deltaTime();
        if(hasLast && dt != e172::Math::null) {
            derivative = (value - hasLast) / dt;
        }
        c.update();
    }

    last = value;
    hasLast = true;
    return derivative;
}
