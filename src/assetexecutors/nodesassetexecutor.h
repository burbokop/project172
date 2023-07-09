#pragma once

#include <e172/assettools/abstractassetexecutor.h>

namespace proj172::core {

class NodesAssetExecutor : public e172::AbstractAssetExecutor {
public:
    NodesAssetExecutor() = default;

    // AbstractAssetExecutor interface
public:
    virtual e172::Variant proceed(const e172::Variant &value) override;
};

} // namespace proj172::core
