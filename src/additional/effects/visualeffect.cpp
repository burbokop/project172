#include "visualeffect.h"


VisualEffect::VisualEffect() {
}

VisualEffect::VisualEffect(e172::Vector offset) {
    this->offset = offset;
}

SDL_Surface *VisualEffect::operator()(SDL_Surface *input) {
    return input;
}

void VisualEffect::setOffset(const e172::Vector &value) {
    offset = value;
}

VisualEffect::~VisualEffect() {}
