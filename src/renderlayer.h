#pragma once

#include <memory>

namespace e172 {

class AbstractGraphicsProvider;
class GameApplication;

} // namespace e172

namespace proj172 {

std::shared_ptr<e172::AbstractGraphicsProvider> chooseGraphicsProvider(const e172::GameApplication &app);

} // namespace proj172
