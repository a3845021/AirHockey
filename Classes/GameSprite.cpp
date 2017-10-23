//
// Created by Borna Koruznjak on 23/10/2017.
//

#include "GameSprite.h"

GameSprite::GameSprite() {
    vector = cocos2d::Vec2(0, 0);
}

GameSprite::~GameSprite() {
    //destructor
}

GameSprite *GameSprite::gameSpriteWithFile(const char *pszFileName) {
    auto sprite = new GameSprite();
    if (sprite && sprite->initWithFile(pszFileName)) {
        sprite->autorelease();
        return sprite;
    }

    CC_SAFE_DELETE(sprite);
    return sprite = nullptr;
}

void GameSprite::setPosition(const cocos2d::Vec2 &position) {
    cocos2d::Sprite::setPosition(position);
    if (!nextPosition.equals(position)) {
        nextPosition = position;
    }
}

float GameSprite::radius() {
    return getTexture()->getContentSize().width * 0.5f;
}
