#include "systeminfo.h"

#ifdef __unix__
#include <string.h>
#include <stdio.h>
#endif

bool e172::SystemInfo::memoryUsageKb(long *vmrss_kb, long *vmsize_kb) {
#ifdef __unix__
    FILE* procfile = fopen("/proc/self/status", "r");

    long to_read = 8192;
    char buffer[to_read];
    fread(buffer, sizeof(char), to_read, procfile);
    fclose(procfile);

    bool found_vmrss = false;
    bool found_vmsize = false;
    char* search_result;

    /* Look through proc status contents line by line */
    char delims[] = "\n";
    char* line = strtok(buffer, delims);

    while (line != NULL && (found_vmrss == false || found_vmsize == false)) {
        search_result = strstr(line, "VmRSS:");
        if (search_result != NULL) {
            sscanf(line, "%*s %ld", vmrss_kb);
            found_vmrss = true;
        }

        search_result = strstr(line, "VmSize:");
        if (search_result != NULL) {
            sscanf(line, "%*s %ld", vmsize_kb);
            found_vmsize = true;
        }
        line = strtok(NULL, delims);
    }
    return found_vmrss && found_vmsize;
#else
    (void)vmrss_kb;
    (void)vmsize_kb;
    return false;
#endif
}

e172::SystemInfo::MemotyUsageInfo e172::SystemInfo::memoryUsageKb() {
    MemotyUsageInfo result;
    result.isValid = memoryUsageKb(&result.rss, &result.vm);
    return result;
}
