#include "debug.h"

bool Debug::errEnbled = false;
bool Debug::outEnbled = false;

unsigned Debug::lastError = 0;
std::string Debug::lastSite = "";

#ifdef __unix__
#include <execinfo.h>  // for backtrace
#include <dlfcn.h>     // for dladdr
#endif
#include <cxxabi.h>    // for __cxa_demangle

#include <string>
#include <sstream>


int get_sym_name(void *addr) {
#ifdef __unix__
    Dl_info info;
    int res = dladdr(addr, &info);
    std::cout << info.dli_fname << ": " << info.dli_sname << "\n\n";
    return res;
#endif
    (void)addr;
    return -100;
}


void Debug::onSegSignal(int signum) {
#ifdef __unix__
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

#endif
    exit(1);
}

std::string Debug::codeToString(unsigned code) {
    switch (code) {
        case 0: return  "NO_ERROR";
        case APPEAL_TO_REMOVED: return "APPEAL_TO_REMOVED";
        case ASSET_KEY_NOT_FOUND : return "ASSET_KEY_NOT_FOUND";
        case UNKNOWN_ASSET_CLASS : return "UNKNOWN_ASSET_CLASS";
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

void Debug::err(unsigned code, std::string site, std::string comment) {
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


void process_mem_usage(double& vm_usage, double& resident_set) {
#ifdef __unix__
    vm_usage = 0.0;
    resident_set = 0.0;
    unsigned long vsize;
    long rss;
    {
        std::string ignore;
        std::ifstream ifs("/proc/self/stat", std::ios_base::in);
        ifs >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore
            >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore
            >> ignore >> ignore >> vsize >> rss;
    }

    long page_size_kb = sysconf(_SC_PAGE_SIZE) / 1024; // in case x86-64 is configured to use 2MB pages
    vm_usage = vsize / 1024.0;
    resident_set = rss * page_size_kb;
#endif
    (void)vm_usage;
    (void)resident_set;
}

double Debug::getRuntimeVM() {
    double vm, rss;
    process_mem_usage(vm, rss);
    return vm;
}

double Debug::getRuntimeRSS() {
    double vm, rss;
    process_mem_usage(vm, rss);
    return rss;
}





