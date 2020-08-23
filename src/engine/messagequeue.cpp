#include "messagequeue.h"

#include <iostream>



void e172::MessageBusPrivate::throwExeption(const std::string &exeption) {
    throw std::runtime_error(exeption.c_str());
}

void e172::MessageBusPrivate::warningExeption(const std::string &exeption) {
    std::cout << exeption << "\n";
}
