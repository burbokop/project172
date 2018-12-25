#include "spm.h"

Uint32 SPM::ColorRGB(Uint8 R, Uint8 G, Uint8 B) {
    return 65536 * R + 256 * G + B;
}

void SPM::FillPixel(SDL_Surface *surface, int x, int y, Uint32 color) {
    Uint32 *pixels = static_cast<Uint32*>(surface->pixels);
    if (x >= 0 && y >= 0 && x < surface->w && y < surface->h) pixels[(y * surface->w) + x] = color;
}

Uint32 SPM::GetPixel(SDL_Surface *surface, int x, int y) {
    return (static_cast<Uint32*>(surface->pixels))[x + surface->w * y];
}

void SPM::Line(SDL_Surface *surface, int point1_x, int point1_y, int point2_x, int point2_y, Uint32 color) {
    int d, dL, dU, dx, dy, temp;
    dx = point2_x - point1_x;
    dy = point2_y - point1_y;
    if (dy < 0)
    {
        temp = point2_x;
        point2_x = point1_x;
        point1_x = temp;
        temp = point2_y;
        point2_y = point1_y;
        point1_y = temp;
    }
    dx = point2_x - point1_x;
    dy = point2_y - point1_y;
    if (dx >= 0)
    {
        if (dy > dx)
        {
            d = dy - 2 * dx;
            dL = -2 * dx;
            dU = 2 * dy - 2 * dx;
            for(int x = point1_x, y = point1_y; y <= point2_y; y++)
            {
                SPM::FillPixel(surface, x, y, color);
                if (d >= 1)
                {
                    d += dL;
                }
                else
                {
                    x++;
                    d += dU;
                }
            }
        }
        else
        {
            d = 2 * dy - dx;
            dL = 2 * dy;
            dU = 2 * dy - 2 * dx;
            for(int x = point1_x, y = point1_y; x <= point2_x; x++)
            {
                SPM::FillPixel(surface, x, y, color);
                if (d <= 0)
                {
                    d += dL;
                }
                else
                {
                    y++;
                    d += dU;
                }
            }
        }
    }
    else if (dx < 0)
    {
        if (dy > -dx)
        {
            d = dy - 2 * -dx;
            dL = -2 * -dx;
            dU = 2 * dy - 2 * -dx;
            for (int x = point1_x, y = point1_y; y <= point2_y; y++)
            {
                SPM::FillPixel(surface, x, y, color);
                if (d >= 1)
                {
                    d += dL;
                }
                else
                {
                    --x;
                    d += dU;
                }
            }
        }
        else
        {
            d = 2 * dy + dx;
            dL = 2 * dy;
            dU = 2 * dy - 2 * -dx;
            for (int x = point1_x, y = point1_y; x >= point2_x; --x)
            {
                SPM::FillPixel(surface, x, y, color);
                if (d <= 0)
                {
                    d += dL;
                }
                else
                {
                    y++;
                    d += dU;
                }
            }
        }
    }
}

void SPM::VerticalLine(SDL_Surface *surface, int point_x, int point_y, int l, Uint32 color) {
    for (int i = 0; i < l; i++) SPM::FillPixel(surface, point_x , point_y + i, color);
}

void SPM::HorizontalLine(SDL_Surface *surface, int point_x, int point_y, int l, Uint32 color) {
    for (int i = 0; i < l; i++) SPM::FillPixel(surface, point_x + i , point_y, color);
}

void SPM::Square(SDL_Surface *surface, int point_x, int point_y, int l, Uint32 color) {
    for(int i = 0; i < l; i++)
    {
        SPM::FillPixel(surface, point_x + i, point_y, color);
        SPM::FillPixel(surface, point_x + i, point_y + l, color);
        SPM::FillPixel(surface, point_x, point_y + i, color);
        SPM::FillPixel(surface, point_x + l, point_y + i, color);
    }
    SPM::FillPixel(surface, point_x + l, point_y + l, color);
}

