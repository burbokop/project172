#include "abstractassetexecutor.h"

#include <src/engine/additional.h>

namespace e172 {

std::string AbstractAssetExecutor::fullPath(const std::string &path) {
    return Additional::concatenatePaths(executor_path, path);
}

AbstractAssetExecutor::AbstractAssetExecutor() {}

AbstractAssetExecutor::~AbstractAssetExecutor() {}
}
