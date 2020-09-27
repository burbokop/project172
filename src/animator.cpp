#include "animator.h"

#include <src/engine/graphics/abstractrenderer.h>


void Animator::setDefaultMode(unsigned value) {
    defaultMode = value;
}

bool Animator::isValid() const {
    return m_isValid;
}

int Animator::frameCount() const
{
    return m_frameCount;
}

int Animator::trackCount() const
{
    return m_trackCount;
}

Animator::Animator() {
    
}

Animator::Animator(const e172::Image &origin, int frames, int tracks) {
    this->angle = 0;
    this->zoom = 1;

    this->origin = origin;
    m_frameCount = frames;
    m_trackCount = tracks;
    const int frameWidth = origin.width() / frames;
    const int frameHeigth = origin.height() / tracks;

    currentFrame = 0;
    currentTrack = 0;

    for(int i = 0; i < m_frameCount; i++) {
        this->frames.push_back(origin.fragment(i * frameWidth, 0, frameWidth, frameHeigth));
    }

    m_isValid = this->frames.size() > 0;
}

void Animator::play(unsigned mode) {
    this->mode = mode;
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
    if(m_isValid) {
        if (renderer != nullptr && this->mode != NotRender) {
            e172::Vector local = pos + renderer->offset();
            renderer->drawImage(frames[static_cast<unsigned long>(currentFrame)], local, angle, zoom);
        }
        if(this->timer.check()) {
            if(this->mode == Loop) {
                this->currentFrame++;
                if(this->currentFrame >= m_frameCount) this->currentFrame = 0;
            }
        }
        if(defaultMode != Inactive) mode = defaultMode;
    }
}

bool operator ==(const Animator &anim0, const Animator &anim1) {
    return anim0.id == anim1.id;
}
