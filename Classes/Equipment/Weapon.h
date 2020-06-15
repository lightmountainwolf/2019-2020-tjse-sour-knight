#pragma once

#ifndef _WEAPON_H_
#define _WEAPON_H_

#include"cocos2d.h"
#include"Constant/Constant.h"
#include"Component/Debuff.h"

USING_NS_CC;

//说明：在建立武器类时，include"Equipment/Weapon.h"即可，建立方式为auto weapon=Weapon::create(const std::string& filename, int attack, int mpconsuming, EAttackMode attackmode, EDebuffType debufftype);
//从左到右依次为：攻击力，消耗体力的值，攻击方式（远程or进程），存在的debuff

class Weapon :public Sprite
{
	CC_SYNTHESIZE(int, _attack, Attack);//攻击力
	CC_SYNTHESIZE(EDebuffType, _debuff, DebuffType);//释放Debuff的类型
	CC_SYNTHESIZE(EAttackMode, _attackMode, AttackMode);//攻击方式
	CC_SYNTHESIZE(int, _MPConsuming, MPConsuming);//消耗能量的值
public:
	virtual bool init(const std::string& filename, int attack, int mpconsuming, EAttackMode attackmode, EDebuffType debufftype);
	static Weapon* create(const std::string& filename, int attack, int mpconsuming, EAttackMode attackmode, EDebuffType debufftype);
	static Weapon* create(const std::string& filename, Weapon* wep);
	virtual bool init(const std::string& filename, Weapon* wep);
};


#endif