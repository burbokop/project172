#include "debug.h"


void Debug::onSegSignal(int signum) {
    log("Debug: segmentation fault (signum: " + std::to_string(signum) + ")\n");
    signal(signum, SIG_DFL);
    exit(3);
}

void Debug::log(std::string message) {
    std::ofstream log("debug.log", std::ios::app);
    log << message << "\n";
    log.close();
}

void Debug::init() {
    log("\n--------- DEBUG START ---------\n\n");
    signal(SIGSEGV, onSegSignal);
}
