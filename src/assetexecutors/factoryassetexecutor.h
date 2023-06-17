#ifndef RECIEPTASSETEXECUTOR_H
#define RECIEPTASSETEXECUTOR_H

#include <src/assettools/abstractassetexecutor.h>

namespace proj172::core {

class RecieptAssetExecutor : public e172::AbstractAssetExecutor {
public:
    RecieptAssetExecutor();

    // AbstractAssetExecutor interface
public:
    virtual e172::Variant proceed(const e172::Variant &value) override;
};

} // namespace proj172::core

#endif // RECIEPTASSETEXECUTOR_H
