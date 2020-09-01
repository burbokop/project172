#include "smartenum.h"



std::string e172::__enum_tools::trim(const std::string &str) {
    size_t first = str.find_first_not_of(' ');
    if (std::string::npos == first) {
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

std::vector<std::string> e172::__enum_tools::split(const std::string &s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

std::map<uint8_t, std::string> e172::__enum_tools::__va_args_to_map(const std::string &str) {
    auto vec = split(str, ',');
    std::map<uint8_t, std::string> result;
    for(size_t i = 0, count = vec.size(); i < count; ++i) {
        result[i] = trim(vec[i]);
    }
    return result;
}
