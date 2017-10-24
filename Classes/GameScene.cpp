
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

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    playerVector = cocos2d::Vector<GameSprite *>(2);
    scorePlayerOne = 0;
    scorePlayerTwo = 0;
    screenSize = Director::getInstance()->getWinSize();

    auto imageCourt = cocos2d::Sprite::create("assets/res/GameScene/img_background.png");
    imageCourt->setPosition(Vec2(screenSize.width * 0.5, screenSize.height * 0.5));
    this->addChild(imageCourt);

    playerOne = GameSprite::gameSpriteWithFile("assets/res/GameScene/img_player.png");
    playerOne->setPosition(cocos2d::Vec2(screenSize.width * 0.5f, playerOne->radius() * 2));
    playerVector.pushBack(playerOne);
    this->addChild(playerOne);

    playerTwo = GameSprite::gameSpriteWithFile("assets/res/GameScene/img_player.png");
    playerTwo->setPosition(
            cocos2d::Vec2(screenSize.width * 0.5f, screenSize.height - playerTwo->radius() * 2));
    playerVector.pushBack(playerTwo);
    this->addChild(playerTwo);

    ball = GameSprite::gameSpriteWithFile("assets/res/GameScene/img_puck.png");
    ball->setPosition(cocos2d::Vec2(screenSize.width * 0.5f, screenSize.height * 0.5f));
    this->addChild(ball);

    scoreLabelPlayerOne = cocos2d::Label::createWithTTF("0", "assets/fonts/arial.ttf", 60);
    scoreLabelPlayerOne->setPosition(
            cocos2d::Vec2(screenSize.width - 60, screenSize.height * 0.5f - 80));
    scoreLabelPlayerOne->setRotation(180);
    this->addChild(scoreLabelPlayerOne);

    scoreLabelPlayerTwo = cocos2d::Label::createWithTTF("0", "assets/fonts/arial.ttf", 60);
    scoreLabelPlayerTwo->setPosition(
            cocos2d::Vec2(screenSize.width - 60, screenSize.height * 0.5f + 80));
    scoreLabelPlayerTwo->setRotation(180);
    this->addChild(scoreLabelPlayerTwo);

    //preload music
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(
            "assets/res/GameScene/effect_hit.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(
            "assets/res/GameScene/effect_score.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.5f);
    CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(0.5f);

    auto touchListener = cocos2d::EventListenerTouchAllAtOnce::create();
    touchListener->onTouchesBegan = CC_CALLBACK_2(GameScene::onTouchesBegan, this);
    touchListener->onTouchesMoved = CC_CALLBACK_2(GameScene::onTouchesMoved, this);
    touchListener->onTouchesEnded = CC_CALLBACK_2(GameScene::onTouchesEnded, this);

    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
    this->scheduleUpdate();

    return true;
}

void GameScene::onTouchesBegan(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *event) {
    for (auto touch : touches) {
        if (touch != nullptr) {
            auto tapLocation = touch->getLocation();
//            __android_log_print(ANDROID_LOG_DEBUG, "TestOne", "position : %f",touch->getLocation().x);
            for (auto player : playerVector) {
                if (player->getBoundingBox().containsPoint(tapLocation)) {
                    player->setTouch(touch);
                }
            }

        }
    }
}

void GameScene::onTouchesMoved(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *event) {
    //loop through all moving touches
    for (auto touch : touches) {
        if (touch != nullptr) {
            auto tapLocation = touch->getLocation();
            __android_log_print(ANDROID_LOG_DEBUG, "AirHockey", "lokacija x:%f, y:%f",
                                tapLocation.x, tapLocation.y);
            for (auto player : playerVector) {
                //if touch belongs to player
                if (player->getTouch() != nullptr && player->getTouch() == touch) {

                    Point nextPosition = tapLocation;

                    //keep player inside screen
                    if (nextPosition.x < player->radius())
                        nextPosition.x = player->radius();
                    if (nextPosition.x > screenSize.width - player->radius())
                        nextPosition.x = screenSize.width - player->radius();
                    if (nextPosition.y < player->radius())
                        nextPosition.y = player->radius();
                    if (nextPosition.y > screenSize.height - player->radius())
                        nextPosition.y = screenSize.height - player->radius();

                    //keep player inside its court
                    if (player->getPosition().y < screenSize.height * 0.5f) {
                        //player one
                        if (nextPosition.y > screenSize.height * 0.5f - player->radius()) {
                            nextPosition.y = screenSize.height * 0.5f - player->radius();
                        }
                    } else {
                        //player two
                        if (nextPosition.y < screenSize.height * 0.5f + player->radius()) {
                            nextPosition.y = screenSize.height * 0.5f + player->radius();
                        }
                    }

                    player->setNextPosition(nextPosition);
                    player->setVector(
                            Vec2(tapLocation.x - player->getPositionX(),
                                 tapLocation.y - player->getPositionY()));
                }
            }
        }
    }
}

void
GameScene::onTouchesEnded(const std::vector<cocos2d::Touch *> &touches, cocos2d::Event *event) {
    //loop through all ending touches
    for (auto touch : touches) {
        if (touch != nullptr) {
            for (auto player : playerVector) {
                if (player->getTouch() != nullptr && player->getTouch() == touch) {
                    //if touch ending belongs to this player, clear it
                    player->setTouch(nullptr);
                    player->setVector(Vec2(0, 0));
                }
            }
        }
    }
}

