#ifndef ANIMATORASSETEXECUTOR_H
#define ANIMATORASSETEXECUTOR_H

#include <src/assettools/abstractassetexecutor.h>



class AnimatorAssetExecutor : public e172::AbstractAssetExecutor {
public:
    AnimatorAssetExecutor();

    // AssetExecutor interface
public:
    e172::Variant proceed(const e172::Variant &value) override;
};

#endif // ANIMATORASSETEXECUTOR_H
