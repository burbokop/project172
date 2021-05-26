#ifndef TEMPLATEVECTORASSETEXECUTOR_H
#define TEMPLATEVECTORASSETEXECUTOR_H

#include <src/assettools/abstractassetexecutor.h>



class TemplateVectorAssetExecutor : public e172::AbstractAssetExecutor {
public:
    TemplateVectorAssetExecutor();

    // AbstractAssetExecutor interface
public:
    virtual e172::Variant proceed(const e172::Variant &value) override;
};



#endif // TEMPLATEVECTORASSETEXECUTOR_H
