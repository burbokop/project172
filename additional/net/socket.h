#ifndef SOCKET_H
#define SOCKET_H

#ifdef __WIN32__

#include <winsock2.h>
typedef SOCKET CROSS_SOCKET;
typedef SOCKADDR CROSS_SOCKADDR;
typedef SOCKADDR_IN CROSS_SOCKADDR_IN;

#else

#include <sys/socket.h>
#include <netinet/in.h>
typedef int CROSS_SOCKET;
typedef sockaddr CROSS_SOCKADDR;
typedef sockaddr_in CROSS_SOCKADDR_IN;

#endif

#define MAXCONN 16

#include <string>
#include <SDL2/SDL.h>

#include "framebuilder.h"


namespace burbokop {
class Socket {
private:
    CROSS_SOCKADDR_IN addr;
    CROSS_SOCKET sys_socket;

    static bool initialized;

    static std::string err_line;
    static void setError(std::string text);

    bool instance_initialized = true;

    Socket(CROSS_SOCKET sys_socket, CROSS_SOCKADDR_IN addr);
public:
    static bool init();

    Socket(unsigned short port, std::string ip = "127.0.0.1");
    Socket *listen();
    bool connect();
    void send(std::string massage);
    void send(const char *massage, int length);
    char *recv(int length);
    void close();

    void sendFrame(std::vector<char> data);
    std::vector<char> receiveFrame();

    void sendSurface(SDL_Surface *surface);
    SDL_Surface *receiveSurface();

    static std::string getError();
};
}
#endif // SOCKET_H
