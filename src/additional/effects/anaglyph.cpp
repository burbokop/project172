#include "anaglyph.h"


SDL_Surface *separateChannel(SDL_Surface *origin, Uint32 mask) {
    SDL_Surface* result = SDL_CreateRGBSurface(0, origin->w, origin->h, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
    SDL_SetSurfaceAlphaMod(result, (mask & 0xff000000) >> 24);

    Uint32 *src_pixels = static_cast<Uint32*>(origin->pixels);
    Uint32 *dst_pixels = static_cast<Uint32*>(result->pixels);

    SDL_LockSurface(result);
    for(int i = 0, l = origin->w * origin->h; i < l; i++) {
        dst_pixels[i] = (src_pixels[i] & (mask | 0xff000000));
    }
    SDL_UnlockSurface(result);

    return result;
}

Uint32 blendChanel(Uint8 C1, Uint8 A1, Uint8 C2, Uint8 A2) {
    Uint16 AA = A1 + A2;
    return AA != 0 ? ((C1 * A1 + C2 * A2) / AA) : 0;
}

Uint32 blendColor(Uint32 color1, Uint32 color2) {
    Uint8 A1 = (color1 >> 24) & 255;
    Uint8 R1 = (color1 >> 16) & 255;
    Uint8 G1 = (color1 >> 8) & 255;
    Uint8 B1 = (color1 >> 0) & 255;

    Uint8 A2 = (color2 >> 24) & 255;
    Uint8 R2 = (color2 >> 16) & 255;
    Uint8 G2 = (color2 >> 8) & 255;
    Uint8 B2 = (color2 >> 0) & 255;

    Uint8 A = (255 - ((255 - A1) * (255 - A2) / 255));
    //Uint8 A = (A1 < A2) ? A1 : A2;

    Uint32 R = blendChanel(R1, A1, R2, A2);
    Uint32 G = blendChanel(G1, A1, G2, A2);
    Uint32 B = blendChanel(B1, A1, B2, A2);


    //Uint8 R = (A1 + A2) != 0 ? ((R1 * A1 + R2 * A2) / (A1 + A2)) : 0;
    //Uint8 G = (A1 + A2) != 0 ? ((G1 * A1 + G2 * A2) / (A1 + A2)) : 0;
    //Uint8 B = (A1 + A2) != 0 ? ((B1 * A1 + B2 * A2) / (A1 + A2)) : 0;

    return ((A << 24) | (R << 16) | (G << 8) | (B << 0));
}



void SPM_FillPixel(SDL_Surface *surface, int x, int y, Uint32 color) {
    Uint32 *pixels = static_cast<Uint32*>(surface->pixels);
    if (x >= 0 && y >= 0 && x < surface->w && y < surface->h) pixels[(y * surface->w) + x] = color;
}

Uint32 SPM_GetPixel(SDL_Surface *surface, int x, int y) {
    return (x >= 0 && y >= 0 && x < surface->w && y < surface->h) ? (static_cast<Uint32*>(surface->pixels))[x + surface->w * y] : 0;
}


SDL_Surface *blendSurface(SDL_Surface *src1, SDL_Surface *src2, int x, int y) {
    SDL_Surface* result = SDL_CreateRGBSurface(0, src1->w + std::abs(x), src1->h + std::abs(y), 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
    SDL_LockSurface(result);
    for(int i = 0, l = result->w; i < l; i++) {
        for(int j = 0, l = result->h; j < l; j++) {
            int x1, y1, x2, y2;
            if (x > 0) {
                if(y > 0) {
                    x1 = i;
                    y1 = j;
                    x2 = i - x;
                    y2 = j - y;
                } else {
                    x1 = i;
                    y1 = j + y;
                    x2 = i - x;
                    y2 = j;
                }
            } else {
                if(y > 0) {
                    x1 = i + x;
                    y1 = j + y;
                    x2 = i;
                    y2 = j;
                } else {
                    x1 = i + x;
                    y1 = j;
                    x2 = i;
                    y2 = j - y;
                }
            }

            SPM_FillPixel(
                result, i, j,
                blendColor(
                    SPM_GetPixel(src1, x1, y1),
                    SPM_GetPixel(src2, x2, y2)
                )
            );
        }
    }
    SDL_UnlockSurface(result);
    return result;
}


Anaglyph::Anaglyph() : VisualEffect () {
}

Anaglyph::Anaglyph(Vector offset) : VisualEffect (offset) {
}


SDL_Surface *Anaglyph::operator ()(SDL_Surface *input) {
    SDL_Surface *r = separateChannel(input, 0xffff0000);
    SDL_Surface *b = separateChannel(input, 0xff00ffff);
    SDL_Surface *result = blendSurface(r, b, offset.getIntX(), offset.getIntY());
    SDL_FreeSurface(r);
    SDL_FreeSurface(b);
    return result;
}
