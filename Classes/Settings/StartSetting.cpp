#include "Settings/StartSetting.h"
#include "Scene/firstStage.h"
#include "Scene/StartScene2.h"
#include "Settings/SoundAndMusic.h"

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
    auto background1 = Sprite::create("Backgrounds/start2.png");
    background1->setAnchorPoint(Point(0, 0));
    background1->setPosition(Point(0, 0));
    addChild(background1);

    //menu-exit
    //退出按钮
    auto exit = MenuItemImage::create(
        "Buttons/buttonExit.png",
        "Buttons/buttonExitClicked.png", CC_CALLBACK_1(StartSetting::menuCloseCallback, this));
    exit->setPosition(Vec2(100, 80));

    //menu-setting
    //设置按钮
    auto setting = MenuItemImage::create(
        "Buttons/buttonSet.png",
        "Buttons/buttonSetClicked.png", CC_CALLBACK_1(StartSetting::menuSettingCallback, this));
    setting->setPosition(Vec2(100, 200));

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
        soundOnMenuItem = MenuItemImage::create( "Buttons/buttonSoundClicked.png", "Buttons/buttonSoundClicked.png");
        soundOffMenuItem = MenuItemImage::create( "Buttons/buttonSound.png", "Buttons/buttonSound.png");
    }
        auto soundToggleMenuItem = MenuItemToggle::createWithCallback(
            CC_CALLBACK_1(StartSetting::menuSoundToggleCallback, this),
            soundOnMenuItem, soundOffMenuItem, NULL);
        soundToggleMenuItem->setPosition(Vec2(100, 320));

    auto menuSoundIncrease = MenuItemImage::create(
            "Buttons/buttonVolumnIncrease.png",
            "Buttons/buttonVolumnIncreaseClicked.png", CC_CALLBACK_1(StartSetting::menuSoundVolumnIncrease, this));
    menuSoundIncrease->setPosition(Vec2(220, 320));

    auto menuSoundDecrease = MenuItemImage::create(
        "Buttons/buttonVolumnDecrease.png",
        "Buttons/buttonVolumnDecreaseClicked.png", CC_CALLBACK_1(StartSetting::menuSoundVolumnDecrease, this));
    menuSoundDecrease->setPosition(Vec2(340, 320));
    

    //music control
    //音乐按钮
        MenuItemImage* musicOnMenuItem;
        MenuItemImage* musicOffMenuItem;
        if (musicCondition)
        {
            musicOnMenuItem = MenuItemImage::create( "Buttons/buttonMusic.png", "Buttons/buttonMusic.png");
            musicOffMenuItem = MenuItemImage::create( "Buttons/buttonMusicClicked.png", "Buttons/buttonMusicClicked.png");
        }
        else
        {
            musicOnMenuItem = MenuItemImage::create( "Buttons/buttonMusicClicked.png", "Buttons/buttonMusicClicked.png");
            musicOffMenuItem = MenuItemImage::create( "Buttons/buttonMusic.png", "Buttons/buttonMusic.png");
        }

    auto musicToggleMenuItem = MenuItemToggle::createWithCallback(
        CC_CALLBACK_1(StartSetting::menuMusicToggleCallback, this),
        musicOnMenuItem, musicOffMenuItem, NULL);
    musicToggleMenuItem->setPosition(Vec2(100, 440));

    auto menuMusicIncrease = MenuItemImage::create(
        "Buttons/buttonVolumnIncrease.png",
        "Buttons/buttonVolumnIncreaseClicked.png", CC_CALLBACK_1(StartSetting::menuMusicVolumnIncrease, this));
    menuMusicIncrease->setPosition(Vec2(220, 440));

    auto menuMusicDecrease = MenuItemImage::create(
        "Buttons/buttonVolumnDecrease.png",
        "Buttons/buttonVolumnDecreaseClicked.png", CC_CALLBACK_1(StartSetting::menuMusicVolumnDecrease, this));
    menuMusicDecrease->setPosition(Vec2(340, 440));

    //menu-new game
    //新游戏
    auto newGame = MenuItemImage::create(
        "Buttons/buttonNewGame.png",
        "Buttons/buttonNewGameClicked.png", CC_CALLBACK_1(StartSetting::menuNewGameCallback, this));
    newGame->setScale(1.5);
    newGame->setPosition(Vec2(400, 150));

    Menu* startMenu = Menu::create(exit, setting, soundToggleMenuItem, musicToggleMenuItem, newGame,
        menuSoundIncrease, menuSoundDecrease, menuMusicIncrease, menuMusicDecrease,NULL);
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
    //SimpleAudioEngine::getInstance()->stopBackgroundMusic("SafeMapBGM.mp3");
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
    //auto soundToggleMenuItem = (MenuItemToggle*)pSender;
    // log("soundToggleMenuItem %d", soundToggleMenuItem->getSelectedIndex());
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

void StartSetting::menuMusicToggleCallback(Ref* pSender)
{
    //auto musicToggleMenuItem = (MenuItemToggle*)pSender;
    //log("musicToggleMenuItem %d", musicToggleMenuItem->getSelectedIndex());
    //playMusic("sound/FightMapBGM.mp3", true, musicToggleMenuItem->getSelectedIndex());
    if (musicCondition == true)
    {
        playMusic("sound/FightMapBGM.mp3", true, 1);
    }
    else
    {
        playMusic("sound/FightMapBGM.mp3", true, 0);
    }
    playSound("sound/ClickSound.mp3");
}

void StartSetting::menuMusicVolumnIncrease(Ref* pSender)
{
    MusicVolumnIncrease();
    playSound("sound/ClickSound.mp3");
}

void StartSetting::menuMusicVolumnDecrease(Ref* pSender)
{
    MusicVolumnDecrease();
    playSound("sound/ClickSound.mp3");
}

void StartSetting::menuSoundVolumnIncrease(Ref* pSender)
{
    SoundVolumnIncrease();
    playSound("sound/ClickSound.mp3");
}

void StartSetting::menuSoundVolumnDecrease(Ref* pSender)
{
    SoundVolumnDecrease();
    playSound("sound/ClickSound.mp3");
}

//new game
void StartSetting::menuNewGameCallback(Ref* pSender)//进入安全屋
{
    auto scene = firstStage::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(0.3, scene, Color3B(255, 255, 255)));
    playSound("sound/ClickSound.mp3");
    //SimpleAudioEngine::getInstance()->stopBackgroundMusic("sound/FightMapBGM.mp3");
}
