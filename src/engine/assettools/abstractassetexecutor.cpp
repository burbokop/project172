#include "abstractassetexecutor.h"

#include <filesystem.h>
namespace e172 {

std::string AbstractAssetExecutor::fullPath(const std::string &path) {
    return FileSystem::addPrefix(path, executor_path);
}

AbstractAssetExecutor::AbstractAssetExecutor() {}

AbstractAssetExecutor::~AbstractAssetExecutor() {}
}
