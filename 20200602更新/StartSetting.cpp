#include "StartSetting.h"
#include "firstStage.h"
#include "StartScene2.h"
#include "SoundAndMusic.h"

using namespace CocosDenshion;
USING_NS_CC;

Scene* StartSetting::createScene()
{
    return StartSetting::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in StartScene2.cpp\n");
}

// on "init" you need to initialize your instance
bool StartSetting::init()
{

    if (!Scene::init())
    {
        return false;
    }
    log("StartSetting init");

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //background-start setting
    //设置背景
    auto background1 = Sprite::create("start2.png");
    background1->setAnchorPoint(Point(0, 0));
    background1->setPosition(Point(0, 0));
    addChild(background1);

    //menu-exit
    //退出按钮
    auto exit = MenuItemImage::create(
        "buttonExit.png",
        "buttonExitClicked.png", CC_CALLBACK_1(StartSetting::menuCloseCallback, this));
    exit->setPosition(Vec2(100, 80));

    //menu-setting
    //设置按钮
    auto setting = MenuItemImage::create(
        "buttonSet.png",
        "buttonSetClicked.png", CC_CALLBACK_1(StartSetting::menuSettingCallback, this));
    setting->setPosition(Vec2(100, 200));

    //sound control
    //音效按钮
    auto soundOnMenuItem = MenuItemImage::create(
        "buttonSound.png","buttonSound.png");
    auto soundOffMenuItem = MenuItemImage::create(
        "buttonSoundClicked.png", "buttonSoundClicked.png");

    auto soundToggleMenuItem = MenuItemToggle::createWithCallback(
                               CC_CALLBACK_1(StartSetting::menuSoundToggleCallback,this),
                               soundOnMenuItem,soundOffMenuItem,NULL);
    soundToggleMenuItem->setPosition(Vec2(100,320));

    //music control
    //音乐按钮
    auto musicOnMenuItem = MenuItemImage::create(
        "buttonMusic.png", "buttonMusic.png");
    auto musicOffMenuItem = MenuItemImage::create(
        "buttonMusicClicked.png", "buttonMusicClicked.png");

    auto musicToggleMenuItem = MenuItemToggle::createWithCallback(
        CC_CALLBACK_1(StartSetting::menuMusicToggleCallback, this),
        musicOnMenuItem, musicOffMenuItem, NULL);
    musicToggleMenuItem->setPosition(Vec2(100, 440));

    //menu-new game
    //新游戏
    auto newGame = MenuItemImage::create(
        "buttonNewGame.png",
        "buttonNewGameClicked.png", CC_CALLBACK_1(StartSetting::menuNewGameCallback, this));
    newGame->setScale(1.5);
    newGame->setPosition(Vec2(400, 150));

    Menu* startMenu = Menu::create(exit, setting, soundToggleMenuItem, musicToggleMenuItem, newGame, NULL);
    startMenu->setPosition(Vec2::ZERO);
    this->addChild(startMenu);

    return true;
}

void StartSetting::onEnter()
{
    Scene::onEnter();
    log("Setting onEnter");

}

void StartSetting::onEnterTransitionDidFinish()
{
    Scene::onEnterTransitionDidFinish();
    log("Setting onEnterTransitionDidFinish");
    //playMusic("sound/FightMapBGM.mp3",true);
}

void StartSetting::onExit()
{
    Scene::onExit();
    log("Setting onExit");
}

void StartSetting::onExitTransitionDidStart()
{
    Scene::onExitTransitionDidStart();
    log("Setting onExitTransitionDidStart");
}

void StartSetting::cleanup()
{
    Scene::cleanup();
    log("Setting cleanup");
    //playMusic("sound/FightMapBGM.mp3", true, 1);
    SimpleAudioEngine::getInstance()->stopBackgroundMusic("SafeMapBGM.mp3");
}

//exit
void StartSetting::menuCloseCallback(Ref* pSender)
{
    playSound("sound/ClickSound.mp3");
    Director::getInstance()->end();
}

//setting
void StartSetting::menuSettingCallback(Ref* pSender)
{
    Director::getInstance()->popScene();
    playSound("sound/ClickSound.mp3");
}

void StartSetting::menuSoundToggleCallback(Ref* pSender)
{
    auto soundToggleMenuItem = (MenuItemToggle*)pSender;
    log("soundToggleMenuItem %d", soundToggleMenuItem->getSelectedIndex());
    
    playSound("sound/ClickSound.mp3", soundToggleMenuItem->getSelectedIndex());

}

void StartSetting::menuMusicToggleCallback(Ref* pSender)
{
    auto musicToggleMenuItem = (MenuItemToggle*)pSender;
    log("musicToggleMenuItem %d", musicToggleMenuItem->getSelectedIndex());
    playMusic("sound/FightMapBGM.mp3", true, musicToggleMenuItem->getSelectedIndex());
    playSound("sound/ClickSound.mp3");
}

//new game
void StartSetting::menuNewGameCallback(Ref* pSender)//进入安全屋
{
    auto scene = firstStage::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(0.3, scene, Color3B(255, 255, 255)));
    playSound("sound/ClickSound.mp3");
    SimpleAudioEngine::getInstance()->stopBackgroundMusic("sound/FightMapBGM.mp3");
}
