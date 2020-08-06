#include "type.h"

#include <cxxabi.h>
#include <stdexcept>

using namespace e172;

std::string TypePrivate::demangle(const std::string &typeName) {
    size_t originalTypeNameSize = typeName.size();
    int status = 0;
    char *demangleResult = abi::__cxa_demangle(typeName.c_str(), nullptr, &originalTypeNameSize, &status);
    std::string result;
    if(status == 0) {
        result = demangleResult;
    } else if(status == -1) {
        throw std::runtime_error("KType: Memory allocation failiure occurred.");
    } else if(status == -2) {
        throw std::runtime_error("KType: Mangled_name is not a valid name under the C++ ABI mangling rules.");
    } else if(status == -3) {
        throw std::runtime_error("KType: One of the arguments is invalid.");
    }
    std::free(demangleResult);
    return result;
}
