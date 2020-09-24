#ifndef AVERAGECALCULATOR_H
#define AVERAGECALCULATOR_H


class AverageCalculator {
    double average = 0;
    unsigned long count = 0;

    double m_autoResetError = 0;
    bool m_enableAutoReset = false;
public:
    AverageCalculator();
    double proceed(double value);
    double autoResetError() const;
    void setAutoResetError(double autoResetError);
    bool enableAutoReset() const;
    void setEnableAutoReset(bool enableAutoReset);
};

#endif // AVERAGECALCULATOR_H
