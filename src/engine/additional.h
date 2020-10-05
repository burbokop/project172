#ifndef ADDITIONAL_H
#define ADDITIONAL_H

#include <string>
#include <vector>
#include <map>
#include <list>

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
    static std::pair<std::string, std::string> splitIntoPair(const std::string& s, char delimiter);
    static std::string trim(const std::string& str, char symbol = ' ');
    static std::string trim(const std::string& str, const std::vector<char> &symbols);
    static std::string removeSymbols(const std::string &string, const std::vector<char> &symbols);
    static std::string absolutePath(const std::string &path, const std::string &exe_path);

    enum Fence {
        Brackets,
        Parentheses,
        CurlyBraces
    };
    static std::string fencedArea(const std::string &string, Fence fence);
    static std::string fencedArea(const std::string &string, size_t beginIndex = 0, size_t *nextIndexPtr = nullptr);
    static std::string jsonTopLevelField(const std::string &string, size_t beginIndex = 0, size_t *nextIndexPtr = nullptr);
    static std::vector<std::string> jsonTopLevelFields(const std::string &string);
    static std::vector<std::string> fencedAreas(const std::string &string);
    static char reversedFence(char symbol);
    template<typename T>
    static typename T::mapped_type value(const T& map, const typename T::key_type& key, const typename T::mapped_type& defaultValue = typename T::mapped_type()) {
        const auto it = map.find(key);
        if(it == map.end()) {
            return defaultValue;
        } else {
            return it->second;
        }
    }

    static std::string readFile(std::string path);
    static std::vector<std::string> directoryContent(std::string path);
    static bool isDirectory(std::string path);
    static std::string fileSufix(std::string string);
    static std::string concatenatePaths(std::string prefix, std::string string);
    static std::string cutPath(std::string string, unsigned level);

    static size_t countOfFiles(std::string path, std::string suffix);

    static std::map<std::string, std::string> readAllVof(const std::string &path, char delimiter = '=');
    static std::string readVof(const std::string &path, const std::string &id, char delimiter = '=');
    static void writeVof(const std::string &path, const std::string &id, const std::string &value, char delimiter = '=');
};

}

#endif // ADDITIONAL_H
