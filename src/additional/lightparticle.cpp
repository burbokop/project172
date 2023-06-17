#include "lightparticle.h"

#include <inttypes.h>

#include <src/context.h>

#include <src/graphics/abstractrenderer.h>

//#include <vulkan/vulkan_intel.h>

const unsigned LightParticle::PIXEL = 0;
const unsigned LightParticle::SQUARE = 1;
const unsigned LightParticle::CIRCLE = 2;

const int LightParticle::DEFAULT_AVERAGE_LIFE_TIME = 6000;
const int LightParticle::DEFAULT_LIFE_TIME_DELTA = 4000;

const double LightParticle::STOP_MOVING_VELOCITY = 0.015;

LightParticle::LightParticle(e172::FactoryMeta &&meta,
                             unsigned shape,
                             int averageLifeTime,
                             int lifeTimeDelta)
    : e172::Entity(std::move(meta))
{
    uint32_t colors[] = { 0xdeff17, 0xfe4600, 0xf9990f, 0x8a27ff };
    m_color = colors[std::rand() % 4];
    m_shape = shape;
    m_destroyTimer = new e172::ElapsedTimer(
        static_cast<unsigned>((rand() % (2 * lifeTimeDelta)) + (averageLifeTime - lifeTimeDelta)));
    m_destroyTimer->reset();
    m_velocityMultiplier = static_cast<double>((std::rand() % 4 + 3)) / 5;
}

void LightParticle::place(e172::Vector<double> pos, e172::Vector<double> vel) {
    m_pos = pos;
    m_vel = vel;
}


void LightParticle::proceed(e172::Context *context, e172::EventHandler *eventHandler) {
    UNUSED(eventHandler);
    if (m_destroyTimer && m_destroyTimer->check()) {
        context->emitMessage(e172::Context::DestroyEntity, entityId());
    }
    m_vel = m_vel * (1 - context->deltaTime() * m_velocityMultiplier);
    m_pos += m_vel * context->deltaTime() * 0.1;
}

void LightParticle::render(e172::AbstractRenderer *renderer) {
    switch (m_shape) {
    case PIXEL:
        renderer->drawPixel(renderer->offset() + m_pos, m_color);
        break;
    case SQUARE:
        renderer->drawSquare(renderer->offset() + m_pos, m_radius / 2, m_color);
        break;
    case CIRCLE:
        renderer->drawCircle(renderer->offset() + m_pos, m_radius, m_color);
        break;
    }
}
