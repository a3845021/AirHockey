//
// Created by Borna Koruznjak on 23/10/2017.
//

#ifndef __GAME_SPRITE_H__
#define __GAME_SPRITE_H__

#include "cocos2d.h"

class GameSprite : public cocos2d::Sprite {

public:

    CC_SYNTHESIZE(cocos2d::Vec2, nextPosition, NextPosition);

    CC_SYNTHESIZE(cocos2d::Vec2, vector, Vector);

    CC_SYNTHESIZE(cocos2d::Touch*, touch, Touch);

    GameSprite();

    virtual ~GameSprite();

    static GameSprite *gameSpriteWithFile(const char *pszFileName);

    virtual void setPosition(const cocos2d::Vec2 &pos) override;

    float radius();

};

#endif //__GAME_SPRITE_H__
