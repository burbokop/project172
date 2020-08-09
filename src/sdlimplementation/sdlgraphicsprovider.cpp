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
    SDL_Surface *surface = IMG_Load(path.c_str());

    if(surface) {
        return __createImage(new e172::Image::handle<SDL_Surface*>(surface), this, surface->w, surface->h, [](e172::Image::data_ptr d) {
            const auto handle = e172::Image::handle_cast<SDL_Surface*>(d);

            SDL_FreeSurface(handle->c);
            delete handle;
        }, [](e172::Image::data_ptr ptr) -> e172::Image::ptr {
            return e172::Image::handle_cast<SDL_Surface*>(ptr)->c->pixels;
        }, [](e172::Image::data_ptr d, int x, int y, int &w, int &h) -> e172::Image::data_ptr {
            const auto handle = e172::Image::handle_cast<SDL_Surface*>(d);
            const auto newHandle = new e172::Image::handle<SDL_Surface*>(SPM::CutOutSurface(handle->c, x, y, w, h));
            w = newHandle->c->w;
            h = newHandle->c->h;
            return newHandle;
        });
    }
    return e172::Image();
}

e172::Image SDLGraphicsProvider::createImage(void *bitmap, int format) const {
    return e172::Image();
}
