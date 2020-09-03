#ifndef MESH_H
#define MESH_H

#include <vector>
#include <glm/glm.hpp>
#include <string>

namespace e172vp {


struct Mesh {
    std::vector <glm::vec3> vertices;
    std::vector <glm::vec2> uvMap;
    std::vector <glm::vec3> normals;

    std::vector <uint32_t> vertexIndices;
    std::vector <uint32_t> uvIndices;
    std::vector <uint32_t> normalIndices;

    bool useTexture = false;

    Mesh();
    static Mesh load(const char *path);
    static Mesh load(const std::string &path);
    static Mesh plate(float radius);
    static Mesh plate(const glm::vec2 point0, const glm::vec2 point1);
};

}

#endif // MESH_H
