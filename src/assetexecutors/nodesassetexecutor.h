#ifndef NODESASSETEXECUTOR_H
#define NODESASSETEXECUTOR_H


#include <src/assettools/abstractassetexecutor.h>

class NodesAssetExecutor : public e172::AbstractAssetExecutor {
public:
    NodesAssetExecutor();

    static std::optional<double> parseAngle(const std::string& str);

    // AbstractAssetExecutor interface
public:
    virtual e172::Variant proceed(const e172::Variant &value) override;
};

#endif // NODESASSETEXECUTOR_H