void SPM::FillSquare(SDL_Surface *surface, int point_x, int point_y, int l, Uint32 color) {
    for (int i = 0; i < l; i++)
    {
        for (int j = 0; j < l; j++)
        {
            SPM::FillPixel(surface, point_x + j, point_y + i, color);
        }
    }
}

void SPM::Rect(SDL_Surface *surface, int point1_x, int point1_y, int point2_x, int point2_y, Uint32 color) {
    int dx = point2_x - point1_x, dy = point2_y - point1_y;
    if (dx >= 0)
    {
        for (int i = 0; i <= dx; i++)
        {
            SPM::FillPixel(surface, point1_x + i, point1_y, color);
            SPM::FillPixel(surface, point1_x + i, point1_y + dy, color);
        }
    }
    else if (dx < 0)
    {
        for (int i = 0; i >= dx; i--)
        {
            SPM::FillPixel(surface, point1_x + i, point1_y, color);
            SPM::FillPixel(surface, point1_x + i, point1_y + dy, color);
        }
    }
    if (dy >= 0)
    {
        for (int i = 0; i <= dy; i++)
        {
            SPM::FillPixel(surface, point1_x, point1_y + i, color);
            SPM::FillPixel(surface, point1_x + dx, point1_y + i, color);
        }
    }
    else if (dy < 0)
    {
        for (int i = 0; i >= dy; i--)
        {
            SPM::FillPixel(surface, point1_x, point1_y + i, color);
            SPM::FillPixel(surface, point1_x + dx, point1_y + i, color);
        }
    }
}

void SPM::FillArea(SDL_Surface *surface, int point1_x, int point1_y, int point2_x, int point2_y, Uint32 color) {
    int dx = point2_x - point1_x, dy = point2_y - point1_y;
    if (dx >= 0)
    {
        if (dy >= 0)
        {
            for (int i = 0; i < dy; i++)
            {
                for (int j = 0; j < dx; j++)
                {
                    SPM::FillPixel(surface, point1_x + j, point1_y + i, color);
                }
            }
        }
        else
        {
            for (int i = 0; i >= dy; i--)
            {
                for (int j = 0; j < dx; j++)
                {
                    SPM::FillPixel(surface, point1_x + j, point1_y + i, color);
                }
            }
        }
    }
    else
    {
        if (dy >= 0)
        {
            for (int i = 0; i < dy; i++)
            {
                for (int j = 0; j >= dx; j--)
                {
                    SPM::FillPixel(surface, point1_x + j, point1_y + i, color);
                }
            }
        }
        else
        {
            for (int i = 0; i >= dy; i--)
            {
                for (int j = 0; j >= dx; j--)
                {
                    SPM::FillPixel(surface, point1_x + j, point1_y + i, color);
                }
            }
        }
    }
}

void SPM::Circle(SDL_Surface *surface, int center_x, int center_y, int radius, Uint32 color) {
    for(int i = 0; i < sqrt(radius * radius - i * i); i++)
    {
        int i2 = static_cast<int>(sqrt(radius * radius - i * i));
        SPM::FillPixel(surface, center_x + i, center_y + i2, color);
        SPM::FillPixel(surface, center_x - i, center_y - i2, color);
        SPM::FillPixel(surface, center_x + i, center_y - i2, color);
        SPM::FillPixel(surface, center_x - i, center_y + i2, color);

        SPM::FillPixel(surface, center_x + i2, center_y + i, color);
        SPM::FillPixel(surface, center_x - i2, center_y - i, color);
        SPM::FillPixel(surface, center_x - i2, center_y + i, color);
        SPM::FillPixel(surface, center_x + i2, center_y - i, color);
    }
}

void SPM::Grid(SDL_Surface *surface, int point1_x, int point1_y, int point2_x, int point2_y, int interval, Uint32 color) {
    for (int i = 0; i < std::abs(point2_x - point1_x) / interval; i++)
    {
        for (int j = 0; j < std::abs(point2_y - point1_y); j++)
        {
            SPM::FillPixel(surface, point1_x + (i * interval), point1_y + j, color);
        }
    }
    for (int i = 0; i < std::abs(point2_y - point1_y) / interval; i++)
    {
        for (int j = 0; j < std::abs(point2_x - point1_x); j++)
        {
            SPM::FillPixel(surface, point1_x + j, point1_y + (i * interval), color);
        }
    }
}

