#pragma once

#include <src/assettools/abstractassetexecutor.h>

namespace proj172::core {

class AnimatorAssetExecutor : public e172::AbstractAssetExecutor {
public:
    AnimatorAssetExecutor() = default;

    // AssetExecutor interface
public:
    e172::Variant proceed(const e172::Variant &value) override;
};

} // namespace proj172::core
