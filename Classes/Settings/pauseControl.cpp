#include "Settings/pauseControl.h"
#include "Settings/PauseSetting.h"
#include "Settings/StartPauseScene.h"
#include "Settings/SoundAndMusic.h"
USING_NS_CC;

Scene* Pause::createScene()
{
	return Pause::create();
}

bool Pause::init()
{
	if (!Scene::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//暂停面板
	auto background1 = Sprite::create("Infos/tablePause.png");
	background1->setAnchorPoint(Point(0.5,0.5));
	background1->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
	addChild(background1);


	//人物头像
	//auto player = setPlayer();
	//!!!!在将来设计多个英雄的时候还应进行修改
	auto player = Sprite::create("Heroes/knight.png");
	float length = 100;
	auto playerSize = player->getContentSize();
	float scaleSize = length / playerSize.width;
	player->setScale(scaleSize);

	player->setAnchorPoint(Point(0,0));
	player->setPosition(Point(381, 960 - 409));
	addChild(player);


	//menu-setting
	MenuItemImage* setting = MenuItemImage::create(
		"Buttons/buttonSet.png","Buttons/buttonSetClicked.png", CC_CALLBACK_1(Pause::menuSettingCallback, this));
	setting->setAnchorPoint(Vec2(0, 0));
	setting->setPosition(Vec2(387, 960-636));

	//menu-continue
	MenuItemImage* continueButton = MenuItemImage::create(
		"Buttons/buttonContinue.png", "Buttons/buttonContinueClicked.png", CC_CALLBACK_1(Pause::menuContinueCallback, this));
	continueButton->setAnchorPoint(Vec2(0, 0));
	continueButton->setPosition(Vec2(560, 960 - 636));

	//menu-home
	MenuItemImage* home = MenuItemImage::create(
		"Buttons/buttonHome.png", "Buttons/buttonHomeClicked.png", CC_CALLBACK_1(Pause::menuHomeCallback, this));
	home->setAnchorPoint(Vec2(0, 0));
	home->setPosition(Vec2(789, 960 - 636));

	/*//sound control
	//音效按钮
	//bug 没有更新当前状态的图片！
	//bug 没有按setting的时候只是隐藏状态
	auto soundOnMenuItem = MenuItemImage::create("buttonSound.png", "buttonSound.png");
	auto soundOffMenuItem = MenuItemImage::create("buttonSoundClicked.png", "buttonSoundClicked.png");
	auto soundToggleMenuItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(Pause::menuSoundToggleCallback, this),
		                                                                    soundOnMenuItem, soundOffMenuItem, NULL);
	soundToggleMenuItem->setOpacity(0);
	soundToggleMenuItem->setAnchorPoint(Vec2(0, 0));
	soundToggleMenuItem->setPosition(Vec2(58,50));

	//music control
	//音乐按钮
	//bug 没有更新当前状态的图片！
	//bug 没有按setting的时候只是隐藏状态
	auto musicOnMenuItem = MenuItemImage::create("buttonMusic.png", "buttonMusic.png");
	auto musicOffMenuItem = MenuItemImage::create("buttonMusicClicked.png", "buttonMusicClicked.png");
	auto musicToggleMenuItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(Pause::menuMusicToggleCallback, this),
		                                                            musicOnMenuItem, musicOffMenuItem, NULL);
	musicToggleMenuItem->setOpacity(0);
	musicToggleMenuItem->setAnchorPoint(Vec2(0, 0));
	musicToggleMenuItem->setPosition(Vec2(217,50));*/


	Menu* menu = Menu::create(setting,continueButton,home, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);
	return true;
}

void Pause::onEnter()
{
	Scene::onEnter();
	log("PauseControl onEnter");
}

void Pause::onEnterTransitionDidFinish()
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

void Pause::onExit()
{
	Scene::onExit();
	log("PauseControl onExit");
}

void Pause::onExitTransitionDidStart()
{
	Scene::onExitTransitionDidStart();
	log("PauseControl onExitTransitionDidStart");
}

void Pause::cleanup()
{
	Scene::cleanup();
	log("PauseControl cleanup");
}

void Pause::menuSettingCallback(cocos2d::Ref* pSender)
{
	auto PauseSettingScene = PauseSetting::createScene();
	Director::getInstance()->pushScene(PauseSettingScene);
	playSound("sound/ClickSound.mp3");
}

void Pause::menuContinueCallback(cocos2d::Ref* pSender)
{
	Director::getInstance()->popScene();
	playSound("sound/ClickSound.mp3");
}

void Pause::menuHomeCallback(cocos2d::Ref* pSender)
{
	auto startPauseScene = StartPause::createScene();
	Director::getInstance()->pushScene(startPauseScene);
	playSound("sound/ClickSound.mp3");
}