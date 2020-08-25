#ifndef NETLISTENER_H
#define NETLISTENER_H


#include <src/engine/context.h>


#include <src/additional/net/socket.h>
#include <thread>

class NetListener {
private:
    // TO DO std::thread *thread = nullptr;
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
