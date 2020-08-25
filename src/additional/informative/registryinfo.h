#ifndef REGISTRYINFO_H
#define REGISTRYINFO_H


#include <src/iinformative.h>


class RegistryInfo : public IInformative {
public:
    RegistryInfo();

    // IInformative interface
public:
    std::string getInfo();
};

#endif // REGISTRYINFO_H
