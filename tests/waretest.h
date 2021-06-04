#ifndef WARETEST_H
#define WARETEST_H

#include <src/additional/ware/warecontainer.h>

#include <src/testing.h>

class TestWareContainer : public WareContainer {
public:
    TestWareContainer(size_t capacity);

};

class WareTest {
    static void printContainer(const TestWareContainer &container, const std::string &coment);
    static void test0(); e172_test(test0)
};

#endif // WARETEST_H
