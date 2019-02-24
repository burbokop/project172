#include <iostream>
#include <locale>


#include "environment.h"
#include "debug.h"


int foo() {

    int *a = reinterpret_cast<int*>(-1);
    int b = *a;
    return b;


}

void bar() { foo(); }
void baz() { bar(); }
void bab() { baz(); }


int main(int argc, char *argv[]) {
    Debug::init(false, true);
    //Debug::init(false, false);

    //bab();

    Environment env;
    env.init(argc, argv);
    env.start();
    return 0;
}
