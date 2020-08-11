#include "animatorassetexecutor.h"

#include <engine/graphics/abstractgraphicsprovider.h>

#include <animator.h>



AnimatorAssetExecutor::AnimatorAssetExecutor() {}

e172::Variant AnimatorAssetExecutor::proceed(const Json::Value &value, e172::AbstractGraphicsProvider *graphicsProvider, e172::AbstractAudioProvider *) {
    Json::Value spritesheet = value["spritesheet"];
    Json::Value frames = value["frames"];
    Json::Value tracks = value["tracks"];
    Json::Value play = value["play"];
    if(!spritesheet.isNull()) {
        Animator anim(graphicsProvider->loadImage(fullPath(spritesheet.asString())), frames.isNull() ? 1 : frames.asInt(), tracks.isNull() ? 1 : tracks.asInt());
        if(play.isString()) {
            if(play == "loop") {
                anim.play(Animator::Loop);
            } else {
                anim.play(Animator::NotRender);
            }
        } else {
            anim.play(Animator::Loop);
        }
        return e172::Variant::fromValue(anim);
    }
    return e172::Variant();
}
