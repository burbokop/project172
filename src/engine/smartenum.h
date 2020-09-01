#ifndef KSMARTENUM_H
#define KSMARTENUM_H

#include <string>
#include <vector>
#include <map>
#include <sstream>

namespace e172 {

struct __enum_tools {
    static std::string trim(const std::string& str);
    static std::vector<std::string> split(const std::string& s, char delimiter);
    static std::map<uint8_t, std::string> __va_args_to_map(const std::string &str);
};

}
#define E172_SMART_ENUM(TYPE, ...) struct TYPE { enum Enum { __VA_ARGS__ }; static inline const auto names = e172::__enum_tools::__va_args_to_map(#__VA_ARGS__); };



#endif // KSMARTENUM_H