void SPM::BlitRotatedSurface(SDL_Surface *surface, SDL_Surface *screen_surface, int x, int y, double angle, double zoom, int smooth) {
    SDL_Surface *temp_surface = nullptr;
    SDL_Rect rect = {
        static_cast<int>(x - surface->w * zoom / 2),
        static_cast<int>(y - surface->h * zoom / 2), 0, 0
    };
    angle = angle * RADS_MULTIPLIER;
    temp_surface = rotozoomSurface(surface, angle, zoom, smooth);
    rect.x = static_cast<int>(rect.x - temp_surface->w / 2 + surface->w * zoom / 2);
    rect.y = static_cast<int>(rect.y - temp_surface->h / 2 + surface->h * zoom / 2);
    SDL_BlitSurface(temp_surface, nullptr, screen_surface, &rect);
}

void SPM::BlendedText(SDL_Surface *surface, std::string text_line, TTF_Font *text_font, int text_x, int text_y, SDL_Color text_color) {
    SDL_Surface *text_surface = nullptr;
    SDL_Rect text_rect;
    text_surface = TTF_RenderText_Blended(text_font, text_line.c_str(), text_color);
    text_rect.x = text_x;
    text_rect.y = text_y;
    SDL_BlitSurface(text_surface, nullptr, surface, &text_rect);
    SDL_FreeSurface(text_surface);
}

void SPM::BlendedText(SDL_Surface *surface, std::string text_line, TTF_Font *text_font, int text_x, int text_y, Uint32 color) {
    SDL_Surface *text_surface = nullptr;
    SDL_Rect text_rect;
    SDL_Color rgbColor;
    rgbColor.a = (color >> 24) & 255;
    rgbColor.r = (color >> 16) & 255;
    rgbColor.g = (color >> 8) & 255;
    rgbColor.b = (color >> 0) & 255;
    text_surface = TTF_RenderUTF8_Blended(text_font, text_line.c_str(), rgbColor);
    text_rect.x = text_x;
    text_rect.y = text_y;
    SDL_BlitSurface(text_surface, nullptr, surface, &text_rect);
    SDL_FreeSurface(text_surface);
}

SDL_Surface *SPM::CutOutSurface(SDL_Surface *surface, int x, int y, int w, int h) {
    SDL_Rect surfaceRect;
    surfaceRect.x = x;
    surfaceRect.y = y;
    surfaceRect.w = w;
    surfaceRect.h = h;
    SDL_Surface *tmp;
    tmp = SDL_CreateRGBSurface(0, surfaceRect.w, surfaceRect.h, 32, 0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000);
    SDL_BlitSurface(surface, &surfaceRect, tmp, nullptr);
    return tmp;
}

SDL_Surface *SPM::Flip(SDL_Surface *surface, bool xFlip, bool yFlip) {
    SDL_Surface *result = SDL_CreateRGBSurface(0, surface->w, surface->h, 32, 0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000);
    Uint32 *pixels = static_cast<Uint32*>(surface->pixels);
    if(xFlip) {
        for (int y = 0; y < surface->h; ++y) {
            for (int x = 0; x < surface->w; ++x) {
                SPM::FillPixel(result, surface->w - x, y, pixels[x + surface->w * y]);
            }
        }
    }
    else if(yFlip) {
        for (int y = 0; y < surface->h; ++y) {
            for (int x = 0; x < surface->w; ++x) {
                SPM::FillPixel(result, x, surface->h - y, pixels[x + surface->w * y]);
            }
        }
    }
    else if(xFlip && yFlip) {
        for (int y = 0; y < surface->h; ++y) {
            for (int x = 0; x < surface->w; ++x) {
                SPM::FillPixel(result, surface->w - x, surface->h - y, pixels[x + surface->w * y]);
            }
        }
    }
    return result;
}
