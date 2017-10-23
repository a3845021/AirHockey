
#include "GameScene.h"

USING_NS_CC;

GameScene::GameScene() {}

GameScene::~GameScene() {
    playerVector.clear();
    CC_SAFE_DELETE(playerOne);
    CC_SAFE_DELETE(playerTwo);
    CC_SAFE_DELETE(ball);
    CC_SAFE_DELETE(scoreLabelPlayerOne);
    CC_SAFE_DELETE(scoreLabelPlayerTwo);
}

Scene *GameScene::createScene() {
    return GameScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char *filename) {
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameScene::init() {
    //////////////////////////////
    // 1. super init first
    if (!Scene::init()) {
        return false;
    }

    playerVector = cocos2d::Vector<GameSprite *>(2);
    scorePlayerOne = 0;
    scorePlayerTwo = 0;
    screenSize = Director::getInstance()->getWinSize();

    auto imageCourt = cocos2d::Sprite::create("assets/res/GameScene/img_background.png");
    imageCourt->setPosition(Vec2(screenSize.width * 0.5, screenSize.height * 0.5));
    this->addChild(imageCourt);

    playerOne = GameSprite::gameSpriteWithFile("assets/res/GameScene/img_player.png");
    playerOne->setPosition(cocos2d::Vec2(screenSize.width / 2, playerOne->radius() * 2));
    playerVector.pushBack(playerOne);
    this->addChild(playerOne);

    playerTwo = GameSprite::gameSpriteWithFile("assets/res/GameScene/img_player.png");
    playerTwo->setPosition(
            cocos2d::Vec2(screenSize.width / 2, screenSize.height - playerTwo->radius() * 2));
    playerVector.pushBack(playerTwo);
    this->addChild(playerTwo);

    ball = GameSprite::gameSpriteWithFile("assets/res/GameScene/img_puck.png");
    ball->setPosition(cocos2d::Vec2(screenSize.width/2, screenSize.height/2));
    this->addChild(ball);

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    //preload music
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(
            "assets/res/GameScene/effect_hit.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(
            "assets/res/GameScene/effect_score.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.5f);
    CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(0.5f);


    return true;
}

void
GameScene::onTouchesBegan(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *event) {
//todo
}

void
GameScene::onTouchesMoved(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *event) {
//todo
}

void
GameScene::onTouchesEnded(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *event) {
//todo
}

void GameScene::update(float dt) {
    //Node::update(dt);
}

