#include "Scene/StartScene.h"
using namespace CocosDenshion;
USING_NS_CC;

Scene* Start::createScene()
{
    return Start::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in StartScene.cpp\n");
}

// on "init" you need to initialize your instance
bool Start::init()
{

    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //bagrount-start1
    auto background1 = Sprite::create("Backgrounds/start1.png");
    background1->setAnchorPoint(Point(0, 0));
    background1->setPosition(Point(0, 0));
    //background1->setScale(0.8);
    addChild(background1);

    //menu-clickToStart
    MenuItemImage* startMenuItem = MenuItemImage::create(
                                               "Buttons/clickToStart.png",
                                                "Buttons/clickToStart2.png", CC_CALLBACK_1(Start::menuItem1Callback, this));
    float x = origin.x + visibleSize.width/2;
    float y = origin.y + 120;
    startMenuItem->setPosition(Vec2(x, y));

    //menu-exit
    MenuItemImage* exit = MenuItemImage::create(
        "Buttons/buttonExit.png",
        "Buttons/buttonExitClicked.png", CC_CALLBACK_1(Start::menuCloseCallback, this));
    //exit->setScale(0.6);
    exit->setPosition(Vec2(100,80));

    Menu* startMenu = Menu::create(startMenuItem,exit,NULL);
    startMenu->setPosition(Vec2::ZERO);
    this->addChild(startMenu);

    return true;
}

void Start::onEnter()
{
    Scene::onEnter();
}

void Start::onEnterTransitionDidFinish()
{
    Scene::onEnterTransitionDidFinish();
    SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/FightMapBGM.mp3", true);
}

void Start::onExit()
{
    Scene::onExit();
    log("start2 onExit");
}

void Start::onExitTransitionDidStart()
{
    Scene::onExitTransitionDidStart();
    log("Start2 onExitTransitionDidStart");
}

void Start::cleanup()
{
    Scene::cleanup();
    log("Start2 cleanup");
    //SimpleAudioEngine::getInstance()->stopBackgroundMusic("sound/FightMapBGM.mp3");
}

//exit
void Start::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
    SimpleAudioEngine::getInstance()->playEffect("sound/ClickSound.mp3");
}

//click to start
void Start::menuItem1Callback(Ref* pSender)//进入第二个初始界面
{
    auto scene = Start2::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(0.3, scene, Color3B(255, 255, 255)));
    SimpleAudioEngine::getInstance()->playEffect("sound/ClickSound.mp3");
}
