#ifndef ASSETPROVIDER_H
#define ASSETPROVIDER_H

#include <string>

#include <engine/variant.h>

namespace e172 {


class AssetProvider {
public:
    AssetProvider();
    void load(const std::string &folder);

    Variant asset(const std::string &id) {}
};


void aaa() {
    AssetProvider ap;

    ap.asset("goga").value<std::string>();

}

};

#endif // ASSETPROVIDER_H
