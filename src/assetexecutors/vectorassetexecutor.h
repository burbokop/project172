#pragma once

#include <e172/assettools/abstractassetexecutor.h>

namespace proj172::core {

class VectorAssetExecutor : public e172::AbstractAssetExecutor {
public:
    VectorAssetExecutor() = default;

    // AssetExecutor interface
public:
    virtual e172::Variant proceed(const e172::Variant &value) override;
};

} // namespace proj172::core
