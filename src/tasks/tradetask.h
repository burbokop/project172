#ifndef TRADETASK_H
#define TRADETASK_H

#include "task.h"
#include <src/smartenum.h>

namespace proj172::core {

class TradeTask : public Task {
    e172_enum_member(Status, status,
                     Idle,
                     Buying,
                     Selling
                     )


    void resetState();
    void updateState(const std::string& ware, e172::Context *context);
public:
    TradeTask();

    // Task interface
public:
    virtual void proceed(e172::Context *) override;
    virtual bool start(e172::Context *context) override;
    virtual void initFromCommand(const std::vector<std::string> &args, e172::Context *context) override;
};

} // namespace proj172::core

#endif // TRADETASK_H
