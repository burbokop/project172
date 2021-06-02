#ifndef SELLWARETASK_H
#define SELLWARETASK_H

#include "task.h"

class SellWareTask : public Task {
public:
    SellWareTask();

    // Task interface
public:
    virtual void proceed(e172::Context *context) override;
    virtual bool start(e172::Context *context) override;
    virtual void initFromCommand(const std::vector<std::string> &args, e172::Context *context) override;
};

#endif // SELLWARETASK_H
