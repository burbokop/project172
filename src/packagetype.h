#pragma once

#include <src/net/common.h>

namespace proj172::core {

enum class PackageType : std::underlying_type<e172::GamePackageType>::type {
    AddCapability = std::underlying_type<e172::GamePackageType>::type(
        e172::GamePackageType::UserType),
    RemoveCapability
};

inline e172::PackageType operator~(PackageType type)
{
    return static_cast<e172::PackageType>(type);
}

} // namespace proj172::core
