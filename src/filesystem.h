#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <vector>
#include <string>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fstream>

class FileSystem {
public:
    static std::string readFile(std::string path);
    static std::vector<std::string> readDir(std::string path);
    static bool isDir(std::string path);

    static std::string getSufix(std::string string);
    static std::string addPrefix(std::string string, std::string prefix);

    static std::string cutPath(std::string string, unsigned level = 1);
};

#endif // FILESYSTEM_H
