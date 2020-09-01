#include "netlistener.h"

NetListener::NetListener(e172::Context *context) {
    this->context = context;
    serverSocket = new burbokop::Socket(7788);
}

void NetListener::start() {
    // TO DO thread = new std::thread(&NetListener::loop, this);
}

void NetListener::loop() {
#ifdef __WIN32__
    while(!quitFlag) {
        burbokop::Socket *connection = serverSocket->listen();
        if(connection) {
            while(!quitFlag) {
                SDL_Surface *image = connection->receiveSurface();
                if(image) {
                    // TO DO context->addEvent(nullptr, e172::Context::SPAWN_UNIT, image);
                } else {
                    // TO DO SDL_Delay(1000);
                }
            }
        } else {
            SDL_Delay(1000);
        }
    }
#endif
}

void NetListener::quit() {
    serverSocket->close();
    quitFlag = true;

    // TO DO
    //if(thread != nullptr && thread->joinable()) {
    //    thread->join();
    //}
}
