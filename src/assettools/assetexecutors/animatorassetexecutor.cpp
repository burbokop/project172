#include "animatorassetexecutor.h"

#include <engine/graphics/abstractgraphicsprovider.h>

#include <animator.h>



AnimatorAssetExecutor::AnimatorAssetExecutor() {}

e172::Variant AnimatorAssetExecutor::proceed(const Json::Value &value, e172::AbstractGraphicsProvider *graphicsProvider) {
    Json::Value spritesheet = value["spritesheet"];
    Json::Value frames = value["frames"];
    Json::Value tracks = value["tracks"];
    Json::Value play = value["play"];
    if(!spritesheet.isNull()) {
        Animator anim(graphicsProvider->loadImage(fullPath(spritesheet.asString())), frames.isNull() ? 1 : frames.asInt(), tracks.isNull() ? 1 : tracks.asInt());
        if(play.isString()) {
            if(play == "loop") {
                anim.play(Animator::LOOP);
            } else {
                anim.play(Animator::NOTRENDER);
            }
        } else {
            anim.play(Animator::LOOP);
        }
        return e172::Variant::fromValue(anim);
    }
    return e172::Variant();
}
