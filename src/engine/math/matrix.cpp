#include "matrix.h"

#include <math.h>

e172::Matrix::Matrix(double value) {
    m_a11 = value;
    m_a21 = value;
}

e172::Vector e172::Matrix::operator*(const e172::Vector &vector) const {
    return {
        m_a11 * vector.x() + m_a12 * vector.y(),
        m_a21 * vector.x() + m_a22 * vector.y()
    };
}

e172::Matrix e172::Matrix::fromRadians(double value) {
    Matrix m;
    m.m_a11 = std::cos(value);
    m.m_a12 = -std::sin(value);
    m.m_a21 = -m.m_a12;
    m.m_a22 = m.m_a11;
    return m;
}
