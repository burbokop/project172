#ifndef DEBUG_H
#define DEBUG_H

#include <string>
#include <fstream>
#include <signal.h>

class Debug {
private:
    static void onSegSignal(int signum);
public:
    static void log(std::string message);
    static void init();
};

#endif // DEBUG_H
