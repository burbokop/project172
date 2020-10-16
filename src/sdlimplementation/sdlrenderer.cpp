#include "sdlrenderer.h"
#include "spm.h"


#include <src/sdlimplementation/effects/anaglyph.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <src/math/math.h>

const int SDLRenderer::DefaultFontSize = 20;


e172::Vector SDLRenderer::resolution() const {
    return m_resolution;
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
    SDL_DestroyWindow(window);
}

void SDLRenderer::setResolution(e172::Vector value) {
    SDL_SetWindowSize(window, value.intX(), value.intY());
    surface = SDL_GetWindowSurface(window);
    m_resolution = value;
}

void SDLRenderer::applyLensEffect(const e172::Vector &point0, const e172::Vector &point1, double coefficient) {
    const auto delta = point1 - point0;
    if(e172::Math::cmpf(delta.x(), 0) || e172::Math::cmpf(delta.y(), 0) || e172::Math::cmpf(coefficient, 0))
        return;

    m_lensQueue.push({ point0, point1, coefficient });
}

SDLRenderer::SDLRenderer(const char *title, int x, int y) {
    if(!sdl_initialized) {
        SDL_Init(SDL_INIT_EVERYTHING);
        TTF_Init();
        sdl_initialized = true;
    }
    SDL_Window *window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, x, y, 0);
    SDL_Surface *surface = SDL_GetWindowSurface(window);

    this->window = window;
    this->m_resolution = e172::Vector(x, y);
    this->surface = surface;

}

void SDLRenderer::__applyLensEffect(SDL_Surface *surface, const e172::Vector point0, const e172::Vector point1, double coef) {
    auto pixels = reinterpret_cast<uint32_t*>(surface->pixels);

    auto center = (point0 + point1) / 2;

    uint32_t pix[point1.intY()-point0.intY()][point1.intX()-point0.intX()];
    for(int y = point0.intY(); y < point1.intY(); ++y) {
        for(int x = point0.intX(); x < point1.intX(); ++x) {
            uint32_t p = pixels[(y * surface->w) + x];



            //auto rx = ( center.x()) ;
            //auto ry = ( center.y()) ;

            //int newX = static_cast<int>(abs(x - rx) *1* (std::sin(coef * (x - rx))) + rx);
            //int newY = static_cast<int>(abs(y - ry) *1* (std::sin(coef * (y - ry))) + ry);

            double mx = (M_PI) / (point1.x() - point0.x());
            double my = (M_PI) / (point1.y() - point0.y());




            int newY = static_cast<int>((y-center.y()) + coef * sin((y-center.y()) * my) + center.y());
            int newX = static_cast<int>((x-center.x()) + coef * sin((x-center.x()) * mx) + center.x());

            //int newY = (y-center.y()) + coef * (cos((y-center.y()) * my*2) + 1) + center.y();
            //int newX = (x-center.x()) + coef * (cos((x-center.x()) * mx*2) + 1) + center.x();

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

            //if(std::pow(x-center.x(), 2) + std::pow(y-center.y(), 2) < std::pow((point1.x() - point0.x()) / 2, 2.)) {
                SPM::FillPixel(surface, x, y, pix[y-point0.intY()][x-point0.intX()]);
            //}


            //SPM::FillPixel(surface, x, y, pix[y-point0.intY()][x-point0.intX()]);
            //pixels[(newY * surface->w) + newX] = p;
        }
    }

    //SPM::Rect(surface, point0.x(), point0.y(), point1.x(), point1.y(), 0xff0000);
    //SPM::Square(surface, center.x(), center.y(), 3, 0xff0000);
}

size_t SDLRenderer::presentEffectCount() const {
    return 0;
}

std::string SDLRenderer::presentEffectName(size_t index) const {
    return "";
}

void SDLRenderer::drawEffect(size_t index, const e172::VariantVector &args) {

}

void SDLRenderer::fill(uint32_t color) {
    SDL_FillRect(surface, nullptr, color);
}


e172::Vector SDLRenderer::screenSize() const {
    SDL_DisplayMode displayMode;
    SDL_GetCurrentDisplayMode(0, &displayMode);
    return e172::Vector(displayMode.w, displayMode.h);
}

void SDLRenderer::setFullscreen(bool value) {
    if(m_lastFullscreen == value)
        return;

    m_lastFullscreen = value;

    if(value) {
        SDL_DisplayMode displayMode;
        SDL_GetCurrentDisplayMode(0, &displayMode);
        setResolution(e172::Vector(displayMode.w, displayMode.h));

        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
        SDL_ShowCursor(false);
    } else {
        SDL_SetWindowFullscreen(window, 0);
        SDL_ShowCursor(true);
    }
    if(surface)
        SDL_FreeSurface(surface);

    surface = SDL_GetWindowSurface(window);
}

