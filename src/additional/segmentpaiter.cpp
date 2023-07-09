#include "segmentpaiter.h"

#include <e172/context.h>
#include <e172/graphics/abstractrenderer.h>
#include <e172/math/math.h>

namespace proj172::core {

SegmentPainter::SegmentPainter(e172::FactoryMeta &&meta)
    : e172::Entity(std::move(meta))
{}

void SegmentPainter::proceed(e172::Context *context, e172::EventHandler *eventHandler)
{
    proceedPhysics(context->deltaTime());
}

void SegmentPainter::render(e172::Context *context, e172::AbstractRenderer *renderer)
{
    static const double c = clock();
    const double time = timer.elapsed();
    const auto lineCount = 3;
    constexpr double coeficient = 0.5;
    const uint32_t colors[5] = { 0xff0000, 0xffff00, 0xff00ff };

    for(auto i = 0; i < lineCount; ++i) {
        srand(i + reinterpret_cast<uintptr_t>(this) + c);
        const double random = rand() / static_cast<double>(std::numeric_limits<decltype (rand())>::max()) * 2 - 1;
        const double alpha = random * 0.001 * time * coeficient;

        for(int j = 0; j < 2; ++j) {
            srand(i + random + reinterpret_cast<uintptr_t>(this));
            const double rand2 = rand() / static_cast<double>(std::numeric_limits<decltype (rand())>::max()) * 2 - 1;
            const double beta = rand2 * std::sin(0.001 * time * coeficient + rand2);

            renderer->drawLineShifted(position(),
                                      position()
                                          + e172::Vector<double>::createByAngle(
                                              50, alpha + j * beta * e172::Math::Pi / 4),
                                      colors[i]);
        }
    }
}

} // namespace proj172::core
