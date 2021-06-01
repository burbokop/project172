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
    virtual void initFromCommand(const std::vector<std::string> &args, std::list<std::string> *lines, e172::Context *context) override;
};

#endif // SELLWARETASK_H
