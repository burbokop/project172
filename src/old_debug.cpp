#include "old_debug.h"


#ifdef __unix__
#include <execinfo.h>  // for backtrace
#include <dlfcn.h>     // for dladdr
#include <string.h>
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



namespace old {

bool Debug::errEnbled = false;
bool Debug::outEnbled = false;

unsigned Debug::lastError = 0;
std::string Debug::lastSite = "";


void Debug::onSegSignal(int signum) {
#ifdef __unix__
    err(Code::SEGMENTATION_FAULT, __PRETTY_FUNCTION__, std::to_string(signum));

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

Debug::ProcessStat Debug::proc_stat() {
    ProcessStat result;
#ifdef __unix__
    long rss;
    {
        std::string ignore;
        std::ifstream ifs("/proc/self/stat", std::ios_base::in);
        ifs >> ignore >> ignore >> result.uid >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore
            >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore
            >> ignore >> ignore >> result.vsize_origin >> rss;
    }

    result.page_size = _SC_PAGE_SIZE;
    result.sc = sysconf(result.page_size);
    long page_size_kb = result.sc / 1024; // in case x86-64 is configured to use 2MB pages
    result.vm = result.vsize_origin / 1024.0;
    result.rss = rss * page_size_kb;
#endif
    return result;
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
    if(errEnbled) {
        if(code != lastError || site != lastSite) {
            if(comment == "") {
                std::cerr << "ERROR: <code: " << Code::names.at(code) << " appearance: " << site << ">\n";
            } else {
                std::cerr << "ERROR: <code: " << Code::names.at(code) << " ( " << comment << " ) appearance: " << site << ">\n";
            }
        }
        lastError = code;
        lastSite = site;
    }
}


const int Debug::static_call = []{
    signal(SIGSEGV, onSegSignal);
    return 0;
}();

void Debug::init(bool out, bool err) {
    outEnbled = out;
    errEnbled = err;
    log("\n--------- DEBUG START ---------\n\n");
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




int Debug::get_memory_usage_kb(long* vmrss_kb, long* vmsize_kb)
{
    /* Get the the current process' status file from the proc filesystem */
    FILE* procfile = fopen("/proc/self/status", "r");

    long to_read = 8192;
    char buffer[to_read];
    int read = fread(buffer, sizeof(char), to_read, procfile);
    fclose(procfile);

    short found_vmrss = 0;
    short found_vmsize = 0;
    char* search_result;

    /* Look through proc status contents line by line */
    char delims[] = "\n";
    char* line = strtok(buffer, delims);

    while (line != NULL && (found_vmrss == 0 || found_vmsize == 0) )
    {
        search_result = strstr(line, "VmRSS:");
        if (search_result != NULL)
        {
            sscanf(line, "%*s %ld", vmrss_kb);
            found_vmrss = 1;
        }

        search_result = strstr(line, "VmSize:");
        if (search_result != NULL)
        {
            sscanf(line, "%*s %ld", vmsize_kb);
            found_vmsize = 1;
        }

        line = strtok(NULL, delims);
    }

    return (found_vmrss == 1 && found_vmsize == 1) ? 0 : 1;
}

}


