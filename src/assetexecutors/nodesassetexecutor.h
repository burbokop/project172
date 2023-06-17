#pragma once

#include <src/assettools/abstractassetexecutor.h>

class NodesAssetExecutor : public e172::AbstractAssetExecutor {
public:
    NodesAssetExecutor() = default;

    // AbstractAssetExecutor interface
public:
    virtual e172::Variant proceed(const e172::Variant &value) override;
};

