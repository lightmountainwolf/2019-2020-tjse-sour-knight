#include "Settings/StartPauseScene.h"
#include "Scene/firstStage.h"
#include "Settings/StartPauseSettingScene.h"

using namespace CocosDenshion;
USING_NS_CC;

Scene* StartPauseSetting::createScene()
{
    return StartPauseSetting::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in StartPause.cpp\n");
}

// on "init" you need to initialize your instance
bool StartPauseSetting::init()
{
    if (!Scene::init())
    {
        return false;
    }

    log("StartPauseSetting init");

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //background-start2
    auto background1 = Sprite::create("Backgrounds/start2.png");
    background1->setAnchorPoint(Point(0, 0));
    background1->setPosition(Point(0, 0));
    addChild(background1);

    //menu-exit
    MenuItemImage* exit = MenuItemImage::create(
        "Buttons/buttonExit.png", "Buttons/buttonExitClicked.png", CC_CALLBACK_1(StartPauseSetting::menuCloseCallback, this));
    exit->setPosition(Vec2(100, 80));

    //menu-setting
    MenuItemImage* setting = MenuItemImage::create(
        "Buttons/buttonSet.png", "Buttons/buttonSetClicked.png", CC_CALLBACK_1(StartPauseSetting::menuSettingCallback, this));
    setting->setPosition(Vec2(100, 200));

    //menu-new game
    MenuItemImage* newGame = MenuItemImage::create(
        "Buttons/buttonNewGame.png", "Buttons/buttonNewGameClicked.png", CC_CALLBACK_1(StartPauseSetting::menuNewGameCallback, this));
    newGame->setPosition(Vec2(500, 150));

    //menu-continue game
    MenuItemImage* continueGame = MenuItemImage::create(
        "Buttons/buttonContinueGame.png", "Buttons/buttonContinueGameClicked.png", CC_CALLBACK_1(StartPauseSetting::menuContinueGameCallback, this));
    continueGame->setPosition(Vec2(500, 300));

    //sound control
    //音效按钮
    MenuItemImage* soundOnMenuItem;
    MenuItemImage* soundOffMenuItem;
    if (soundCondition)
    {
        soundOnMenuItem = MenuItemImage::create("Buttons/buttonSound.png", "Buttons/buttonSound.png");
        soundOffMenuItem = MenuItemImage::create("Buttons/buttonSoundClicked.png", "Buttons/buttonSoundClicked.png");
    }
    else
    {
        soundOnMenuItem = MenuItemImage::create("Buttons/buttonSoundClicked.png", "Buttons/buttonSoundClicked.png");
        soundOffMenuItem = MenuItemImage::create("Buttons/buttonSound.png", "Buttons/buttonSound.png");
    }
    auto soundToggleMenuItem = MenuItemToggle::createWithCallback(
        CC_CALLBACK_1(StartPauseSetting::menuSoundToggleCallback, this),
        soundOnMenuItem, soundOffMenuItem, NULL);
    soundToggleMenuItem->setPosition(Vec2(100, 320));

    auto menuSoundIncrease = MenuItemImage::create(
        "Buttons/buttonVolumnIncrease.png",
        "Buttons/buttonVolumnIncreaseClicked.png", CC_CALLBACK_1(StartPauseSetting::menuSoundVolumnIncrease, this));
    menuSoundIncrease->setPosition(Vec2(220, 320));

    auto menuSoundDecrease = MenuItemImage::create(
        "Buttons/buttonVolumnDecrease.png",
        "Buttons/buttonVolumnDecreaseClicked.png", CC_CALLBACK_1(StartPauseSetting::menuSoundVolumnDecrease, this));
    menuSoundDecrease->setPosition(Vec2(340, 320));

    //music control
    //音乐按钮
    MenuItemImage* musicOnMenuItem;
    MenuItemImage* musicOffMenuItem;
    if (musicCondition)
    {
        musicOnMenuItem = MenuItemImage::create("Buttons/buttonMusic.png", "Buttons/buttonMusic.png");
        musicOffMenuItem = MenuItemImage::create("Buttons/buttonMusicClicked.png", "Buttons/buttonMusicClicked.png");
    }
    else
    {
        musicOnMenuItem = MenuItemImage::create("Buttons/buttonMusicClicked.png", "Buttons/buttonMusicClicked.png");
        musicOffMenuItem = MenuItemImage::create("Buttons/buttonMusic.png", "Buttons/buttonMusic.png");
    }
    auto musicToggleMenuItem = MenuItemToggle::createWithCallback(
        CC_CALLBACK_1(StartPauseSetting::menuMusicToggleCallback, this),
        musicOnMenuItem, musicOffMenuItem, NULL);
    musicToggleMenuItem->setPosition(Vec2(100, 440));

    auto menuMusicIncrease = MenuItemImage::create(
        "Buttons/buttonVolumnIncrease.png",
        "Buttons/buttonVolumnIncreaseClicked.png", CC_CALLBACK_1(StartPauseSetting::menuMusicVolumnIncrease, this));
    menuMusicIncrease->setPosition(Vec2(220, 440));

    auto menuMusicDecrease = MenuItemImage::create(
        "Buttons/buttonVolumnDecrease.png",
        "Buttons/buttonVolumnDecreaseClicked.png", CC_CALLBACK_1(StartPauseSetting::menuMusicVolumnDecrease, this));
    menuMusicDecrease->setPosition(Vec2(340, 440));

    Menu* menu = Menu::create(exit, setting, newGame, continueGame,soundToggleMenuItem,musicToggleMenuItem, 
        menuSoundIncrease, menuSoundDecrease, menuMusicIncrease, menuMusicDecrease, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);

    return true;
}

