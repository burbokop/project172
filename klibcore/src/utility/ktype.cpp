#include "ktype.h"

#include <cxxabi.h>


#ifdef QT_CORE_LIB
    #include <QCryptographicHash>
    #include <QDataStream>
#endif

uint64_t KTypeAdditional::hash64(const std::string &string) {
#ifdef QT_CORE_LIB
    QByteArray hash = QCryptographicHash::hash(QByteArray::fromRawData(string.c_str(), string.length()), QCryptographicHash::Md5);
    Q_ASSERT(hash.size() == 16);
    QDataStream stream(&hash, QIODevice::ReadOnly);
    quint64 a, b;
    stream >> a >> b;
    return a ^ b;
#else
    (void)string;
    return 0;
#endif
}



std::string KTypeAdditional::demangle(const std::string &typeName) {
    size_t originalTypeNameSize = typeName.size();
    int status = 0;
    char *demangleResult = abi::__cxa_demangle(typeName.c_str(), nullptr, &originalTypeNameSize, &status);
    std::string result;
    if(status == 0) {
        result = demangleResult;
    } else if(status == -1) {
        printf("KType: Memory allocation failiure occurred.");
    } else if(status == -2) {
        printf("KType: Mangled_name is not a valid name under the C++ ABI mangling rules.");
    } else if(status == -3) {
        printf("KType: One of the arguments is invalid.");
    }
    std::free(demangleResult);
    return result;
}

