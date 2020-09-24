#include "averagecalculator.h"
#include "math.h"

#include <math.h>

double AverageCalculator::autoResetError() const
{
    return m_autoResetError;
}

void AverageCalculator::setAutoResetError(double autoResetError)
{
    m_autoResetError = autoResetError;
}

bool AverageCalculator::enableAutoReset() const
{
    return m_enableAutoReset;
}

void AverageCalculator::setEnableAutoReset(bool enableAutoReset)
{
    m_enableAutoReset = enableAutoReset;
}

AverageCalculator::AverageCalculator() {}

double AverageCalculator::proceed(double value) {
    if(m_enableAutoReset && value != e172::Math::null && (std::abs(average - value) / value) > m_autoResetError) {
        average = value;
    }

    average = ((average * count + value) / (count + 1));
    count++;
    return average;
}
