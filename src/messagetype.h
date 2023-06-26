#pragma once

#include <src/context.h>

namespace proj172::core {

enum class MessageType : std::underlying_type<e172::Context::MessageType>::type {
    AddCapability = e172::Context::UserMessage,
    RemoveCapability,
    SpawnExplosive,
    SpawnEngineParticles,
    SpawnUnit,
    SpawnSurface,
    EmergencyMessage,
    BackgroundFlashing,
    FloatingMessage,
    ChangeResolution,
    ChangeFullscreen,
    ChangeAnaglyph
};

inline e172::Context::MessageType operator~(MessageType type)
{
    return static_cast<e172::Context::MessageType>(type);
}

} // namespace proj172::core
