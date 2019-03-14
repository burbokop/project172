#include <iostream>
#include <locale>

#include "environment.h"


std::vector<std::string> coverArgs(int argc, char *argv[]) {
    std::vector<std::string> result;
    for(int i = 0; i < argc; i++) {
        result.push_back(argv[i]);
    }
    return result;
}


int main(int argc, char *argv[]) {
    std::vector<std::string> args = coverArgs(argc, argv);
    Environment env(args);
    env.start();
    return 0;
}
