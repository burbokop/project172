#include "additional.h"

#include <list>
#include <sstream>

#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fstream>



std::string e172::Additional::constrainPath(const std::string &path) {
    if(path.size() <= 0)
        return "";

    auto results = split(path, separator);

    std::list<std::string> stack;
    for(auto&& r : results) {
        if(r == "..") {
            stack.pop_back();
        } else if(r == ".") {

        } else if(r == "") {

        } else {
            stack.push_back(r);
        }
    }

    std::string result = (path[0] == separator) ? separatorString : "";
    int i = 0;
    for(auto&& s : stack) {
        result += ((i == 0) ? "" : separatorString) + s;
        i++;
    }
    return result;
}

std::vector<std::string> e172::Additional::split(const std::string &s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}

std::string e172::Additional::absolutePath(const std::string &path, const std::string &exe_path) {
    if(exe_path.size() <= 0) return "";
    if(path.size() <= 0) return "";

#ifdef __WIN32__
    if(path.size() > 2 && path[1] == ':' && path[2] == separator) return path;
#else
    if(path[0] == separator) return path;
#endif

    return constrainPath(exe_path + separatorString + ".." + separatorString + path);
}



std::string e172::Additional::readFile(std::string path) {
    std::ifstream ifile(path);
    std::string string((std::istreambuf_iterator<char>(ifile)), std::istreambuf_iterator<char>());
    ifile.close();
    return string;
}


std::vector<std::string> e172::Additional::directoryContent(std::string path) {
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir (path.c_str())) != nullptr) {
        std::vector<std::string> result;
        while ((ent = readdir (dir)) != nullptr) {
            if(strcmp(ent->d_name, "..") && strcmp(ent->d_name, ".")) {
                result.push_back(ent->d_name);
            }
        }
        closedir (dir);
        return result;
    } else {
        return std::vector<std::string>();
    }
}


bool e172::Additional::isDirectory(std::string path) {
    struct stat st;
    if(stat(path.c_str(), &st) == 0 && S_ISDIR(st.st_mode)) {
        return true;
    } else {
        return false;
    }
}

std::string e172::Additional::fileSufix(std::string string) {
    return string.substr(string.find_last_of('.'), string.length() - 1);
}

std::string e172::Additional::concatenatePaths(std::string prefix, std::string string) {
    if(string[0] == '.') string.erase(0, 1);
    if(string[0] != '/') string = '/' + string;
    if(prefix[prefix.length() - 1] == '/') prefix.pop_back();

    return prefix + string;
}

std::string e172::Additional::cutPath(std::string string, unsigned level) {
    size_t pos = string.find_last_of('/');
    std::string result = string.substr(0, pos);
    if(level > 1) {
        return cutPath(result, level - 1);
    }
    return result;
}

size_t e172::Additional::countOfFiles(std::string path, std::string suffix) {
    if(path[path.length() - 1] == '/') path.pop_back();
    std::vector<std::string> items = e172::Additional::directoryContent(path);
    size_t sum_count = 0;
    for(unsigned long long i = 0, L = items.size(); i < L; i++) {
        std::string item = items[i];
        std::string file = path + '/' + item;
        if(e172::Additional::isDirectory(file)) {
            sum_count += countOfFiles(file, suffix);
        } else {
            if(e172::Additional::fileSufix(file) == suffix) {
                ++sum_count;
            }
        }
    }
    return sum_count;
}
