#include "warecontainerspec.h"

void WareContainerSpec::test0() {
    WareContainer container0(4);
    container0.addWare("ware0", 2, true);
    container0.addWare("ware1", 2, true);

    container0.setAllowedInput(WareContainer::AllAllowed);
    container0.setAllowedOutput(WareContainer::AllAllowed);

    WareContainer container1(10);
    container1.addWare("ware0", 4, true);
    container1.addWare("ware1", 4, true);

    container1.setAllowedInput(WareContainer::AllAllowed);
    container1.setAllowedOutput(WareContainer::AllAllowed);

    e172_shouldEqual(container0.wareInfoCount(), 2);
    shouldContainWare(container0, "ware0", 2);
    shouldContainWare(container0, "ware1", 2);

    e172_shouldEqual(container1.wareInfoCount(), 2);
    shouldContainWare(container1, "ware0", 4);
    shouldContainWare(container1, "ware1", 4);

    const auto index0 = container0.indexOf("ware0");
    e172_shouldEqual(index0.isDefined(), true);
    e172_shouldEqual(container0.transferWareTo(index0.value(), &container1, 2), 2);

    e172_shouldEqual(container0.wareInfoCount(), 1);
    shouldContainWare(container0, "ware1", 2);

    e172_shouldEqual(container1.wareInfoCount(), 2);
    shouldContainWare(container1, "ware0", 6);
    shouldContainWare(container1, "ware1", 4);
}
