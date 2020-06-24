#pragma once
#ifndef  HERO_H_
#define HERO_H_

#include<iostream>
#include"cocos2d.h"
#include "Constant/constant.h"
#include"Equipment/weapon.h"
#include "Actor.h"

USING_NS_CC;

class Hero :public Actor
{
	CC_SYNTHESIZE(int, _armor, Armor);//护甲
	CC_SYNTHESIZE(int, _MP, MP);//蓝条（能量）
	CC_SYNTHESIZE(int, _MPConsuming, MPConsuming);//每一次攻击消耗的能量值
	CC_SYNTHESIZE(int, _maxArmor, MaxArmor);//护甲最大值
	CC_SYNTHESIZE(int, _maxMP, MaxMP);//MP最大值
	CC_SYNTHESIZE(float, _skillPoint, SkillPoint);//当前的技能点
	CC_SYNTHESIZE(float, _maxSkillPoint, MaxSkillPoint);//最大的技能点
	CC_SYNTHESIZE(int, _levelNum, LevelNum);//最大关卡
	CC_SYNTHESIZE(int, _gold, Gold);//金币
	

public:
	virtual bool init(const std::string& filename,
		const EAttackMode attackmode,
		const float attackradius,
		const int HP,
		const int MP,
		const int armor,
		const int attack
	);



	static Hero* create(const std::string& filename,
		const EAttackMode attackmode,
		const float attackradius,
		const int HP,
		const int MP,
		const int armor,
		const int attack
	);

void consumeMP();

virtual void takeDamage(Actor* actor);

virtual void takeDamage(Bullet* bullet);

virtual void changeWeapon(Weapon* weapon);

};



#endif // ! HERO_H_

