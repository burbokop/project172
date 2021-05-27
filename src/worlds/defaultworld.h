#ifndef DEFAULTWORLD_H
#define DEFAULTWORLD_H


#include "world.h"


class DefaultWorld : public WorldPreset {
public:
    DefaultWorld();

    // World interface
public:
    virtual GenerationResult generate(e172::Context *context) override;

    GenerationResult generatePlayer(e172::Context *context, const std::string &templateId, const e172::ptr<Person> &person);
    GenerationResult generateSomeShips(e172::Context *context, size_t cnt, const e172::ptr<Person> &person);
    GenerationResult generateSomeStations(e172::Context *context, size_t cnt, const e172::ptr<Person> &person);
};

#endif // DEFAULTWORLD_H
