
//这是安全地图
#pragma once
#ifndef __FIRST_STAGE_H__
#define __FIRST_STAGE_H__

#include"Scene/startScene.h"
#include"cocos2d.h"
#include"Hero/Knight.h"
#include"Constant/Constant.h"
#include"Equipment/Bullet.h"
#include"SimpleAudioEngine.h"
#include"Equipment/Weapon.h"
#include"Scene/Level01.h"

using namespace CocosDenshion;
USING_NS_CC;


class firstStage : public cocos2d::Layer
{
	cocos2d::TMXTiledMap* map;

	cocos2d::TMXLayer* collidable;

	CC_SYNTHESIZE(Knight*, _knight, Knight);//角色--骑士
	CC_SYNTHESIZE(Weapon*, _weapon, Weapon);//武器
	CC_SYNTHESIZE(Bullet*, _bullet, Bullet);//子弹

	CC_SYNTHESIZE(bool, _knightBeenSelected, KnightBeenSelected);//角色骑士是否被选中
	CC_SYNTHESIZE(bool, _inAttackRange, InAttackRange);//判断敌人是否在攻击范围内
public:
	void update(float delta);
	 void knightMove();//骑士角色的移动

	static cocos2d::Scene* createScene();//建立场景
	virtual bool init();//初始化

	virtual void onEnter();//注册监听器
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();//注销监听器
	virtual void onExitTransitionDidStart();
	virtual void cleanup();

	//////////////////////////////////////////////////
	void menuPauseCallback(cocos2d::Ref* pSender);
	//////////////////////////////////////////////////


	bool chooseKnightTouchBegan(Touch* touch, Event* event);//选择英雄-骑士（开始）
	void chooseKnightTouchEnded(Touch* touch, Event* event);//选择英雄-骑士（结束）

	
	bool onTouchBegan(Touch* touch, Event* event);
	void removeFromParent( Node* m);
	
// ///////////////////////////////////////////

	void setPlayerPosition(cocos2d::Point position);

	cocos2d::Point transPoision(cocos2d::Point position);

	void screenRoll(cocos2d::Point position);

// //////////////////////////////////////////

	CREATE_FUNC(firstStage);

private:
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;
};


#endif // __FIRST_STAGE_H__

