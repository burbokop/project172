#pragma once

#include <memory>

namespace e172 {

class AbstractGraphicsProvider;
class AbstractEventProvider;
class AbstractAudioProvider;
class GameApplication;

} // namespace e172

namespace proj172 {

struct Platform
{
    std::shared_ptr<e172::AbstractGraphicsProvider> graphicsProvider;
    std::shared_ptr<e172::AbstractEventProvider> eventProvider;
    std::shared_ptr<e172::AbstractAudioProvider> audioProvider;
};

Platform choosePlatform(const e172::GameApplication &app);

} // namespace proj172