void GameScene::update(float dt) {
    //update puck
    auto ballNextPosition = ball->getNextPosition();
    auto ballVector = ball->getVector();
    ballVector *= 0.98f;

    ballNextPosition.x += ballVector.x;
    ballNextPosition.y += ballVector.y;

    //test for puck and mallet collision
    float squared_radii = pow(playerOne->radius() + ball->radius(), 2);

    for (auto player : playerVector) {

        auto playerNextPosition = player->getNextPosition();
        auto playerVector = player->getVector();

        float diffx = ballNextPosition.x - player->getPositionX();
        float diffy = ballNextPosition.y - player->getPositionY();

        float distanceOne = pow(diffx, 2) + pow(diffy, 2);
        float distanceTwo = pow(ball->getPositionX() - playerNextPosition.x, 2) +
                            pow(ball->getPositionY() - playerNextPosition.y, 2);

        if (distanceOne <= squared_radii || distanceTwo <= squared_radii) {

            float magBall = pow(ballVector.x, 2) + pow(ballVector.y, 2);
            float magPlayer = pow(playerVector.x, 2) + pow(playerVector.y, 2);

            float force = sqrt(magBall + magPlayer);
            float angle = atan2(diffy, diffx);

            ballVector.x = force * cos(angle);
            ballVector.y = (force * sin(angle));

            ballNextPosition.x =
                    playerNextPosition.x + (player->radius() + ball->radius() + force) * cos(angle);
            ballNextPosition.y =
                    playerNextPosition.y + (player->radius() + ball->radius() + force) * sin(angle);

            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(
                    "assets/res/GameScene/effect_hit.wav");
        }
    }

    //check collision of ball and sides
    if (ballNextPosition.x < ball->radius()) {
        ballNextPosition.x = ball->radius();
        ballVector.x *= -0.8f;
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(
                "assets/res/GameScene/effect_hit.wav");
    }

    if (ballNextPosition.x > screenSize.width - ball->radius()) {
        ballNextPosition.x = screenSize.width - ball->radius();
        ballVector.x *= -0.8f;
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(
                "assets/res/GameScene/effect_hit.wav");
    }
    //ball and top of the court
    if (ballNextPosition.y > screenSize.height - ball->radius()) {
        if (ball->getPosition().x < screenSize.width * 0.5f - GOAL_WIDTH * 0.5f ||
            ball->getPosition().x > screenSize.width * 0.5f + GOAL_WIDTH * 0.5f) {
            ballNextPosition.y = screenSize.height - ball->radius();
            ballVector.y *= -0.8f;
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(
                    "assets/res/GameScene/effect_hit.wav");
        }
    }
    //ball and bottom of the court
    if (ballNextPosition.y < ball->radius()) {
        if (ball->getPosition().x < screenSize.width * 0.5f - GOAL_WIDTH * 0.5f ||
            ball->getPosition().x > screenSize.width * 0.5f + GOAL_WIDTH * 0.5f) {
            ballNextPosition.y = ball->radius();
            ballVector.y *= -0.8f;
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(
                    "assets/res/GameScene/effect_hit.wav");
        }
    }

    //finally, after all checks, update ball's vector and next position
    ball->setVector(ballVector);
    ball->setNextPosition(ballNextPosition);


    //check for goals!
    if (ballNextPosition.y < -ball->radius() * 2) {
        this->updatePlayerScore(2);

    }
    if (ballNextPosition.y > screenSize.height + ball->radius() * 2) {
        this->updatePlayerScore(1);
    }

    //move pieces to next position
    playerOne->setPosition(playerOne->getNextPosition());
    playerTwo->setPosition(playerTwo->getNextPosition());
    ball->setPosition(ball->getNextPosition());
}

void GameScene::updatePlayerScore(int player) {
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("score.wav");

    ball->setVector(Vec2(0, 0));
    //if player 1 scored...
    if (player == 1) {

        scorePlayerOne++;
        scoreLabelPlayerOne->setString(
                String::createWithFormat("%i", scorePlayerOne)->getCString());
        //move ball to player 2 court
        ball->setNextPosition(
                Vec2(screenSize.width * 0.5f, screenSize.height * 0.5f + 2 * ball->radius()));

        //if player 2 scored...
    } else {

        scorePlayerTwo++;
        scoreLabelPlayerTwo->setString(
                String::createWithFormat("%i", scorePlayerTwo)->getCString());
        //move ball to player 1 court
        ball->setNextPosition(
                Vec2(screenSize.width * 0.5f, screenSize.height * 0.5f - 2 * ball->radius()));

    }
    //move players to original position
    playerOne->setPosition(Vec2(screenSize.width * 0.5f, playerOne->radius() * 2));
    playerTwo->setPosition(Vec2(screenSize.width * 0.5f, screenSize.height - playerOne->radius() * 2));

    //clear current touches
    playerOne->setTouch(nullptr);
    playerTwo->setTouch(nullptr);
}


