#ifndef NETLISTENER_H
#define NETLISTENER_H

#include <thread>

#include "additional/net/socket.h"

#include "context.h"

class NetListener {
private:
    std::thread *thread;
    bool quitFlag = false;
    burbokop::Socket *serverSocket;
    Context *context;
public:
    NetListener(Context *context);
    void start();
    void loop();
    void quit();
};

#endif // NETLISTENER_H
