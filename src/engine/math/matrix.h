#ifndef MATRIX_H
#define MATRIX_H

#include "vector.h"

namespace e172 {

class Matrix {
    double m_a11 = 0;
    double m_a12 = 0;
    double m_a21 = 0;
    double m_a22 = 0;
public:
    Matrix(double value = 1);
    static Matrix fromRadians(double value);

    Vector operator*(const Vector &vector) const;
};

}

#endif // MATRIX_H
