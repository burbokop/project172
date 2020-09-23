#ifndef WARETEST_H
#define WARETEST_H

#include <src/additional/ware/warecontainer.h>

#include <src/engine/testprovider.h>

class TestWareContainer : public WareContainer {
public:
    TestWareContainer(size_t capacity);
};

class WareTest {
    static void printContainer(const TestWareContainer &container, const std::string &coment);
    static void test();
    static inline const int static_call = [] {
        TestProvider::addTest("WareTest", &WareTest::test);
        return 0;
    }();;
};

#endif // WARETEST_H