void StartPauseSetting::onEnter()
{
    Scene::onEnter();
    log("StartPause onEnter");
}

void StartPauseSetting::onEnterTransitionDidFinish()
{
    Scene::onEnterTransitionDidFinish();
    log("StartPause onEnterTransitionDidFinish");
    ////playMusic("sound/FightMapBGM.mp3", true);
}

void StartPauseSetting::onExit()
{
    Scene::onExit();
    log("StartPause onExit");
}

void StartPauseSetting::onExitTransitionDidStart()
{
    Scene::onExitTransitionDidStart();
    log("StartPause onExitTransitionDidStart");
}

void StartPauseSetting::cleanup()
{
    Scene::cleanup();
    log("StartPause cleanup");
}

//exit
void StartPauseSetting::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
    playSound("sound/ClickSound.mp3");
}

//setting
void StartPauseSetting::menuSettingCallback(Ref* pSender)
{
    Director::getInstance()->popScene();
    playSound("sound/ClickSound.mp3");
}

//new game
void StartPauseSetting::menuNewGameCallback(Ref* pSender)//进入安全屋
{
    auto scene = firstStage::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(0.3, scene, Color3B(255, 255, 255)));
    playSound("sound/ClickSound.mp3");
    //SimpleAudioEngine::getInstance()->stopBackgroundMusic("sound/FightMapBGM.mp3");
}

//continue game
void StartPauseSetting::menuContinueGameCallback(cocos2d::Ref* pSender)
{
    doContinueGame = true;
    Director::getInstance()->popScene();////
    playSound("sound/ClickSound.mp3");
}

void StartPauseSetting::menuSoundToggleCallback(cocos2d::Ref* pSender)
{
    //auto soundToggleMenuItem = (MenuItemToggle*)pSender;
    //log("soundToggleMenuItem %d", soundToggleMenuItem->getSelectedIndex());
    if (soundCondition == true)
    {
        playSound("sound/ClickSound.mp3", 1);
    }
    else
    {
        playSound("sound/ClickSound.mp3", 0);
    }
    //playSound("sound/ClickSound.mp3", soundToggleMenuItem->getSelectedIndex());
}

void StartPauseSetting::menuMusicToggleCallback(cocos2d::Ref* pSender)
{
    //auto musicToggleMenuItem = (MenuItemToggle*)pSender;
    //log("musicToggleMenuItem %d", musicToggleMenuItem->getSelectedIndex());
    //playMusic("sound/FightMapBGM.mp3", true, musicToggleMenuItem->getSelectedIndex());
    if (musicCondition == true)
    {
        playMusic("sound/FightMapBGM.mp3",true, 1);
    }
    else
    {
        playMusic("sound/FightSound.mp3",true, 0);
    }
    playSound("sound/ClickSound.mp3");
}

void StartPauseSetting::menuMusicVolumnIncrease(Ref* pSender)
{
    MusicVolumnIncrease();
    playSound("sound/ClickSound.mp3");
}

void StartPauseSetting::menuMusicVolumnDecrease(Ref* pSender)
{
    MusicVolumnDecrease();
    playSound("sound/ClickSound.mp3");
}

void StartPauseSetting::menuSoundVolumnIncrease(Ref* pSender)
{
    SoundVolumnIncrease();
    playSound("sound/ClickSound.mp3");
}

void StartPauseSetting::menuSoundVolumnDecrease(Ref* pSender)
{
    SoundVolumnDecrease();
    playSound("sound/ClickSound.mp3");
}

