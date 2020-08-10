#ifndef WORKER_H
#define WORKER_H




#include "object.h"

#include <engine/graphics/abstractrenderer.h>
#include <engine/abstracteventhandler.h>



class Context;

class Worker : public Object {
public:
    Worker();
    void virtual tick(Context *context, e172::AbstractEventHandler *eventHandler) = 0;
    void virtual render(e172::AbstractRenderer *renderer) = 0;
    virtual ~Worker();
};


#endif // WORKER_H
