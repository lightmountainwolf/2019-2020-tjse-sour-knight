#include "StartScene2.h"

USING_NS_CC;

Scene* Start2::createScene()
{
    return Start2::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in StartScene2.cpp\n");
}

// on "init" you need to initialize your instance
bool Start2::init()
{

    if (!Scene::init())
    {
        return false;
    }

    log("Start2 init");

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //bagrount-start2
    auto background1 = Sprite::create("start2.png");
    background1->setAnchorPoint(Point(0, 0));
    background1->setPosition(Point(0, 0));
    addChild(background1);

    //menu-exit
    MenuItemImage* exit = MenuItemImage::create(
        "buttonExit.png",
        "buttonExitClicked.png", CC_CALLBACK_1(Start2::menuCloseCallback, this));
    exit->setPosition(Vec2(100, 80));

    //menu-setting
    MenuItemImage* setting = MenuItemImage::create(
        "buttonSet.png",
        "buttonSetClicked.png", CC_CALLBACK_1(Start2::menuSettingCallback, this));
    setting->setPosition(Vec2(100, 200));

    //menu-new game
    MenuItemImage* newGame = MenuItemImage::create(
        "buttonNewGame.png",
        "buttonNewGameClicked.png", CC_CALLBACK_1(Start2::menuNewGameCallback, this));
    newGame->setScale(1.5);
    newGame->setPosition(Vec2(400, 150));

    Menu* startMenu = Menu::create(exit,setting,newGame, NULL);
    startMenu->setPosition(Vec2::ZERO);
    this->addChild(startMenu);

    return true;
}

void Start2::onEnter()
{
    Scene::onEnter();
    log("Start2 onEnter");
}

void Start2::onEnterTransitionDidFinish()
{
    Scene::onEnterTransitionDidFinish();
    log("Start2 onEnterTransitionDidFinish");
    playMusic("sound/FightMapBGM.mp3", true);
}

void Start2::onExit()
{
    Scene::onExit();
    log("start2 onExit");
}

void Start2::onExitTransitionDidStart()
{
    Scene::onExitTransitionDidStart();
    log("Start2 onExitTransitionDidStart");
}

void Start2::cleanup()
{
    Scene::cleanup();
    log("Start2 cleanup");
    playMusic("sound/FightMapBGM.mp3", true,1);
}

//exit
void Start2::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
    playSound("sound/ClickSound.mp3");
}

//setting
void Start2::menuSettingCallback(Ref* pSender)
{
    auto sc = StartSetting::createScene();
    Director::getInstance()->pushScene(sc);
    playSound("sound/ClickSound.mp3");
}

//new game
void Start2::menuNewGameCallback(Ref* pSender)//进入安全屋
{
	auto scene = firstStage::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(0.3, scene, Color3B(255, 255, 255)));
    playSound("sound/ClickSound.mp3");
}
