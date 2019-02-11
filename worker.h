#ifndef WORKER_H
#define WORKER_H

#include <vector>

#include "object.h"
#include "renderer.h"
#include "additional/event.h"

class Context;

class Worker : public Object {
public:
    Worker();
    void virtual loop(Context *context, Event *event) = 0;
    void virtual render(Renderer *renderer) = 0;
    virtual ~Worker() = 0;
};

#endif // WORKER_H
