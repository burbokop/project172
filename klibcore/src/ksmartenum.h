#ifndef KSMARTENUM_H
#define KSMARTENUM_H

#include <string>
#include <vector>
#include <map>
#include <sstream>

struct KSmartEnumTools {
    static std::string trim(const std::string& str);
    static std::vector<std::string> split(const std::string& s, char delimiter);
    static std::map<uint8_t, std::string> __va_args_to_map(const std::string &str);
};

#define K_SMART_ENUM(TYPE, ...) struct TYPE { enum Enum { __VA_ARGS__ }; static inline const auto __map = KSmartEnumTools::__va_args_to_map(#__VA_ARGS__); };



#endif // KSMARTENUM_H
