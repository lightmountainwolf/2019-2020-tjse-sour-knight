#pragma once
#ifndef _CONSTANT_H_
#define _CONSTANT_H_

#include"cocos2d.h";

//敌人攻击力与血量
#define CREEP_HP_1 8
#define CREEP_HP_2 12
#define CREEP_HP_3 15
#define CREEP_HP_4 20
#define CREEP_HP_5 36
#define CREEP_HP_6 50

#define BOSS_HP_LOW 500
#define BOSS_HP_MEDIUN 700
#define BOSS_HP_HIGH 900

#define MONSTER_ATTACK_LOW 3
#define MONSTER_ATTACK_MEDIUN 4
#define MONSTER_ATTACK_HIGH 5

//buff与debuff
#define DEBUFF_ATTACK 1
#define NONE_DEBUFF 0


//攻击方式
enum EAttackMode
{
	MELEE,
	REMOTE
};




//英雄的信息
//Knight
#define HP_OF_KNIGHT 7
#define ARMOR_OF_KNIGHT 6
#define MP_OF_KNIGHT 200





#endif // !_CONSTANT_H_

