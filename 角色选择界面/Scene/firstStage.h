
//这是安全地图
#pragma once
#ifndef __FIRST_STAGE_H__
#define __FIRST_STAGE_H__

#include"Scene/startScene.h"
#include"cocos2d.h"
#include"Hero/Knight.h"
#include"Constant/Constant.h"

USING_NS_CC;

class firstStage : public cocos2d::Scene
{
	CC_SYNTHESIZE(bool, _knightBeenSelected, KnightBeenSelected);
public:
	void update(float delta);

	static cocos2d::Scene* createScene();
	virtual bool init();

	virtual void onEnter();
	virtual void onExit();
	bool touchBegan(Touch* touch, Event* event);
	void touchEnded(Touch* touch, Event* event);

	CREATE_FUNC(firstStage);

private:
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;
};


#endif // __FIRST_STAGE_H__

