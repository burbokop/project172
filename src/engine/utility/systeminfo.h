#ifndef SYSTEMINFO_H
#define SYSTEMINFO_H

namespace e172 {


class SystemInfo {
public:
    struct MemotyUsageInfo {
        long rss;
        long vm;
        bool isValid = false;
    };
    static bool memoryUsageKb(long* vmrss_kb, long* vmsize_kb);
    static MemotyUsageInfo memoryUsageKb();
};

}
#endif // SYSTEMINFO_H
