#pragma once
#include "cocos2d.h"

//void setPauseButton(MenuItemImage * menu,int x,int y,int length,Ref *pSender);

#ifndef __PAUSE_SCENE_H__
#define __PAUSE_SCENE_H__


class Pause : public cocos2d::Scene
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

	//void menuSoundToggleCallback(cocos2d::Ref* pSender);

	//void menuMusicToggleCallback(cocos2d::Ref* pSender);

	CREATE_FUNC(Pause);
};

//Sprite* setPlayer(const char* hero);

#endif // __PAUSE_SCENE_H__

