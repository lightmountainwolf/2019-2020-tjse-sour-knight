#pragma once
#ifndef _CONSTANT_H_
#define _CONSTANT_H_

#include"cocos2d.h";

//数学相关
#define PI 3.14159

//物理引擎
#define MY_HERO_1 0x02
#define MY_HERO_2 0x01
#define ENEMY_1   0x08
#define ENEMY_2   0x04
#define MY_BULLET_1 0x04
#define MY_BULLET_2 0x08
#define ENEMY_BULLET_1 0x01
#define ENEMY_BULLET_2 0x02


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
	MELEE=100,//近战
	REMOTE=300//远程攻击
};



//英雄的信息
//Knight
#define HP_OF_KNIGHT 7
#define ARMOR_OF_KNIGHT 6
#define MP_OF_KNIGHT 200

//Tag部分

//场景部分（安全地图与关卡）1~49
#define TAG_OF_FIRST_STAGE 1


//人物部分（英雄角色与敌人） 50~100
#define TAG_OF_KNIGHT 50

#define TAG_OF_ENEMY_1 60






#endif // !_CONSTANT_H_

