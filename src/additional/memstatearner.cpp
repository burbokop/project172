#include "memstatearner.h"

#include <src/context.h>
#include <src/debug.h>
#include <src/eventhandler.h>
#include <src/graphics/abstractrenderer.h>
#include <src/utility/systeminfo.h>

namespace proj172::core {

MemStatEarner::MemStatEarner(e172::FactoryMeta &&meta)
    : e172::Entity(std::move(meta))
{
    vm_diff_ac.setAutoResetEnabled(true);
    vm_diff_ac.setAutoResetError(0.5);

    rss_diff_ac.setAutoResetEnabled(true);
    rss_diff_ac.setAutoResetError(0.5);
}

void MemStatEarner::proceed(e172::Context *context, e172::EventHandler *e)
{
    if(e->keySinglePressed(e172::ScancodeF3)) {
        enabled = !enabled;
    }

    if(enabled) {
        const auto memUsage = e172::sysinfo::memoryUsage().unwrap();
        vm = memUsage.vm;
        rss = memUsage.rss;
        vm_d = vm_size_differentiator.proceed(vm) * 0.001;
        rss_d = rss_differentiator.proceed(rss) * 0.001;
        vm_d_average = vm_diff_ac.proceed(vm_d);
        rss_d_average = rss_diff_ac.proceed(rss_d);

        proceed_delay = context->proceedDelay();
        proceed_delay_avrg = proceed_delay_ac.proceed(proceed_delay);
        render_delay = context->renderDelay();
        render_delay_avrg = render_delay_ac.proceed(render_delay);
    }
}

void MemStatEarner::render(e172::Context *context, e172::AbstractRenderer *renderer)
{
    if(enabled) {
        e172::TextFormat textFormat;
        textFormat.setFontSize(12);
        renderer->drawString("vm: " + std::to_string(vm),
                             e172::Vector<double>(200, 10),
                             0xff8800,
                             textFormat);

        renderer->drawString("vm_diff: " + std::to_string(vm_d_average),
                             e172::Vector<double>(200, 30),
                             0xff8800,
                             textFormat);

        renderer->drawString("rss: " + std::to_string(rss),
                             e172::Vector<double>(200, 50),
                             0xff8800,
                             textFormat);

        renderer->drawString("rss_diff: " + std::to_string(rss_d_average),
                             e172::Vector<double>(200, 70),
                             0xff8800,
                             textFormat);

        renderer->drawString("proceed delay: " + std::to_string(proceed_delay_avrg),
                             e172::Vector<double>(200, 90),
                             0xff00ff,
                             textFormat);

        renderer->drawString("render delay: " + std::to_string(render_delay_avrg),
                             e172::Vector<double>(200, 110),
                             0xff00ff,
                             textFormat);

        renderer->drawString(std::to_string(vm),
                             e172::Vector<double>(400, 10),
                             0xff8800,
                             textFormat);

        renderer->drawString(std::to_string(vm_d),
                             e172::Vector<double>(400, 30),
                             0xff8800,
                             textFormat);

        renderer->drawString(std::to_string(rss),
                             e172::Vector<double>(400, 50),
                             0xff8800,
                             textFormat);

        renderer->drawString(std::to_string(rss_d),
                             e172::Vector<double>(400, 70),
                             0xff8800,
                             textFormat);

        renderer->drawString(std::to_string(proceed_delay),
                             e172::Vector<double>(400, 90),
                             0xff00ff,
                             textFormat);

        renderer->drawString(std::to_string(render_delay),
                             e172::Vector<double>(400, 110),
                             0xff00ff,
                             textFormat);
    }
}

} // namespace proj172::core
