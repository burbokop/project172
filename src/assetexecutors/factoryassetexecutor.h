#pragma once

#include <e172/assettools/abstractassetexecutor.h>

namespace proj172::core {

class RecieptAssetExecutor : public e172::AbstractAssetExecutor {
public:
    RecieptAssetExecutor();

    // AbstractAssetExecutor interface
public:
    virtual e172::Variant proceed(const e172::Variant &value) override;
};

} // namespace proj172::core
