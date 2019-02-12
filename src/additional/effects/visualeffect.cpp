#include "visualeffect.h"


VisualEffect::VisualEffect() {
}

VisualEffect::VisualEffect(Vector offset) {
    this->offset = offset;
}

SDL_Surface *VisualEffect::operator()(SDL_Surface *input) {
    return input;
}

void VisualEffect::setOffset(const Vector &value) {
    offset = value;
}

VisualEffect::~VisualEffect() {}
