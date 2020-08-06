#include "sdlrenderer.h"
#include "spm.h"

#include "units/camera.h"
#include "debug.h"

#include <additional/effects/anaglyph.h>

const int SDLRenderer::DEFAULT_FONT_SIZE = 20;


e172::Vector SDLRenderer::resolution() const {
    return m_resolution;
}

e172::Vector SDLRenderer::offset() const {
    return m_offset;
}

void SDLRenderer::enableEffect(uint64_t effect) {
    (void)effect;
    if(effect == 0) {
        anaglyphEnabled = true;
    } else {
        anaglyphEnabled2 = true;
    }
}

void SDLRenderer::disableEffect(uint64_t effect) {
    (void)effect;
    if(effect == 0) {
        anaglyphEnabled = false;
    } else {
        anaglyphEnabled2 = false;
    }
}

SDLRenderer::~SDLRenderer() {
    SDL_FreeSurface(surface);
    TTF_Quit();
    SDL_Quit();
}

void SDLRenderer::setResolution(e172::Vector value) {
    SDL_SetWindowSize(window, value.intX(), value.intY());
    surface = SDL_GetWindowSurface(window);
    m_resolution = value;
}

void SDLRenderer::setResolutionCallback(Variant value) {
    setResolution(value.toVector());
}


void SDLRenderer::setCamera(Camera *value) {
    camera = value;
}

Camera *SDLRenderer::getCamera() const {
    return camera;
}

SDLRenderer::SDLRenderer(const char *title, int x, int y, std::string fontPath) {
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    SDL_Window *window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, x, y, 0);
    SDL_Surface *surface = SDL_GetWindowSurface(window);

    this->fontPath = fontPath;
    this->window = window;
    this->m_resolution = e172::Vector(x, y);
    this->surface = surface;
    this->fonts[DEFAULT_FONT_SIZE] = TTF_OpenFont(fontPath.c_str(), DEFAULT_FONT_SIZE);
}

void SDLRenderer::fill(uint32_t color) {
    SDL_FillRect(surface, nullptr, color);
}

void SDLRenderer::setFullscreen() {
    fullscreen = !fullscreen;
    if(fullscreen) {
        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
        SDL_ShowCursor(false);
    } else {
        SDL_SetWindowFullscreen(window, 0);
        SDL_ShowCursor(true);
    }
    surface = SDL_GetWindowSurface(window);
}

void SDLRenderer::drawPixel(const e172::Vector &point, Uint32 color) {
    SPM::FillPixel(surface, point.intX(), point.intY(), color);
}

void SDLRenderer::drawLine(const e172::Vector &point1, const e172::Vector &point2, Uint32 color) {
    SDL_LockSurface(surface);
    SPM::Line(surface, point1.intX(), point1.intY(), point2.intX(), point2.intY(), color);
    SDL_UnlockSurface(surface);
}

void SDLRenderer::drawRect(const e172::Vector &point1, const e172::Vector &point2, Uint32 color) {
    SDL_LockSurface(surface);
    SPM::Rect(surface, point1.intX(), point1.intY(), point2.intX(), point2.intY(), color);
    SDL_UnlockSurface(surface);
}

void SDLRenderer::drawSquare(const e172::Vector &point, int radius, Uint32 color) {
    SDL_LockSurface(surface);
    SPM::Square(surface, point.intX(), point.intY(), radius, color);
    SDL_UnlockSurface(surface);
}

void SDLRenderer::drawCircle(const e172::Vector &point, int radius, Uint32 color) {
    SDL_LockSurface(surface);
    SPM::Circle(surface, point.intX(), point.intY(), radius, color);
    SDL_UnlockSurface(surface);
}

void SDLRenderer::drawDiagonalGrid(const e172::Vector &point1, const e172::Vector &point2, int interval, Uint32 color) {
    //SDL_LockSurface(surface);
    SPM::DiagonalGrid(surface, point1.intX(), point1.intY(), point2.intX(), point2.intY(), interval, color);
    //SDL_UnlockSurface(surface);
}

void SDLRenderer::drawImage(const e172::Image &image, const e172::Vector &pos, double angle, double zoom) {
    if(imageId(image) == provider()) {
        VisualEffect *effect = nullptr;
        if(anaglyphEnabled || anaglyphEnabled2)
             effect = new Anaglyph(e172::Vector(2, 1));

        auto image_surface = const_cast<SDL_Surface*>(reinterpret_cast<const SDL_Surface*>(imageData(image)));
        SPM::BlitRotatedSurface(image_surface, surface, pos.intX(), pos.intY(), angle, zoom, 1, effect);
        delete effect;
    }
}

e172::Vector SDLRenderer::drawString(const std::string &string, const e172::Vector &pos, uint32_t color, const e172::TextFormat &format) {
    int size = DEFAULT_FONT_SIZE;
    if(format.fontSize() > 0) {
        size = format.fontSize();
    }

    if(!fonts[size]) {
        fonts[size] = TTF_OpenFont(fontPath.c_str(), size);
    }

    if(fonts[size]) {
        VisualEffect *effect = nullptr;
        if(anaglyphEnabled || anaglyphEnabled2)
             effect = new Anaglyph(e172::Vector(2, 1));

        int w = 0, h = 0;
        TTF_SizeText(fonts[size], string.c_str(), &w, &h);
        int offsetX = 0, offsetY = 0;
        if(format.alignment() & e172::TextFormat::AlignHCenter) {
            offsetX = -w / 2;
        }
        if(format.alignment() & e172::TextFormat::AlignVCenter) {
            offsetY = -h / 2;
        }
        SPM::BlendedText(surface, string, fonts[size], pos.intX() + offsetX, pos.intY() + offsetY, color, 1024, effect);
        delete effect;
        return e172::Vector(w, h);
    }
    return e172::Vector();
}

void SDLRenderer::update() {
    Unit *cameraUnit = dynamic_cast<Unit*>(camera);
    if(cameraUnit) {
        m_offset = m_resolution / 2 - cameraUnit->getPosition();
    }
    SDL_UpdateWindowSurface(window);
}

