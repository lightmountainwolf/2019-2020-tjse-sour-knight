#pragma once
#include "cocos2d.h"
#include"SimpleAudioEngine.h"
#ifndef __PAUSE_SETTING_SCENE_H__
#define __PAUSE_SETTING_SCENE_H__


class PauseSetting : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();
	virtual void cleanup();

	void menuSettingCallback(cocos2d::Ref* pSender);

	void menuContinueCallback(cocos2d::Ref* pSender);

	void menuHomeCallback(cocos2d::Ref* pSender);

	//control sound
	void menuSoundToggleCallback(cocos2d::Ref* pSender);

	//control music
	void menuMusicToggleCallback(cocos2d::Ref* pSender);

	CREATE_FUNC(PauseSetting);
};

//Sprite* setPlayer(const char* hero);

#endif // __PAUSE_SETTING_SCENE_H__

