#include "testprovider.h"

#include <iostream>


std::list<std::pair<std::string, std::function<void()>>> TestProvider::m_tests;


void TestProvider::runAllTests() {
    std::cout << __PRETTY_FUNCTION__ << "\n\n";
    for(auto t : m_tests) {
        std::cout << "TEST: " << t.first << "\n\n";
        if(t.second) {
            t.second();
        } else {
            std::cout << "TEST FUNCTION NOT PROVIDED" << "\n";
        }
        std::cout << "\n";
    }
}

void TestProvider::addTest(const std::string &testName, const std::function<void ()> &testFunction) {
    m_tests.push_back({ testName, testFunction });
}
