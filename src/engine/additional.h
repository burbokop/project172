#ifndef ADDITIONAL_H
#define ADDITIONAL_H

#include <string>
#include <vector>

namespace e172 {

struct Additional {
#ifdef __WIN32__
    static constexpr char separator = '\\';
    static inline const std::string separatorString = "\\";
#else
    static constexpr char separator = '/';
    static inline const std::string separatorString = "/";
#endif

    static std::string constrainPath(const std::string &path);
    static std::vector<std::string> split(const std::string& s, char delimiter);
    static std::string absolutePath(const std::string &path, const std::string &exe_path);

};

}

#endif // ADDITIONAL_H
