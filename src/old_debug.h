#ifndef DEBUG_H
#define DEBUG_H

#include <string>
#include <fstream>
#include <signal.h>
#include <iostream>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <src/engine/smartenum.h>

namespace old {

class Debug {
public:
    E172_SMART_ENUM(Code,
        APPEAL_TO_REMOVED,
        ASSET_ID_NOT_FOUND,
        ASSET_TYPE_NOT_REGISTERED,
        ASSET_NOT_CONTAINS_ID,
        ASSET_NOT_CONTAINS_CLASS_NAME,
        EXECUTOR_NOT_INSTALLED_FOR_ASSET,
        ASSET_IS_NULL,
        SEGMENTATION_FAULT
    )




private:
    static bool errEnbled;
    static bool outEnbled;

    static unsigned lastError;
    static std::string lastSite;

    static void onSegSignal [[ noreturn ]] (int signum);
public:


    static void log(std::string message);
    static void out(std::string message);
    static void err(Debug::Code::Enum code, std::string site, std::string comment = "");
    static void init(bool out = false, bool err = false);

    static double getRuntimeVM();
    static double getRuntimeRSS();


};

}
#endif // DEBUG_H
