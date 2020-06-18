#include "Settings/pauseSetting.h"
#include "Settings/StartPauseScene.h"
#include "Settings/SoundAndMusic.h"
USING_NS_CC;
using namespace CocosDenshion;

Scene* PauseSetting::createScene()
{
	return PauseSetting::create();
}

bool PauseSetting::init()
{
	if (!Scene::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//暂停面板
	auto background1 = Sprite::create("Infos/tablePause.png");
	background1->setAnchorPoint(Point(0.5, 0.5));
	background1->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	addChild(background1);


	//人物头像
	//auto player = setPlayer();
	auto player = Sprite::create("Heroes/knight.png");
	float length = 100;
	auto playerSize = player->getContentSize();
	float scaleSize = length / playerSize.width;
	player->setScale(scaleSize);

	player->setAnchorPoint(Point(0, 0));
	player->setPosition(Point(381, 960 - 409));
	addChild(player);


	//menu-setting
	MenuItemImage* setting = MenuItemImage::create(
		"Buttons/buttonSet.png", "Buttons/buttonSetClicked.png", CC_CALLBACK_1(PauseSetting::menuSettingCallback, this));
	setting->setAnchorPoint(Vec2(0, 0));
	setting->setPosition(Vec2(387, 960 - 636));

	//menu-continue
	MenuItemImage* continueButton = MenuItemImage::create(
		"Buttons/buttonContinue.png", "Buttons/buttonContinueClicked.png", CC_CALLBACK_1(PauseSetting::menuContinueCallback, this));
	continueButton->setAnchorPoint(Vec2(0, 0));
	continueButton->setPosition(Vec2(560, 960 - 636));

	//menu-home
	MenuItemImage* home = MenuItemImage::create(
		"Buttons/buttonHome.png", "Buttons/buttonHomeClicked.png", CC_CALLBACK_1(PauseSetting::menuHomeCallback, this));
	home->setAnchorPoint(Vec2(0, 0));
	home->setPosition(Vec2(789, 960 - 636));

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

	auto soundToggleMenuItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(PauseSetting::menuSoundToggleCallback, this),
																			soundOnMenuItem, soundOffMenuItem, NULL);
	soundToggleMenuItem->setAnchorPoint(Vec2(0, 0));
	soundToggleMenuItem->setPosition(Vec2(58,50));

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

	auto musicToggleMenuItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(PauseSetting::menuMusicToggleCallback, this),
																	musicOnMenuItem, musicOffMenuItem, NULL);
	musicToggleMenuItem->setAnchorPoint(Vec2(0, 0));
	musicToggleMenuItem->setPosition(Vec2(217,50));


	Menu* menu = Menu::create(setting, continueButton, home, soundToggleMenuItem, musicToggleMenuItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);
	return true;
}

void PauseSetting::onEnter()
{
	Scene::onEnter();
	log("PauseControl onEnter");
}

void PauseSetting::onEnterTransitionDidFinish()
{
	Scene::onEnterTransitionDidFinish();
	log("PauseControl onEnterTransitionDidFinish");
	if (doContinueGame == true)
	{
		doContinueGame = false;
		Director::getInstance()->popScene();
		playSound("sound/ClickSound.mp3");
	}
}

void PauseSetting::onExit()
{
	Scene::onExit();
	log("PauseControl onExit");
}

void PauseSetting::onExitTransitionDidStart()
{
	Scene::onExitTransitionDidStart();
	log("PauseControl onExitTransitionDidStart");
}

void PauseSetting::cleanup()
{
	Scene::cleanup();
	log("PauseControl cleanup");
	
}

void PauseSetting::menuSettingCallback(cocos2d::Ref* pSender)
{
	Director::getInstance()->popScene();
	playSound("sound/ClickSound.mp3");
}

void PauseSetting::menuContinueCallback(cocos2d::Ref* pSender)
{
	doContinueGame = true;
	Director::getInstance()->popScene();
	playSound("sound/ClickSound.mp3");
}

void PauseSetting::menuHomeCallback(cocos2d::Ref* pSender)
{
	auto startPauseScene = StartPause::createScene();
	Director::getInstance()->pushScene(startPauseScene);
	playSound("sound/ClickSound.mp3");
}

void PauseSetting::menuSoundToggleCallback(cocos2d::Ref* pSender)
{
	//auto soundToggleMenuItem = (MenuItemToggle*)pSender;
	//log("soundToggleMenuItem %d", soundToggleMenuItem->getSelectedIndex());
	if (soundCondition == true)
	{
		musicCondition = false;
		SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
		//playSound("sound/ClickSound.mp3", 1);
	}
	else
	{
		musicCondition = true;
		SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
		//playSound("sound/ClickSound.mp3", 0);
	}
	//playSound("sound/ClickSound.mp3", soundToggleMenuItem->getSelectedIndex());

}

void PauseSetting::menuMusicToggleCallback(cocos2d::Ref* pSender)
{
	//auto musicToggleMenuItem = (MenuItemToggle*)pSender;
	//log("musicToggleMenuItem %d", musicToggleMenuItem->getSelectedIndex());
	//playMusic("sound/SafeMapBGM.mp3", true, musicToggleMenuItem->getSelectedIndex());
	if (musicCondition == true)
	{
		playMusic("sound/SafeMapBGM.mp3",true, 1);
	}
	else
	{
		playMusic("sound/SafeMapBGM.mp3",true, 0);
	}
	playSound("sound/ClickSound.mp3");
}