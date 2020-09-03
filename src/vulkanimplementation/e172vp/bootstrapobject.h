#ifndef BOOTSTRAPOBJECT_H
#define BOOTSTRAPOBJECT_H

#include "presentationobject.h"

#include <SDL2/SDL.h>

#include "font.h"


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


    static std::vector<std::string> sdlExtensions(SDL_Window *window);

    static std::vector<char> readFile(const std::string &filename);

    bool isValid() const;
};

}
#endif // BOOTSTRAPOBJECT_H
