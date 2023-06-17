#include "__capability.h"

__Capability::__Capability(e172::FactoryMeta &&meta)
    : e172::Entity(std::move(meta))
{}
