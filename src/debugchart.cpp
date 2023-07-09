#include "debugchart.h"

#include "additional/chartview.h"
#include <e172/gameapplication.h>

namespace proj172 {

std::unique_ptr<core::ChartView> addDebugChartToApp(e172::GameApplication &app)
{
    auto chartView = e172::FactoryMeta::makeUniq<core::ChartView>();

    const auto f = [](double x, double x0) {
        if (x0 != e172::Math::null) {
            const auto a = (1 - x / x0);
            if (a != e172::Math::null) {
                return x * std::abs(1 / a - 1) * 2;
            }
        }
        return 0.;
    };

    //const auto f = [](double x, double x0){
    //    return std::pow(2, x) - 1;
    //};

    chartView->setOffset({100, 500});
    chartView->setFunction(f);
    chartView->setCoeficient(200);
    chartView->setPointCount(300);
    app.addEntity(chartView.get());
    return std::move(chartView);
}

} // namespace proj172
