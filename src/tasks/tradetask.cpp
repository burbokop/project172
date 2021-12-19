#include "buywaretask.h"
#include "sellwaretask.h"
#include "tradetask.h"

#include <src/context.h>

void TradeTask::resetState() {
    m_status = Idle;
}

void TradeTask::updateState(const std::string &ware, e172::Context *context) {
    if(m_status == Idle || m_status == Selling) {
        m_status = Buying;
        executeChildTask(new BuyWareTask(), context, [this, context](const e172::Variant& ware){
            context->later(1000, [this, ware, context](){
                updateState(ware.toString(), context);
            });
        });
    } else {
        m_status = Selling;
        executeChildTask(new SellWareTask(ware), context, [this, context](const auto&){
            context->later(1000, [this, context](){
                updateState(std::string(), context);
            });
        });
    }
    out() << "TradeTask: trade status changed: " << statusString() << std::endl;
}

TradeTask::TradeTask() {}

void TradeTask::proceed(e172::Context *) {}

bool TradeTask::start(e172::Context *context) {
    resetState();
    updateState(std::string(), context);
    return true;
}

void TradeTask::initFromCommand(const std::vector<std::string> &args, e172::Context *context) {}
