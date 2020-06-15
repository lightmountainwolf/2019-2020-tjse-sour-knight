#pragma once
 
#ifndef __HELLOWORLDF_SCENE_H__

#define __HELLOWORLDF_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include"Scene/firstStage.h"
#include "Hero/Knight.h"
#include"Constant/Constant.h"
#include "Equipment/Bullet.h"
#include"Equipment/Weapon.h"
#include"Settings/SoundAndMusic.h"
#include"Settings/pauseControl.h"
#include"Settings/CreateDoor.h"
#include"Function/CommonFunction.h"



using namespace CocosDenshion;
USING_NS_CC;

class Level01 : public cocos2d::Layer

{
	

	cocos2d::TMXTiledMap* map;										

	cocos2d::TMXLayer* collidable;

	CC_SYNTHESIZE(Knight*, _knight, Knight);//角色--骑士
	CC_SYNTHESIZE(Weapon*, _weapon, Weapon);//武器
	CC_SYNTHESIZE(Bullet*, _bullet, Bullet);//子弹
	CC_SYNTHESIZE(bool, _knightBeenSelected, KnightBeenSelected);//角色骑士是否被选中
	CC_SYNTHESIZE(bool, _inAttackRange, InAttackRange);//判断敌人是否在攻击范围内

public:
	cocos2d::Vector<cocos2d::Sprite*> creepsVec;

	void update(float delta);
	void myUpData1(float delta);
	void knightMove();//骑士角色的移动
	void creepMove();

	static cocos2d::Scene* createScene();//建立场景
	virtual bool init();//初始化
	

	virtual void onEnter();//注册监听器
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();//注销监听器
	virtual void onExitTransitionDidStart();
	virtual void cleanup();

	void menuPauseCallback(cocos2d::Ref* pSender);

	bool onTouchBegan(Touch* touch, Event* event);
	void removeFromParent(Node* m);


	void setPlayerPosition(cocos2d::Point position);								

	cocos2d::Point transPoision(cocos2d::Point position);					

	void screenRoll(cocos2d::Point position);

	CREATE_FUNC(Level01);

 private:
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;

	
};
#endif // __HELLOWORLD_SCENE_H__
