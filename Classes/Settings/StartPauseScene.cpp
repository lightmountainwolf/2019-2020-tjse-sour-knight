#include "Settings/StartPauseScene.h"
#include "Scene/firstStage.h"
#include "Settings/StartPauseSettingScene.h"

using namespace CocosDenshion;
USING_NS_CC;

Scene* StartPause::createScene()
{
    return StartPause::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in StartPause.cpp\n");
}

// on "init" you need to initialize your instance
bool StartPause::init()
{
    if (!Scene::init())
    {
        return false;
    }

    log("StartPause init");

    //doContinueGame=false;

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //background-start2
    auto background1 = Sprite::create("Backgrounds/start2.png");
    background1->setAnchorPoint(Point(0, 0));
    background1->setPosition(Point(0, 0));
    addChild(background1);

    //menu-exit
    MenuItemImage* exit = MenuItemImage::create(
        "Buttons/buttonExit.png","Buttons/buttonExitClicked.png", CC_CALLBACK_1(StartPause::menuCloseCallback, this));
    exit->setPosition(Vec2(100, 80));

    //menu-setting
    MenuItemImage* setting = MenuItemImage::create(
        "Buttons/buttonSet.png","Buttons/buttonSetClicked.png", CC_CALLBACK_1(StartPause::menuSettingCallback, this));
    setting->setPosition(Vec2(100, 200));

    //menu-new game
    MenuItemImage* newGame = MenuItemImage::create(
        "Buttons/buttonNewGame.png","Buttons/buttonNewGameClicked.png", CC_CALLBACK_1(StartPause::menuNewGameCallback, this));
    newGame->setPosition(Vec2(400, 150));

    //menu-continue game
    MenuItemImage* continueGame = MenuItemImage::create(
        "Buttons/buttonContinueGame.png", "Buttons/buttonContinueGameClicked.png", CC_CALLBACK_1(StartPause::menuContinueGameCallback, this));
    continueGame->setPosition(Vec2(400, 300));

    Menu* menu= Menu::create(exit, setting, newGame,continueGame, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);

    return true;
}

void StartPause::onEnter()
{
    Scene::onEnter();
    log("StartPause onEnter");
}

void StartPause::onEnterTransitionDidFinish()
{
    Scene::onEnterTransitionDidFinish();
    log("StartPause onEnterTransitionDidFinish");
    ////playMusic("sound/FightMapBGM.mp3", true);
    if (doContinueGame == true)
    {
        Director::getInstance()->popScene();
        playSound("sound/ClickSound.mp3");
    }
}

void StartPause::onExit()
{
    Scene::onExit();
    log("StartPause onExit");
}

void StartPause::onExitTransitionDidStart()
{
    Scene::onExitTransitionDidStart();
    log("StartPause onExitTransitionDidStart");
}

void StartPause::cleanup()
{
    Scene::cleanup();
    log("StartPause cleanup");
}

//exit
void StartPause::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
    playSound("sound/ClickSound.mp3");
}

//setting
void StartPause::menuSettingCallback(Ref* pSender)
{
    auto startPauseSettingScene = StartPauseSetting::createScene();
    Director::getInstance()->pushScene(startPauseSettingScene);
    playSound("sound/ClickSound.mp3");
}

//new game
void StartPause::menuNewGameCallback(Ref* pSender)//进入安全屋
{
    auto scene = firstStage::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(0.3, scene, Color3B(255, 255, 255)));
    playSound("sound/ClickSound.mp3");
    //SimpleAudioEngine::getInstance()->stopBackgroundMusic("sound/FightMapBGM.mp3");
}

//continue game
void StartPause::menuContinueGameCallback(cocos2d::Ref* pSender)
{
    doContinueGame = true;
    Director::getInstance()->popScene();////
    playSound("sound/ClickSound.mp3");
}

