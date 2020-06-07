
//这是安全地图
#pragma once
#ifndef __FIRST_STAGE_H__
#define __FIRST_STAGE_H__

#include"Scene/startScene.h"
#include"cocos2d.h"
#include"Hero/Knight.h"
#include"Constant/Constant.h"
#include"Equipment/Bullet.h"


//测试：
#include"Actor/Creep.h"

USING_NS_CC;

class firstStage : public cocos2d::Layer
{
	CC_SYNTHESIZE(bool, _knightBeenSelected, KnightBeenSelected);//角色骑士是否被选中
	CC_SYNTHESIZE(bool, _inAttackRange, InAttackRange);//判断敌人是否在攻击范围内
public:
	void update(float delta);

	static cocos2d::Scene* createScene();//建立场景
	virtual bool init();//初始化

	virtual void onEnter();//注册监听器
	virtual void onExit();//注销监听器
	bool chooseKnightTouchBegan(Touch* touch, Event* event);//选择英雄-骑士（开始）
	void chooseKnightTouchEnded(Touch* touch, Event* event);//选择英雄-骑士（结束）

	
	//bool shootTouchBegan(Touch* touch, Event* event);//射击（鼠标开始点击）
	//void shootTouchEnded(Touch* touch, Event* event);//射击（鼠标结束点击）
	bool onTouchBegan(Touch* touch, Event* event);
	void removeFromParent( Node* m);
	
	

	CREATE_FUNC(firstStage);

private:
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;
};


#endif // __FIRST_STAGE_H__

