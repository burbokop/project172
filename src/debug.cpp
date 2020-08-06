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
#else
    (void)addr;
    return -100;
#endif
}


void Debug::onSegSignal(int signum) {
#ifdef __unix__
    err(Code::SEGMENTATION_FAULT, STATIC_DEBUG_IMPRINT, std::to_string(signum));

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

void Debug::err(Code::Enum code, std::string site, std::string comment) {
    if(errEnbled && code != Code::NO_ERROR) {
        if(code != lastError || site != lastSite) {
            if(comment == "") {
                std::cerr << "ERROR: <code: " << Code::__map.at(code) << " appearance: " << site << ">\n";
            } else {
                std::cerr << "ERROR: <code: " << Code::__map.at(code) << " ( " << comment << " ) appearance: " << site << ">\n";
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





