#ifndef NETLISTENER_H
#define NETLISTENER_H

#include <thread>

#include <engine/context.h>


#include "additional/net/socket.h"


class NetListener {
private:
    std::thread *thread = nullptr;
    bool quitFlag = false;
    burbokop::Socket *serverSocket = nullptr;
    e172::Context *context = nullptr;
public:
    NetListener(e172::Context *context);
    void start();
    void loop();
    void quit();
};

#endif // NETLISTENER_H
