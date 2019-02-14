
#include <environment.h>
#include <iostream>
#include <locale>

int main(int argc, char *argv[]) {
    Auto aaa = 5.6;

    std::cout << "double: " << aaa.toDouble() << "\n";
    std::cout << "int 32: " << aaa.toInt32() << "\n";
    std::cout << "int 64: " << aaa.toInt64() << "\n";
    std::cout << "uint32: " << aaa.toUint32() << "\n";
    std::cout << "uint64: " << aaa.toUint64() << "\n";


    Environment env;
    env.init(argc, argv);
    env.start();
    return 0;
}
