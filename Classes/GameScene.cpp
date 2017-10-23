#include <audio/ios/SimpleAudioEngine_objc.h>
#include "GameScene.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    return GameScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    //preload music
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("assets/res/GameScene/effect_hit.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("assets/res/GameScene/effect_score.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.5f);
    CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(0.5f);




    return true;
}

