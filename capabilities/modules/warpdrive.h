#ifndef WARPDRIVE_H
#define WARPDRIVE_H

#include "module.h"

class WarpDrive : public Module {
public:
    WarpDrive();
    WarpDrive(Loadable *tmp);




    // Worker interface
public:
    void loop(Context *context, Event *event);
};

#endif // WARPDRIVE_H
