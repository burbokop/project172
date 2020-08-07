#include "assetexecutor.h"

#include <filesystem.h>

std::string AssetExecutor::fullPath(const std::string &path) {
    return FileSystem::addPrefix(path, executor_path);
}

AssetExecutor::AssetExecutor()
{

}

AssetExecutor::~AssetExecutor()
{

}