void SDLRenderer::drawPixel(const e172::Vector &point, Uint32 color) {
    SPM::FillPixel(surface, point.intX(), point.intY(), color);
}

void SDLRenderer::drawLine(const e172::Vector &point0, const e172::Vector &point1, Uint32 color) {
    SDL_LockSurface(surface);
    int x0 = point0.intX();
    int y0 = point0.intY();
    int x1 = point1.intX();
    int y1 = point1.intY();
    if(x0 == x1) {
        if(y0 < 0) {
            y0 = 0;
        } else if(y0 > m_resolution.intY()) {
            y0 = m_resolution.intY();
        }
        if(y1 < 0) {
            y1 = 0;
        } else if(y1 > m_resolution.intY()) {
            y1 = m_resolution.intY();
        }
    } else {
        double k = static_cast<double>(y1 - y0) / static_cast<double>(x1 - x0);
        double b = y0 - k * x0;

        if(x0 < 0) {
            x0 = 0;
            y0 = k * x0 + b;
        } else if(x0 > m_resolution.intX()) {
            x0 = m_resolution.intX();
            y0 = k * x0 + b;
        }
        if(x1 < 0) {
            x1 = 0;
            y1 = k * x1 + b;
        } else if(x1 > m_resolution.intX()) {
            x1 = m_resolution.intX();
            y1 = k * x1 + b;
        }
    }
    SPM::Line(surface, x0, y0, x1, y1, color);
    SDL_UnlockSurface(surface);
}

void SDLRenderer::drawRect(const e172::Vector &point0, const e172::Vector &point1, Uint32 color) {
    SDL_LockSurface(surface);
    SPM::Rect(surface, point0.intX(), point0.intY(), point1.intX(), point1.intY(), color);
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
    int expectedSize = DefaultFontSize;
    if(format.fontSize() > 0) {
        expectedSize = format.fontSize();
    }

    const auto font = m_fonts.find(format.font());
    if(font != m_fonts.end()) {
        TTF_Font *f = nullptr;
        const auto s = font->second.sizes.find(expectedSize);
        if(s != font->second.sizes.end()) {
            f = s->second;
        } else {
            f = TTF_OpenFont(font->second.path.c_str(), expectedSize);
            font->second.sizes[expectedSize] = f;
        }


        VisualEffect *effect = nullptr;
        if(anaglyphEnabled || anaglyphEnabled2)
             effect = new Anaglyph(e172::Vector(2, 1));

        int w = 0, h = 0;
        TTF_SizeText(f, string.c_str(), &w, &h);
        int offsetX = 0, offsetY = 0;
        if(format.alignment() & e172::TextFormat::AlignHCenter) {
            offsetX = -w / 2;
        }
        if(format.alignment() & e172::TextFormat::AlignVCenter) {
            offsetY = -h / 2;
        }
        SPM::BlendedText(surface, string, f, pos.intX() + offsetX, pos.intY() + offsetY, color, 1024, effect);
        delete effect;
        return e172::Vector(w, h);
    }

    return e172::Vector();
}

bool SDLRenderer::update() {
    while (m_lensQueue.size() > 0) {
        const auto l = m_lensQueue.front();
        __applyLensEffect(surface, l.point0, l.point1, l.coeficient);
        m_lensQueue.pop();
    }

    SDL_UpdateWindowSurface(window);
    return true;
}


void SDLRenderer::applySmooth(const e172::Vector &point0, const e172::Vector &point1, double coefficient) {    
    uint32_t pix[point1.intY()-point0.intY()][point1.intX()-point0.intX()];
    for(int y = point0.intY(); y < point1.intY(); ++y) {
        for(int x = point0.intX(); x < point1.intX(); ++x) {
            pix[y-point0.intY()][x-point0.intX()]
            = (SPM::GetPixel(surface, static_cast<int>(x + coefficient), y)
            + SPM::GetPixel(surface, static_cast<int>(x - coefficient), y)
            + SPM::GetPixel(surface, x, static_cast<int>(y + coefficient))
            + SPM::GetPixel(surface, x, static_cast<int>(y - coefficient))) / 4;

    //        SPM::FillPixel(surface, x, y, pix[y-point0.intY()][x-point0.intX()]);
        }
    }

    for(int y = point0.intY(); y < point1.intY(); ++y) {
        for(int x = point0.intX(); x < point1.intX(); ++x) {
            SPM::FillPixel(surface, x, y, pix[y-point0.intY()][x-point0.intX()]);
        }
    }

}
