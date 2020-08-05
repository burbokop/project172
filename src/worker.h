#ifndef WORKER_H
#define WORKER_H



#include "additional/event.h"
#include "object.h"
#include "engine/abstractrenderer.h"


class Context;

class Worker : public Object {
public:
    Worker();
    void virtual tick(Context *context, Event *event) = 0;
    void virtual render(e172::AbstractRenderer *renderer) = 0;
    virtual ~Worker();
};


#endif // WORKER_H
