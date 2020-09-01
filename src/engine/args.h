#ifndef ARGS_H
#define ARGS_H

#include "variant.h"


namespace e172 {

class Args {
    VariantVector m_v;
public:
    template<typename ...T>
    Args(const T& ...args) {
        m_v = VariantVector { args... };
    }
    operator Variant() const;
    operator VariantVector() const;
    VariantVector value() const;


    template<typename T>
    friend Args &operator <<(Args& args, const T& v) {
        args.m_v.push_back(v);
        return args;
    }

};


}
#endif // ARGS_H
