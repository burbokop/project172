#ifndef BOOTSTRAPOBJECT_H
#define BOOTSTRAPOBJECT_H

#include "presentationobject.h"

#include <SDL2/SDL.h>

#include "font.h"
#include "vertexobjects/externaltexvertexobject.h"
#include "vertexobjects/wirevertexobject.h"

namespace e172vp {

class Pipeline;

class BootstrapObject {
    PresentationObject *m_presentationObject = nullptr;

    const uint32_t WIDTH = 800;
    const uint32_t HEIGHT = 600;
    SDL_Window *m_window = nullptr;
    Pipeline *pipeline = nullptr;
    Pipeline *pipeline2 = nullptr;
    Font *font = nullptr;
    bool m_isValid = true;

public:
    BootstrapObject(const std::string &assetFolder);
    ~BootstrapObject();
    PresentationObject *presentationObject() const;

    ExternalTexVertexObject *addExternalTexVertexObject(const std::vector<Vertex> &vertices, const std::vector<uint32_t> &indices);
    ExternalTexVertexObject *addExternalTexVertexObject(const Mesh &mesh);
    WireVertexObject *addWireVertexObject(const std::vector<Vertex> &vertices, const std::vector<uint32_t> &indices);
    void removeVertexObject(AbstractVertexObject *object);


    static std::vector<std::string> sdlExtensions(SDL_Window *window);

    static std::vector<char> readFile(const std::string &filename);

    bool isValid() const;
};

}
#endif // BOOTSTRAPOBJECT_H
