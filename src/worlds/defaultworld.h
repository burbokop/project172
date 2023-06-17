#pragma once

#include "world.h"

namespace proj172::core {

class DefaultWorld : public WorldPreset {
public:
    DefaultWorld(e172::Random random = e172::Random::uniq())
        : m_random(std::move(random))
    {}

    // World interface
public:
    virtual GenerationResult generate(e172::Context *context) override;

    GenerationResult generatePlayer(e172::Context *context, const std::string &templateId, const e172::ptr<Person> &person);
    GenerationResult generateSomeShips(e172::Context *context, size_t cnt, const e172::ptr<Person> &person);
    GenerationResult generateSomeStations(e172::Context *context,
                                          size_t cnt,
                                          const e172::ptr<Person> &person);

private:
    e172::Random m_random;
};

} // namespace proj172::core
