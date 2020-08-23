#ifndef TYPEDEFS_H
#define TYPEDEFS_H

#include <inttypes.h>
#include <vector>
#include <map>
#include <list>

namespace e172 {

typedef uint8_t Byte;
typedef std::vector<Byte> ByteArray;
typedef std::string String;

class Variant;
typedef std::vector<Variant> VariantVector;
typedef std::list<Variant> VariantList;
typedef std::map<std::string, Variant> VariantMap;

}

#endif // TYPEDEFS_H
