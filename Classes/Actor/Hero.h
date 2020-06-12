#pragma once
#ifndef  HERO_H_
#define HERO_H_

#include<iostream>
#include"cocos2d.h"
#include "Constant/constant.h"
#include "Actor.h"

USING_NS_CC;

class Hero :public Actor
{
	CC_SYNTHESIZE(int, _armor, Armor);//护甲
	CC_SYNTHESIZE(int, _MP, MP);//蓝条（能量）
	CC_SYNTHESIZE(int, _MPConsuming, MPConsuming);//每一次攻击消耗的能量值


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
};



#endif // ! HERO_H_

