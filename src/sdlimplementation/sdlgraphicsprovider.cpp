#include "sdlgraphicsprovider.h"
#include "spm.h"

#include "SDL2/SDL_image.h"

SDLGraphicsProvider::SDLGraphicsProvider(const char *title, int x, int y, std::string fontPath) {
    m_title = title;
    m_x = x;
    m_y = y;
    m_fontPath = fontPath;

    m_renderer = new SDLRenderer(title, x, y, fontPath);
    installParentToRenderer(m_renderer);
}

SDLGraphicsProvider::~SDLGraphicsProvider() {
    delete m_renderer;
}

e172::AbstractRenderer *SDLGraphicsProvider::renderer() const {
    return m_renderer;
}

e172::Image SDLGraphicsProvider::loadImage(const std::string &path) const {
    const SDL_Surface *surface = IMG_Load(path.c_str());
    const void* s_ptr = reinterpret_cast<const void*>(surface);
    if(surface) {
        return __createImage(s_ptr, this , surface->w, surface->h, [](const void* d) {
            delete reinterpret_cast<const SDL_Surface*>(d);
        }, [](e172::Image::ptr ptr) -> e172::Image::ptr {
            return reinterpret_cast<const SDL_Surface*>(ptr)->pixels;
        }, [](const void* d, int x, int y, int &w, int &h) -> const void* {
            auto surface = reinterpret_cast<const SDL_Surface*>(d);
            surface = SPM::CutOutSurface(surface, x, y, w, h);
            w = surface->w;
            h = surface->h;
            return surface;
        });
    }
    return e172::Image();
}

e172::Image SDLGraphicsProvider::createImage(void *bitmap, int format) const {
    return e172::Image();
}
