#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#define GOAL_WIDTH 400

#include "SimpleAudioEngine.h"
#include "GameSprite.h"

class GameScene : public cocos2d::Scene {

    GameSprite *playerOne;
    GameSprite *playerTwo;
    GameSprite *ball;

    cocos2d::Vector<GameSprite*> playerVector;
    cocos2d::Label *scoreLabelPlayerOne;
    cocos2d::Label *scoreLabelPlayerTwo;

    cocos2d::Size screenSize;
    int scorePlayerOne;
    int scorePlayerTwo;

    void updatePlayerScore(int player);

public:
    GameScene();
    virtual ~GameScene();
    static cocos2d::Scene *createScene();
    virtual bool init();
    void onTouchesBegan(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *event);
    void onTouchesMoved(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *event);
    void onTouchesEnded(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *event);
    void update(float dt);
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
};

#endif
