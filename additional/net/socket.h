#ifndef SOCKET_H
#define SOCKET_H

#ifdef __WIN32__

#include <winsock2.h>
typedef SOCKADDR SOCKADDR_TYPE;
typedef SOCKADDR_IN SOCKADDR_IN_TYPE;
typedef SOCKET SOCKET_TYPE;

#else

#include <sys/socket.h>
#include <netinet/in.h>

typedef sockaddr SOCKADDR_TYPE;
typedef sockaddr_in SOCKADDR_IN_TYPE;
typedef int SOCKET_TYPE;

#endif

#define MAXCONN 16

#include <string>
#include <SDL2/SDL.h>

#include "framebuilder.h"


namespace burbokop {
class Socket {
private:
    SOCKADDR_IN_TYPE addr;
    SOCKET_TYPE sys_socket;
    static bool initialized;

    static std::string err_line;
    static void setError(std::string text);

    bool instance_initialized = true;

    Socket(SOCKET_TYPE sys_socket, SOCKADDR_IN_TYPE addr);
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
