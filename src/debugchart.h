#pragma once

#include <memory>

namespace e172 {
class GameApplication;
}

namespace proj172 {

namespace core {
class ChartView;
}

std::unique_ptr<core::ChartView> addDebugChartToApp(e172::GameApplication &app);

} // namespace proj172
