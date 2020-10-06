#include "memstatearner.h"

#include <src/engine/abstracteventhandler.h>
#include <src/engine/context.h>
#include <src/engine/debug.h>
#include <src/engine/graphics/abstractrenderer.h>
#include <src/engine/utility/systeminfo.h>

MemStatEarner::MemStatEarner() {
    vm_diff_ac.setEnableAutoReset(true);
    vm_diff_ac.setAutoResetError(0.5);

    rss_diff_ac.setEnableAutoReset(true);
    rss_diff_ac.setAutoResetError(0.5);
}


void MemStatEarner::proceed(e172::Context *context, e172::AbstractEventHandler *e) {
    if(e->keySinglePressed(e172::ScancodeF3)) {
        enabled = !enabled;
    }

    if(enabled) {
        const auto memUsage = e172::SystemInfo::memoryUsageKb();
        vm = memUsage.vm;
        rss = memUsage.rss;
        vm_d = vm_size_differentiator.proceed(vm) * 0.001;
        rss_d = rss_differentiator.proceed(rss) * 0.001;
        vm_d_average = vm_diff_ac.proceed(vm_d);
        rss_d_average = rss_diff_ac.proceed(rss_d);

        proceed_delay = proceed_delay_ac.proceed(context->proceedDelay());
        render_delay = render_delay_ac.proceed(context->renderDelay());
    }
}

void MemStatEarner::render(e172::AbstractRenderer *renderer) {
    if(enabled) {
        e172::TextFormat textFormat;
        textFormat.setFontSize(12);
        renderer->drawString("vm: " + std::to_string(vm), e172::Vector(200, 10), 0xff8800, textFormat);
        renderer->drawString("vm_diff: " + std::to_string(vm_d_average), e172::Vector(200, 30), 0xff8800, textFormat);
        renderer->drawString("rss: " + std::to_string(rss), e172::Vector(200, 50), 0xff8800, textFormat);
        renderer->drawString("rss_diff: " + std::to_string(rss_d_average), e172::Vector(200, 70), 0xff8800, textFormat);
        renderer->drawString("proceed delay: " + std::to_string(proceed_delay), e172::Vector(200, 90), 0xff00ff, textFormat);
        renderer->drawString("render delay: " + std::to_string(render_delay), e172::Vector(200, 110), 0xff00ff, textFormat);
    }
}
