#ifndef REGISTRYINFO_H
#define REGISTRYINFO_H


#include <src/iinformative.h>


class RegistryInfo : public IInformative {
public:
    RegistryInfo();

    // IInformative interface
public:
    std::string info() const override;
};

#endif // REGISTRYINFO_H
