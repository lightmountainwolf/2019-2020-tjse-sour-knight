
//这是安全地图
#pragma once
#ifndef __FIRST_STAGE_H__
#define __FIRST_STAGE_H__

#include"StartScene.h"
#include"cocos2d.h"


class firstStage : public cocos2d::Scene

{
public:

	
	void firstStage::update(float delta);

	static cocos2d::Scene* createScene();

	virtual bool init();


	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	//setting
	void menuSettingCallback(cocos2d::Ref* pSender);

	//new game
	void menuNewGameCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(firstStage);
	

	
private:
	
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;
};


#endif // __FIRST_STAGE_H__

