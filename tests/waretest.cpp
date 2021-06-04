#include "waretest.h"

#include <iostream>


TestWareContainer::TestWareContainer(size_t capacity) : WareContainer(capacity) {
    addWare("ware0", capacity / 4);
    addWare("ware1", capacity / 4);
}

void WareTest::printContainer(const TestWareContainer &container, const std::string &coment) {
    std::cout << "container: " << coment << "\n";
    for(size_t i = 0, count = container.wareInfoCount(); i < count; ++i) {
        const auto wareInfo = container.wareInfo(i);
        std::cout << "\t" << wareInfo.wareName() << " [" << wareInfo.count() << "]\n";
    }
}

void WareTest::test0() {
    TestWareContainer container0(4);
    TestWareContainer container1(8);

    printContainer(container0, "0");
    printContainer(container1, "1");

    container0.transferWareTo(0, &container1, 2);

    printContainer(container0, "0");
    printContainer(container1, "1");


}
