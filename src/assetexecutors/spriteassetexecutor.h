#pragma once

#include <e172/assettools/abstractassetexecutor.h>

namespace proj172::core {

class SpriteAssetExecutor : public e172::AbstractAssetExecutor {
public:
    SpriteAssetExecutor() = default;

    // AssetExecutor interface
public:
    virtual e172::Variant proceed(const e172::Variant &value) override;
};

} // namespace proj172::core
