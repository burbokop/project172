#ifndef DEBUG_H
#define DEBUG_H

#include <string>
#include <fstream>
#include <signal.h>
#include <iostream>
#include <stdarg.h>
#include <stdio.h>
#include <execinfo.h>
#include <stdlib.h>
#include <unistd.h>


#define DEBUG_IMPRINT std::string(typeid(*this).name()) + "::" + std::string(__func__)
#define STATIC_DEBUG_IMPRINT "STATIC FUNCTION: " + std::string(__func__)



class Debug {
public:
    static const uint8_t APPEAL_TO_REMOVED = 1;
    static const uint8_t ASSET_KEY_NOT_FOUND = 2;
    static const uint8_t UNKNOWN_ASSET_KEY = 3;
    static const uint8_t SEGMENTATION_FAULT = 4;

private:
    static bool errEnbled;
    static bool outEnbled;

    static uint8_t lastError;
    static std::string lastSite;

    static void onSegSignal [[ noreturn ]] (int signum);
    static std::string codeToString(uint8_t code);
public:


    static void log(std::string message);
    static void out(std::string message);
    static void err(uint8_t code, std::string site, std::string comment = "");
    static void init(bool out = false, bool err = false);

    static double getRuntimeVM();
    static double getRuntimeRSS();


};

#endif // DEBUG_H
