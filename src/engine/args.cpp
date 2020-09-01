#include "args.h"


e172::Args::operator Variant() const {
    return m_v;
}

e172::Args::operator VariantVector() const {
    return m_v;
}

e172::VariantVector e172::Args::value() const {
    return m_v;
}
