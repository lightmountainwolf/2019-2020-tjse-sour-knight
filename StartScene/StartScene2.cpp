#include "SimpleAudioEngine.h"
#include "StartScene2.h"
#include "mapScene.h"


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

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //bagrount-start2
    auto background1 = Sprite::create("start2.png");
    background1->setAnchorPoint(Point(0, 0));
    background1->setPosition(Point(0, 0));
    //background1->setScale(0.8);
    addChild(background1);

    //menu-exit
    MenuItemImage* exit = MenuItemImage::create(
        "buttonExit.png",
        "buttonExitClicked.png", CC_CALLBACK_1(Start2::menuCloseCallback, this));
    //exit->setScale(0.6);
    exit->setPosition(Vec2(100, 80));

    //menu-setting
    MenuItemImage* setting = MenuItemImage::create(
        "buttonSet.png",
        "buttonSetClicked.png", CC_CALLBACK_1(Start2::menuSettingCallback, this));
    //setting->setScale(0.6);
    setting->setPosition(Vec2(100, 200));

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

//exit
void Start2::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

}

//setting
void Start2::menuSettingCallback(Ref* pSender)
{
    ///////////////////////////////////////////////»¹Ã»ÓÐÐ´£¡£¡£¡£¡
}

//new game
void Start2::menuNewGameCallback(Ref* pSender)
{
    auto scene = Map1::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene, Color3B(255, 255, 255)));
}