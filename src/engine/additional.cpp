#include "additional.h"

#include <list>
#include <sstream>

#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fstream>
#include <algorithm>



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
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

std::pair<std::string, std::string> e172::Additional::splitIntoPair(const std::string &s, char delimiter) {
    const auto index = s.find_first_of(delimiter);
    if(index >= 0 && index < s.size())
        return { s.substr(0, index), s.substr(index + 1, s.size() - index) };

    return {};
}

std::string e172::Additional::trim(const std::string &str, char symbol) {
    size_t first = str.find_first_not_of(symbol);
    if (std::string::npos == first) {
        return str;
    }
    size_t last = str.find_last_not_of(symbol);
    return str.substr(first, (last - first + 1));
}

std::string e172::Additional::trim(const std::string &str, const std::vector<char> &symbols) {
    std::string result = str;
    for(auto s : symbols) {
        result = trim(result, s);
    }
    return result;
}

std::string e172::Additional::removeSymbols(const std::string &string, const std::vector<char> &symbols) {
    std::string result;
    result.reserve(string.size());
    for(auto c : string) {
        if(std::find(symbols.begin(), symbols.end(), c) == symbols.end()) {
            result.push_back(c);
        }
    }
    return result;
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

std::string e172::Additional::fencedArea(const std::string &string, e172::Additional::Fence fence) {
    char beginFence;
    char endFence;
    if(fence == Brackets) {
        beginFence = '[';
        endFence = ']';
    } else if(fence == Parentheses) {
        beginFence = '(';
        endFence = ')';
    } else if(fence == CurlyBraces) {
        beginFence = '{';
        endFence = '}';
    } else {
        return string;
    }

    size_t fenceCount = 0;
    size_t begin = 0;
    bool beginFound = false;
    for(size_t i = 0; i < string.size(); ++i) {
        if(string[i] == beginFence) {
            fenceCount++;
            if(!beginFound) {
                begin = i;
                beginFound = true;
            }
        } else if(string[i] == endFence) {
            fenceCount--;
            if(fenceCount == 0 && beginFound) {
                return string.substr(begin, i - begin + 1);
            }
        }
    }
    return string;
}

std::string e172::Additional::fencedArea(const std::string &string, size_t beginIndex, size_t *nextIndexPtr) {
    if(beginIndex >= string.size())
        return std::string();

    char endFence;
    char beginFance;

    size_t fenceCount = 0;
    size_t begin = 0;
    bool beginFound = false;
    for(size_t i = beginIndex; i < string.size(); ++i) {
        if(beginFound) {
            if(string[i] == beginFance) {
                ++fenceCount;
            } else if(string[i] == endFence) {
                if(--fenceCount == 0) {
                    if(nextIndexPtr)
                        *nextIndexPtr = i + 1;
                    return string.substr(begin, i - begin + 1);
                }
            }
        } else if(string[i] == '{' || string[i] == '[' || string[i] == '(') {
            begin = i;
            beginFound = true;
            beginFance = string[i];
            endFence = reversedFence(beginFance);
            ++fenceCount;
        }
    }
    return std::string();
}

std::string e172::Additional::jsonTopLevelField(const std::string &string, size_t beginIndex, size_t *nextIndexPtr) {
    if(beginIndex >= string.size())
        return std::string();

    char endFence;
    char beginFance;

    size_t fenceCount = 0;
    size_t begin = 0;
    bool beginFound = false;
    for(size_t i = beginIndex; i < string.size(); ++i) {
        if(beginFound) {
            if(string[i] == beginFance) {
                ++fenceCount;
            } else if(string[i] == endFence) {
                if(--fenceCount == 0) {
                    beginFound = false;
                    //if(endIndexPtr)
                    //    *endIndexPtr = i + 1;
                    //return string.substr(begin, i - begin + 1);
                }
            }
        } else {
            if(string[i] == ',') {
                if(nextIndexPtr)
                    *nextIndexPtr = i + 1;
                return string.substr(beginIndex, i - beginIndex);
            } else if(string[i] == '{' || string[i] == '[' || string[i] == '(') {
                begin = i;
                beginFound = true;
                beginFance = string[i];
                endFence = reversedFence(beginFance);
                ++fenceCount;
            }
        }
    }
    if(nextIndexPtr)
        *nextIndexPtr = string.size();
    return string.substr(beginIndex, string.size() - beginIndex);
}

std::vector<std::string> e172::Additional::fencedAreas(const std::string &string) {
    size_t begin = 0;
    std::vector<std::string> result;
    while (true) {
         const auto r = fencedArea(string, begin, &begin);
         if(r.size() > 0) {
             result.push_back(r);
         } else {
             return result;
         }
    }
}

std::vector<std::string> e172::Additional::jsonTopLevelFields(const std::string &string) {
    size_t begin = 0;
    std::vector<std::string> result;
    while (true) {
         const auto r = jsonTopLevelField(string, begin, &begin);
         if(r.size() > 0) {
             result.push_back(r);
         } else {
             return result;
         }
    }
}

char e172::Additional::reversedFence(char symbol) {
    switch (symbol) {
    case '{': return '}';
    case '[': return ']';
    case '(': return ')';
    case '<': return '>';
    case '}': return '{';
    case ']': return '[';
    case ')': return '(';
    case '>': return '<';
    default: return symbol;
    }
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
