#include "renderer.h"

#include "units/camera.h"
#include "additional/spm.h"

const int Renderer::DEFAULT_FONT_SIZE = 20;


Vector Renderer::getResolution() {
    return resolution;
}

Vector Renderer::getOffset() {
    return offset;
}

#include "debug.h"



void Renderer::setResolution(Vector value) {
    SDL_SetWindowSize(window, value.getIntX(), value.getIntY());
    surface = SDL_GetWindowSurface(window);
    resolution = value;
}

void Renderer::setResolutionCallback(Variant value) {
    setResolution(value.toVector());
}


void Renderer::setCamera(Camera *value) {
    camera = value;
}

Camera *Renderer::getCamera() const
{
    return camera;
}

Renderer::Renderer(SDL_Window *window, Vector resolution, SDL_Surface *surface, TTF_Font *font) {
    this->window = window;
    this->resolution = resolution;
    this->surface = surface;
    this->fonts[DEFAULT_FONT_SIZE] = font;
}

Renderer *Renderer::create(const char *title, int x, int y, std::string fontPath) {
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    SDL_Window *window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, x, y, 0);

    SDL_Surface *surface = SDL_GetWindowSurface(window);
    Renderer *result = new Renderer(window, Vector(x, y), surface, TTF_OpenFont(fontPath.c_str(), DEFAULT_FONT_SIZE));
    result->fontPath = fontPath;
    return result;
}

void Renderer::effect(VisualEffect *effect, bool lock) {
    if(lock) {
        SPM::LockEffect(effect);
    } else {
        SPM::ApplyEffect(effect);
    }
}

void Renderer::fill(Uint32 color) {
    SDL_FillRect(surface, nullptr, color);
}

void Renderer::setFullscreen() {
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

void Renderer::pixel(Vector point, Uint32 color) {
    SPM::FillPixel(surface, point.getIntX(), point.getIntY(), color);
}

void Renderer::line(Vector point1, Vector point2, Uint32 color) {
    SDL_LockSurface(surface);
    SPM::Line(surface, point1.getIntX(), point1.getIntY(), point2.getIntX(), point2.getIntY(), color);
    SDL_UnlockSurface(surface);
}

void Renderer::rect(Vector point1, Vector point2, Uint32 color) {
    SDL_LockSurface(surface);
    SPM::Rect(surface, point1.getIntX(), point1.getIntY(), point2.getIntX(), point2.getIntY(), color);
    SDL_UnlockSurface(surface);
}

void Renderer::square(Vector point, int radius, Uint32 color) {
    SDL_LockSurface(surface);
    SPM::Square(surface, point.getIntX(), point.getIntY(), radius, color);
    SDL_UnlockSurface(surface);
}

void Renderer::circle(Vector point, int radius, Uint32 color) {
    SDL_LockSurface(surface);
    SPM::Circle(surface, point.getIntX(), point.getIntY(), radius, color);
    SDL_UnlockSurface(surface);
}

void Renderer::diagonalGrid(Vector point1, Vector point2, int interval, Uint32 color) {
    //SDL_LockSurface(surface);
    SPM::DiagonalGrid(surface, point1.getIntX(), point1.getIntY(), point2.getIntX(), point2.getIntY(), interval, color);
    //SDL_UnlockSurface(surface);
}

void Renderer::image(SDL_Surface *image, Vector pos, double angle, double zoom) {
    SPM::BlitRotatedSurface(image, surface, pos.getIntX(), pos.getIntY(), angle, zoom, 1);

    /*
    if(pos.getIntX() >= 0 && pos.getIntY() >= 0 && pos.getIntX() <= resolution.getIntX() && pos.getIntY() <= resolution.getIntY()) {
        SDL_BlitSurface(image, nullptr, surface, new SDL_Rect { pos.getIntX(), pos.getIntY(), 0, 0 });
        std::cout << "pos: " << pos << "\n";
    }
    */
}

void Renderer::string(std::string string, Vector pos, Uint32 color) {
    if(fonts[DEFAULT_FONT_SIZE]) {
        SPM::BlendedText(surface, string, fonts[DEFAULT_FONT_SIZE], pos.getIntX(), pos.getIntY(), color);
    }
}

void Renderer::string(std::string string, Vector pos, Uint32 color, int size) {
    if(!fonts[size]) {
        fonts[size] = TTF_OpenFont(fontPath.c_str(), size);
    }

    if(fonts[size]) {
        SPM::BlendedText(surface, string, fonts[size], pos.getIntX(), pos.getIntY(), color);
    }
}

void Renderer::stringCentered(std::string string, Vector pos, Uint32 color, int size) {
    if(!fonts[size]) {
        fonts[size] = TTF_OpenFont(fontPath.c_str(), size);
    }

    if(fonts[size]) {
        int w = 0, h = 0;
        TTF_SizeText(fonts[size], string.c_str(), &w, &h);

        SPM::BlendedText(surface, string, fonts[size], pos.getIntX() - w / 2, pos.getIntY() - h / 2, color);
    }
}

Vector Renderer::getStringSize(std::string string, int size) {
    if(!fonts[size]) {
        fonts[size] = TTF_OpenFont(fontPath.c_str(), size);
    }

    if(fonts[size]) {
        int w = 0, h = 0;
        TTF_SizeText(fonts[size], string.c_str(), &w, &h);
        return Vector(w, h);
    }
    return Vector();
}


void Renderer::update() {
    Unit *cameraUnit = dynamic_cast<Unit*>(camera);
    if(cameraUnit) {
        offset = getResolution() / 2 - cameraUnit->getPosition();
    }
    SDL_UpdateWindowSurface(window);
}

void Renderer::quit()
{
    SDL_FreeSurface(surface);
    TTF_Quit();
    SDL_Quit();
}
