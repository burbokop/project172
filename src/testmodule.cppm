
export module test_module;

import <iostream>;         // import declaration

export void hello() {      // export declaration
    std::cout << "Hello world!\n";
}

class TestModule {
public:
    TestModule();
};
