#include "netlistener.h"

NetListener::NetListener(Context *context) {
    this->context = context;
    serverSocket = new burbokop::Socket(7788);
}

void NetListener::start() {
    thread = new std::thread(&NetListener::loop, this);
}

void NetListener::loop() {
#ifdef __WIN32__
    while(!quitFlag) {
        burbokop::Socket *connection = serverSocket->listen();
        if(connection) {
            while(!quitFlag) {
                SDL_Surface *image = connection->receiveSurface();
                if(image) {
                    context->addEvent(nullptr, Context::SPAWN_UNIT, image);
                } else {
                    SDL_Delay(1000);
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
    if(thread != nullptr && thread->joinable()) {
        thread->join();
    }
}
