#pragma once

#include <e172/testing.h>

#define shouldContainWare(container, ware, wareCount) \
    { \
        bool found = false; \
        for (size_t i = 0, count = container.wareInfoCount(); i < count; ++i) { \
            const auto wareInfo = container.wareInfo(i); \
            if (wareInfo.isValid() && wareInfo.wareName() == ware \
                && wareInfo.count() == wareCount) { \
                found = true; \
                break; \
            } \
        } \
        if (!found) { \
            e172::Debug::fatal("container not contains", \
                               ware, \
                               "with count", \
                               wareCount, \
                               e172::Debug::codeLocation(__FILE__, __LINE__), \
                               e172_pretty_function); \
        } \
    }

class WareContainerSpec {
    static void test0() e172_test(WareContainerSpec, test0);
};

