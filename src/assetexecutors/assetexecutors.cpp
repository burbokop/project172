#include "assetexecutors.h"

#include "animatorassetexecutor.h"
#include "audioassetexecutor.h"
#include "factoryassetexecutor.h"
#include "nodesassetexecutor.h"
#include "spriteassetexecutor.h"
#include "templatevectorassetexecutor.h"
#include "vectorassetexecutor.h"
#include <src/assettools/assetprovider.h>

void proj172::core::registerAssetExecutors(e172::AssetProvider &ap)
{
    ap.installExecutor("animation", std::make_shared<AnimatorAssetExecutor>());
    ap.installExecutor("sprite", std::make_shared<SpriteAssetExecutor>());
    ap.installExecutor("audio", std::make_shared<AudioAssetExecutor>());
    ap.installExecutor("offset", std::make_shared<VectorAssetExecutor>());
    ap.installExecutor("input", std::make_shared<RecieptAssetExecutor>());
    ap.installExecutor("output", std::make_shared<RecieptAssetExecutor>());
    ap.installExecutor("capabilities", std::make_shared<TemplateVectorAssetExecutor>());
    ap.installExecutor("nodes", std::make_shared<NodesAssetExecutor>());
}
