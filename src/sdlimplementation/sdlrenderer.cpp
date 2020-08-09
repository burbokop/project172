#include "sdlrenderer.h"
#include "spm.h"

#include "units/camera.h"
#include "debug.h"

#include <sdlimplementation/effects/anaglyph.h>


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

bool SDLRenderer::updateLensEffect(e172::AbstractRenderer::Lens lens, const e172::Vector &point1, const e172::Vector &point2, double coefficient) {
    auto it = lenses.find(lens);
    if(it != lenses.end()) {
        it->second = std::make_tuple(point1, point2, coefficient);
        return true;
    }
    return false;
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

void SDLRenderer::applyLensEffect(SDL_Surface *surface, const e172::Vector point0, const e172::Vector point1, double coef) {
    auto pixels = reinterpret_cast<uint32_t*>(surface->pixels);

    auto center = (point0 + point1) / 2;

    uint32_t pix[point1.intY()-point0.intY()][point1.intX()-point0.intX()];
    for(int y = point0.intY(); y < point1.intY(); ++y) {
        for(int x = point0.intX(); x < point1.intX(); ++x) {
            uint32_t p = pixels[(y * surface->w) + x];



            auto rx = ( center.x()) ;
            auto ry = ( center.y()) ;

            //int newX = static_cast<int>(abs(x - rx) *1* (std::sin(coef * (x - rx))) + rx);
            //int newY = static_cast<int>(abs(y - ry) *1* (std::sin(coef * (y - ry))) + ry);

            double mx = (M_PI) / (point1.x() - point0.x());
            double my = (M_PI) / (point1.y() - point0.y());


            int newY = (y-center.y()) + coef * std::abs(cos((y-center.y()) * my)) + center.y();
            int newX = (x-center.x()) + coef * std::abs(cos((x-center.x()) * mx)) + center.x();


            //x0=(xlev-x[ra)/2

            //if (((0<=newY-point0.intY())&&(newY-point0.intY()<point1.intY()-point0.intY()))&&((0<=newX-point0.intX())&&(newX-point0.intX()<point1.intX()-point0.intX()))){
            //    pix[newY-point0.intY()][newX-point0.intX()]=p;
            //}

                if (((point0.intY() <= newY)&&(newY < point1.intY()))&&((point0.intX() <= newX)&&(newX < point1.intX()))){
                    pix[newY-point0.intY()][newX-point0.intX()] = p;
                }



        }
    }
    for(int y = point0.intY(); y < point1.intY(); ++y) {
        for(int x = point0.intX(); x < point1.intX(); ++x) {
            uint32_t p = pixels[(y * surface->w) + x];

            if(std::pow(x-center.x(), 2) + std::pow(y-center.y(), 2) < std::pow((point1.x() - point0.x()) / 2, 2.)) {
                SPM::FillPixel(surface, x, y, pix[y-point0.intY()][x-point0.intX()]);
            }


            //SPM::FillPixel(surface, x, y, pix[y-point0.intY()][x-point0.intX()]);
            //pixels[(newY * surface->w) + newX] = p;
        }
    }

    SPM::Rect(surface, point0.x(), point0.y(), point1.x(), point1.y(), 0xff0000);
    SPM::Square(surface, center.x(), center.y(), 3, 0xff0000);
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

        auto image_surface = imageData<SDL_Surface*>(image);
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
    for(auto l : lenses) {
        applyLensEffect(surface, std::get<0>(l.second), std::get<1>(l.second), std::get<2>(l.second));
    }
    SDL_UpdateWindowSurface(window);
}



e172::AbstractRenderer::Lens SDLRenderer::enableLensEffect(const e172::Vector &point1, const e172::Vector &point2, double coefficient) {
    lenses[nextLens] = std::make_tuple(point1, point2, coefficient);
    return nextLens++;
}

bool SDLRenderer::disableLensEffect(Lens lens) {
    const auto it = lenses.find(lens);
    if(it != lenses.end()) {
        lenses.erase(it);
        return true;
    }
    return false;
}
