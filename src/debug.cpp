#include "debug.h"

bool Debug::errEnbled = false;
bool Debug::outEnbled = false;

uint8_t Debug::lastError = 0;
std::string Debug::lastSite = "";

#include <execinfo.h>  // for backtrace
#include <dlfcn.h>     // for dladdr
#include <cxxabi.h>    // for __cxa_demangle

#include <string>
#include <sstream>


int get_sym_name(void *addr) {
    Dl_info info;
    int res = dladdr(addr, &info);
    std::cout << info.dli_fname << ": " << info.dli_sname << "\n\n";
    return res;
}


#include <near.h>
void Debug::onSegSignal(int signum) {
    err(SEGMENTATION_FAULT, STATIC_DEBUG_IMPRINT, std::to_string(signum));



    void *addrlist[10];
    int addrlen = backtrace(addrlist, sizeof(addrlist) / sizeof(void*));
    char **symbollist = backtrace_symbols(addrlist, addrlen);

    std::cout << '\n';
    for (int j = 0; j < addrlen; j++) {
        std::cout << symbollist[j] << "\n";
    }
    std::cout << '\n';

    free(symbollist);

    exit(1);
}

std::string Debug::codeToString(uint8_t code) {
    switch (code) {
        case 0: return  "NO_ERROR";
        case APPEAL_TO_REMOVED: return "APPEAL_TO_REMOVED";
        case ASSET_KEY_NOT_FOUND : return "ASSET_KEY_NOT_FOUND";
        case UNKNOWN_ASSET_KEY : return "UNKNOWN_ASSET_KEY";
        case SEGMENTATION_FAULT : return "SEGMENTATION_FAULT";
        default: return "UNKNOWN_ERROR";
    }
}

void Debug::log(std::string message) {
    std::ofstream log("debug.log", std::ios::app);
    log << message << "\n";
    log.close();
}


void Debug::out(std::string message) {
    if(outEnbled) {
        std::cout << "MESSAGE: <" << message << ">\n";
    }
}

void Debug::err(uint8_t code, std::string site, std::string comment) {
    if(errEnbled && code != 0) {
        if(code != lastError || site != lastSite) {
            if(comment == "") {
                std::cerr << "ERROR: <code: " << codeToString(code) << " appearance: " << site << ">\n";
            } else {
                std::cerr << "ERROR: <code: " << codeToString(code) << " ( " << comment << " ) appearance: " << site << ">\n";
            }
        }
        lastError = code;
        lastSite = site;
    }
}


void Debug::init(bool out, bool err) {
    outEnbled = out;
    errEnbled = err;
    log("\n--------- DEBUG START ---------\n\n");
    signal(SIGSEGV, onSegSignal);
}

