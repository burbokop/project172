#ifndef TESTPROVIDER_H
#define TESTPROVIDER_H

#include <list>
#include <string>
#include<functional>

class TestProvider {
    static std::list<std::pair<std::string, std::function<void()>>> m_tests;
public:
    static void runAllTests();
    static void addTest(const std::string &testName, const std::function<void()> &testFunction);
};

#endif // TESTPROVIDER_H
