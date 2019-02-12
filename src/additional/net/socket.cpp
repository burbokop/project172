#include "socket.h"


inline int inline_connect(CROSS_SOCKET socket, const struct sockaddr *name, int namelen) {
    return connect(socket, name, namelen);
}

inline int inline_listen(CROSS_SOCKET socket, int backlog) {
    return listen(socket, backlog);
}

inline int inline_send(CROSS_SOCKET socket, const char *buffer, int length, int flags) {
    return send(socket, buffer, length, flags);
}

inline int inline_recv(CROSS_SOCKET socket, char *buffer, int length, int flags) {
    return recv(socket, buffer, length, flags);
}

using namespace burbokop;

bool Socket::initialized = false;
std::string Socket::err_line = "";

void Socket::setError(std::string text) {
    err_line += text + " : ";
}

std::string Socket::getError() {
    return err_line;
}

bool Socket::init() {
#ifdef __WIN32__
    WSADATA wsaData;
    WORD DLLVersion = MAKEWORD(2, 1);
    if(WSAStartup(DLLVersion, &wsaData) != 0) {
        setError("<WSA loading error>");
        return false;
    } else {
        initialized = true;
        return true;
    }
#endif
}



Socket::Socket(CROSS_SOCKET sys_socket, CROSS_SOCKADDR_IN addr) {
    this->sys_socket = sys_socket;
    this->addr = addr;
}

Socket::Socket(unsigned short port, std::string ip) {
    if(!initialized) {
        if(!init()) {
            instance_initialized = false;
        }
    }
#ifdef __WIN32__

    if(instance_initialized) {
        addr.sin_addr.s_addr = inet_addr(ip.c_str());
        addr.sin_port = htons(port);
        addr.sin_family = AF_INET;

        sys_socket = socket(AF_INET, SOCK_STREAM, 0);
    }
#endif
}

Socket *Socket::listen() {
#ifdef __WIN32__

    int sizeofaddr = sizeof(addr);
    bind(sys_socket, reinterpret_cast<SOCKADDR*>(&addr), sizeofaddr);
    inline_listen(sys_socket, MAXCONN);

    SOCKET connection_socket;
    connection_socket = accept(sys_socket, reinterpret_cast<SOCKADDR*>(&addr), &sizeofaddr);
    if(connection_socket != 0) {
        return new Socket(connection_socket, addr);
    }
    setError("<listen error>");
    return nullptr;
#endif
}

bool burbokop::Socket::connect() {
#ifdef __WIN32__

    if(inline_connect(sys_socket, reinterpret_cast<SOCKADDR*>(&addr), sizeof(addr))) {
        setError("<connection error>");
        return false;
    }
    return true;
#endif
}

void burbokop::Socket::send(std::string massage) {
    inline_send(sys_socket, massage.c_str(), static_cast<int>(massage.length()), 0);
}

void burbokop::Socket::send(const char *massage, int length) {
    inline_send(sys_socket, massage, length, 0);
}

char *burbokop::Socket::recv(int length) {
    char *buffer = new char[length];
    inline_recv(sys_socket, buffer, length, 0);
    return buffer;
}

void Socket::close() {
#ifdef __WIN32__

    closesocket(sys_socket);
#endif
}

#include <iostream>

void Socket::sendFrame(std::vector<char> data) {
    std::vector<char> frame = FrameBuilder::cover(data);
    inline_send(sys_socket, &frame[0], static_cast<int>(frame.size()), 0);
}
#include <iostream>
#include <sstream>
std::string H(std::vector<char> data) {
    std::stringstream stream;
    for(char c : data) {
        stream << std::hex << ((static_cast<unsigned int>(c)) & 0x000000ff) << " : ";
    }
    std::string result(stream.str());
    return result;
}

std::vector<char> Socket::receiveFrame() {
    std::vector<char> frame;
    ssize_t bytes_read = 0;
    unsigned int i = 0;

    while(true) {
        char byte[1];
        bytes_read = inline_recv(sys_socket, byte, 1, 0);


        if(bytes_read == 0) {
            std::cout << "bytes_read: " << std::dec << bytes_read << "\n";
            //frame.push_back(0x7E);
            break;
        } else if(bytes_read < 0) {
            setError("<error: package lost>");
            std::cout << "error: bytes_read: " << std::dec << bytes_read << ". package lost\n";
            break;
        }
        frame.push_back(byte[0]);
        if(i > 2 && byte[0] == 0x7E) {
            std::cout << "byte[0] == 0x7E\n";
            break;
        }
        i++;
    }

    std::cout << "frame recieved: " << H(frame) << "\n";

    std::vector<char> result = FrameBuilder::uncover(frame);
    if(result.size() <= 0) {
        setError("<checksum error or empty frame>");
        std::cout << "checksum error or empty frame\n";
    }
    return result;
}

void Socket::sendSurface(SDL_Surface *surface) {
    char *bitmap = reinterpret_cast<char*>(surface->pixels);
    size_t bitmapsize = sizeof (Uint32) * surface->w * surface->h;

    std::vector<char> data = std::vector<char>(bitmap, bitmap + bitmapsize);

    data.push_back((surface->w >> 24) & 0x000000ff);
    data.push_back((surface->w >> 16) & 0x000000ff);
    data.push_back((surface->w >> 8) & 0x000000ff);
    data.push_back((surface->w >> 0) & 0x000000ff);

    data.push_back((surface->h >> 24) & 0x000000ff);
    data.push_back((surface->h >> 16) & 0x000000ff);
    data.push_back((surface->h >> 8) & 0x000000ff);
    data.push_back((surface->h >> 0) & 0x000000ff);

    sendFrame(data);
}

SDL_Surface *Socket::receiveSurface() {
    std::vector<char> *data = new std::vector<char>(receiveFrame());
    unsigned long long size = data->size();
    if(size <= 0) return nullptr;

    char *bitmap = &data->at(0);


    int wigth = bitmap[size - 8] | bitmap[size - 7] | bitmap[size - 6] | bitmap[size - 5];
    int height = bitmap[size - 4] | bitmap[size - 3] | bitmap[size - 2] | bitmap[size - 1];

    std::cout << "wigth: " << wigth << " height: " << height << "\n";

    const int format = 4;
    SDL_Surface *result = SDL_CreateRGBSurfaceFrom(bitmap, wigth, height, format * 8, format * wigth, 0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000);
    //delete [] bitmap;
    return result;
}

