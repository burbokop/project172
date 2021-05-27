#ifndef BUYWARETASK_H
#define BUYWARETASK_H

#include "task.h"

class BuyWareTask : public Task {
    std::string m_targetWare;
public:
    BuyWareTask(const std::string &ware);

    // Task interface
public:
    virtual void proceed(e172::Context *context) override;
    virtual bool start(e172::Context *context) override;
};

#endif // BUYWARETASK_H
