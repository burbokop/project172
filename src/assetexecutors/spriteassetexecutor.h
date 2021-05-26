#ifndef SPRITEASSETEXECUTOR_H
#define SPRITEASSETEXECUTOR_H

#include <src/assettools/abstractassetexecutor.h>



class SpriteAssetExecutor : public e172::AbstractAssetExecutor {
public:
    SpriteAssetExecutor();

    // AssetExecutor interface
public:
    virtual e172::Variant proceed(const e172::Variant &value) override;
};

#endif // SPRITEASSETEXECUTOR_H
