#pragma once

#ifndef __HELLOWORLDF2_SCENE_H__

#define __HELLOWORLDF2_SCENE_H__

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
#include"Actor/Creep.h"
#include"Scene/DeadScene.h"


using namespace CocosDenshion;
USING_NS_CC;

class Level02 : public cocos2d::Layer

{
	cocos2d::TMXTiledMap* map;

	cocos2d::TMXLayer* collidable;

	CC_SYNTHESIZE(Knight*, _knight, Knight);//角色--骑士
	CC_SYNTHESIZE(Weapon*, _weapon, Weapon);//武器
	CC_SYNTHESIZE(Bullet*, _bullet, Bullet);//子弹
	CC_SYNTHESIZE(bool, _knightBeenSelected, KnightBeenSelected);//角色骑士是否被选中
	CC_SYNTHESIZE(bool, _inAttackRange, InAttackRange);//判断敌人是否在攻击范围内
// //////////////////////////////////////////////////////////
	//CC_SYNTHESIZE(bool, _beenAttacked, BeenAttacked);//判断是否被攻击
// ///////////////////////////////////////////////////////
public:
	//update相关函数
	void update(float delta);
	void enemyMoveUpdate(float delta);//敌人的移动
	void enemyAttackUpdate(float dt);//敌人的攻击
	void armorRecoverUpdate(float dt);//护甲的恢复
	void heroDieUpdate(float dt);//英雄角色的死亡与场景的切换

	//人物动作相关函数
	void knightMove();//骑士角色的移动
	void creepMove();//小怪的移动
	void creepDie(Creep* creep);//小怪的死亡
	void createMonster(char arr[5][4], const std::string& location, int num);//小怪的创建
	void attackRandomly(Bullet* bullet);//无目标时攻击
	bool attackTawordsTarget(Bullet* bullet);//有目标时攻击

	void setPlayerPosition(cocos2d::Point position);
	cocos2d::Point transPoision(cocos2d::Point position);
	void screenRoll(cocos2d::Point position);

	//初始化相关函数
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


	CREATE_FUNC(Level02);

private:
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;//按键容器
	cocos2d::Vector<Creep*> creepsVec;//小怪容器
	cocos2d::Vector<EventListener*>listenerVec;//监听器容器
	bool creepDieArr[15];//怪物是否存活
	int littleMapClear[3];//小关内怪物死去的数量
	int littleMapWave[3];//小关是否清理完毕

};
#endif // __HELLOWORLD2_SCENE_H__

