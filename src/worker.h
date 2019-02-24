#ifndef WORKER_H
#define WORKER_H

#include <vector>


#include "additional/event.h"
#include "object.h"
#include "renderer.h"


class Context;

class Worker : public Object {
public:
    Worker();
    void virtual loop(Context *context, Event *event) = 0;
    void virtual render(Renderer *renderer) = 0;
    virtual ~Worker();
};


#endif // WORKER_H
