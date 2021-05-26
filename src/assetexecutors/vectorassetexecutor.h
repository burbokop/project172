#ifndef VECTORASSETEXECUTOR_H
#define VECTORASSETEXECUTOR_H

#include <src/assettools/abstractassetexecutor.h>




class VectorAssetExecutor : public e172::AbstractAssetExecutor {
public:
    VectorAssetExecutor();

    // AssetExecutor interface
public:
    virtual e172::Variant proceed(const e172::Variant &value) override;
};

#endif // VECTORASSETEXECUTOR_H
