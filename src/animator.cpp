#include "animator.h"

#include "additional/spm.h"

const unsigned Animator::PING_PONG = 0;
const unsigned Animator::LOOP = 1;
const unsigned Animator::ONEFRAME = 2;
const unsigned Animator::FROZE = 3;
const unsigned Animator::NOTRENDER = 4;
const unsigned Animator::TOTHEFRAME = 5;
const unsigned Animator::DEFAULT_INACTIVE = 6;



void Animator::setDefaultMode(unsigned value) {
    defaultMode = value;
}

Animator::Animator() {

}

Animator::Animator(const e172::Image &origin, int frames, int tracks) {
    this->angle = 0;
    this->zoom = 1;

    this->origin = origin;
    maxFrame = frames;
    maxTrack = tracks;
    const int frameWidth = origin.width() / frames;
    const int frameHeigth = origin.height() / tracks;

    currentFrame = 0;
    currentTrack = 0;

    for(int i = 0; i < maxFrame; i++) {
        // OLD VERSION (DO NOT DELETE): this->frames.push_back(SPM::CutOutSurface(origin, i * frameWidth, 0, frameWidth, frameHeigth));
        this->frames.push_back(origin.nub(i * frameWidth, 0, frameWidth, frameHeigth));
    }
}

void Animator::play(unsigned mode) {
    this->mode = mode;
}


void Animator::tick(Context *context, Event *event) {
    UNUSED(context);
    UNUSED(event);
}

void Animator::setPosition(e172::Vector pos) {
    this->pos = pos;
}

void Animator::setAngle(double angle) {
    this->angle = angle;
}

void Animator::setZoom(double zoom) {
    this->zoom = zoom;
}

void Animator::render(e172::AbstractRenderer *renderer) {
    if (renderer != nullptr && this->mode != NOTRENDER) {
        e172::Vector local = pos + renderer->offset();
        renderer->drawImage(frames[static_cast<unsigned long>(currentFrame)], local, angle, zoom);
    }
    if(this->timer.count()) {
        if(this->mode == LOOP) {
            this->currentFrame++;
            if(this->currentFrame >= maxFrame) this->currentFrame = 0;
        }
    }
    if(defaultMode != DEFAULT_INACTIVE) mode = defaultMode;
}
