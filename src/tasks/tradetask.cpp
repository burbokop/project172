#include "buywaretask.h"
#include "sellwaretask.h"
#include "tradetask.h"

void TradeTask::changeState(const std::string &ware, e172::Context *context) {
    if(m_status == Idle || m_status == Selling) {
        m_status = Buying;
        executeChildTask(new BuyWareTask(), context, [this, context](const e172::Variant& ware){
            changeState(ware.toString(), context);
        });
    } else {
        m_status = Selling;
        executeChildTask(new SellWareTask(ware), context, [this, context](const auto&){
            changeState(std::string(), context);
        });
    }
    out() << "trade status changed: " << statusString() << std::endl;
}

TradeTask::TradeTask() {}

void TradeTask::proceed(e172::Context *) {}

bool TradeTask::start(e172::Context *context) {
    m_status = Idle;
    changeState(std::string(), context);
    return true;
}

void TradeTask::initFromCommand(const std::vector<std::string> &args, e172::Context *context) {}
