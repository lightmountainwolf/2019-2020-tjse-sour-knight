#pragma once


#ifndef __HELLOWORLDF4_SCENE_H__

#define __HELLOWORLDF4_SCENE_H__

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

class Level04 : public cocos2d::Layer

{
	cocos2d::TMXTiledMap* map;

	cocos2d::TMXLayer* collidable;

	cocos2d::Sprite* smallMap;

	cocos2d::Sprite* smallK;

	void bossMoveUpdate(float delta);//敌人boss的移动
	void bossAttackUpdate(float dt);
	cocos2d::Vector<Creep*>bossVec;//boss

	CC_SYNTHESIZE(Knight*, _knight, Knight);//角色--骑士
	CC_SYNTHESIZE(Weapon*, _weapon, Weapon);//武器
	CC_SYNTHESIZE(Bullet*, _bullet, Bullet);//子弹
	CC_SYNTHESIZE(std::string, knightFilename, KnightFilename);//骑士的文件名
	CC_SYNTHESIZE(std::string, weaponFilename, WeaponFilename);//武器的文件名
	CC_SYNTHESIZE(std::string, bulletFilename, BulletFilename);//子弹的文件名
	CC_SYNTHESIZE(bool, _knightBeenSelected, KnightBeenSelected);//角色骑士是否被选中
	CC_SYNTHESIZE(bool, _inAttackRange, InAttackRange);//判断敌人是否在攻击范围内

// ///////////////////////////////////////////////////////
public:
	//update相关函数
	void update(float delta);
	void enemyMoveUpdate(float delta);//敌人的移动
	void enemyAttackUpdate(float dt);//敌人的攻击
	void armorRecoverUpdate(float dt);//护甲的恢复
	void heroDieUpdate(float dt);//英雄角色的死亡与场景的切换
	void groundAttackUpdate(float dt);//地刺
	void returnColor(float dt);
	Color3B colorKnight;
	//人物动作相关函数
	void knightMove();//骑士角色的移动
	void creepMove();//小怪的移动
	void creepDie(Creep* creep);//小怪的死亡
	void createMonster(char arr[5][4], const std::string& location, int num);//小怪的创建
	void attackMelee(Hero* hero);//无目标时近战攻击
	bool attackTowardsTarget(Hero* hero);//有目标时近战攻击
	void attackRemotely(Vec2 vec, Hero* hero);//远程攻击

	void setPlayerPosition(cocos2d::Point position);
	cocos2d::Point transPoision(cocos2d::Point position);
	void screenRoll(cocos2d::Point position);

	//初始化相关函数
	static cocos2d::Scene* createScene();//建立场景
	virtual bool init();//初始化
	void initWeapon();//初始化

	virtual void onEnter();//注册监听器
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();//注销监听器
	virtual void onExitTransitionDidStart();
	virtual void cleanup();
	//商店相关函数
	void initShop();
	void buyProps();
	//道具相关函数
	void collectProps();
	void initProps();

	void menuPauseCallback(cocos2d::Ref* pSender);
	bool onTouchBegan(Touch* touch, Event* event);
	void removeFromParent(Node* m);
	//切换到下一关
	void nextScene();

	CREATE_FUNC(Level04);
	cocos2d::Vector<Weapon*>weaponVec;//武器库--武器
	cocos2d::Vector<Bullet*>bulletVec;//武器库--子弹
private:
	int buyTimes;
	Vector<Props*>propsOnSaleVec;//商店道具数组
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;//按键容器
	cocos2d::Vector<Creep*> creepsVec;//小怪容器
	cocos2d::Vector<EventListener*>listenerVec;//监听器容器
	Vector<Props*>propsVec;//道具数组


	bool creepDieArr[15];//怪物是否存活
	int littleMapClear[4];//小关内怪物死去的数量
	int littleMapWave[4];//小关是否清理完毕
	int deadCreeps;//死掉的怪物数量
	bool allClear;//大关全灭
};
#endif // __HELLOWORLD4_SCENE_H__
