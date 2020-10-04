#include "debug.h"

#include <iostream>

#include <signal.h>    // for signal
#include <execinfo.h>  // for backtrace
#include <dlfcn.h>     // for dladdr

namespace e172 {



std::function<void(const std::string &, Debug::MessageType)> Debug::m_proceedMessage = [](const std::string &data, Debug::MessageType type){
    if(type == Debug::PrintMessage) {
        std::cout << data << std::endl;
    } else if(type == Debug::WarningMessage) {
        std::cout << "\033[33m" << data << "\033[0m" << std::endl;
    } else if(type == Debug::FatalMessage) {
        std::cout << "\033[31m" << data << "\033[0m" << std::endl;
    }
};

std::string Debug::m_separator = " ";

void Debug::setSeparator(const std::string &separator) {
    m_separator = separator;
}

int Debug::functionName(void *addr, std::string *fname, std::string *sname) {
#ifdef __unix__
    Dl_info info;
    int res = dladdr(addr, &info);
    *fname = info.dli_fname;
    *sname = info.dli_sname;
    return res;
#else
    (void)addr;
    return -100;
#endif
}

std::vector<std::string> Debug::stackTrace() {
    std::vector<std::string> result;
#ifdef __unix__
    void *addrlist[10];
    int addrlen = backtrace(addrlist, sizeof(addrlist) / sizeof(void*));
    char **symbollist = backtrace_symbols(addrlist, addrlen);

    result.resize(addrlen);
    for (int j = 0; j < addrlen; j++) {
        result[j] = symbollist[j];
    }

    free(symbollist);
#endif
    return result;
}

void Debug::installSigsegvHandler(void(*function)(int)) {
#ifdef __unix__
    signal(SIGSEGV, function);
#endif
}

void Debug::installHandler(const std::function<void (const std::string &, Debug::MessageType)> &handler) {
    m_proceedMessage = handler;
}



}
