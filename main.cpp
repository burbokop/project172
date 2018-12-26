
#include <environment.h>
#include <iostream>
#include <locale>

int main(int argc, char *argv[])
{
    Environment env;
    env.init(argc, argv);
    env.start();
}
