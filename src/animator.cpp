#include "animator.h"

#include "additional/spm.h"

const Uint8 Animator::PING_PONG = 0;
const Uint8 Animator::LOOP = 1;
const Uint8 Animator::ONEFRAME = 2;
const Uint8 Animator::FROZE = 3;
const Uint8 Animator::NOTRENDER = 4;
const Uint8 Animator::TOTHEFRAME = 5;
const Uint8 Animator::DEFAULT_INACTIVE = 6;



void Animator::setDefaultMode(const Uint8 &value) {
    defaultMode = value;
}

Animator::Animator() {

}

Animator::Animator(SDL_Surface *origin, int frames, int tracks) {
    this->angle = 0;
    this->zoom = 1;

    this->origin = origin;
    maxFrame = frames;
    maxTrack = tracks;
    const int frameWidth = origin->w / frames;
    const int frameHeigth = origin->h / tracks;

    currentFrame = 0;
    currentTrack = 0;

    for(int i = 0; i < maxFrame; i++) {
        this->frames.push_back(SPM::CutOutSurface(origin, i * frameWidth, 0, frameWidth, frameHeigth));
    }
}

void Animator::play(Uint8 mode) {
    this->mode = mode;
}


void Animator::loop(Context *context, Event *event) {
    UNUSED(context);
    UNUSED(event);
}

void Animator::setPosition(Vector pos) {
    this->pos = pos;
}

void Animator::setAngle(double angle) {
    this->angle = angle;
}

void Animator::setZoom(double zoom) {
    this->zoom = zoom;
}

void Animator::render(Renderer *renderer) {
    if (renderer != nullptr && this->mode != NOTRENDER) {
        Vector local = pos + renderer->getOffset();
        renderer->image(frames[static_cast<unsigned long>(currentFrame)], local, angle, zoom);
    }
    if(this->timer.count()) {
        if(this->mode == LOOP) {
            this->currentFrame++;
            if(this->currentFrame >= maxFrame) this->currentFrame = 0;
        }
    }
    if(defaultMode != DEFAULT_INACTIVE) mode = defaultMode;
}