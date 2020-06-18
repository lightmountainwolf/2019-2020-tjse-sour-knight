#pragma once
#ifndef _CONSTANT_H_
#define _CONSTANT_H_

#include"cocos2d.h"

//数学相关
#define PI 3.14159

//物理引擎(用于碰撞检测)

#define WEAPON_1 0x00//远程武器通用掩码
#define WEAPON_2 0x00
#define MY_HERO_1 0x02
#define MY_HERO_2 0x01
#define ENEMY_1   0x08
#define ENEMY_2   0x04
#define MY_BULLET_1 0x04  //英雄的远程武器子弹和近战武器
#define MY_BULLET_2 0x08
#define ENEMY_BULLET_1 0x01//敌人的远程武器子弹和近战武器
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
	ENEMY_REMOTE=300,//远程攻击
	HERO_REMOTE=500 //英雄-远程攻击范围
	
};


//英雄的信息
//Knight
#define HP_OF_KNIGHT 7
#define ARMOR_OF_KNIGHT 6
#define MP_OF_KNIGHT 200

//Tag部分

//场景部分（安全地图与关卡）1~34
#define TAG_OF_FIRST_STAGE_LAYER 1
#define TAG_OF_FIRST_STAGE_SCENE 2
#define TAG_OF_LEVEL_01 3


//人物贴图部分
#define SIZE_OF_HERO 35

//人物部分（英雄角色与敌人） 50~200
#define TAG_OF_KNIGHT 50

//小怪tag
#define TAG_OF_MONSTER_1 55
#define TAG_OF_MONSTER_2 56
#define TAG_OF_MONSTER_3 57
#define TAG_OF_MONSTER_4 58
#define TAG_OF_MONSTER_5 59

//目前排到了69
#define MAX_TAG_OF_MONSTER 84


//信息栏部分（HP，MP，护甲）201~250
#define TAG_OF_LABEL_HP 201
#define TAG_OF_LABEL_ARMOR 202
#define TAG_OF_LABEL_MP 203

#define TAG_OF_HP_BAR 204
#define TAG_OF_ARMOR_BAR 205
#define TAG_OF_MP_BAR 206

#define TAG_OF_INFORMATION_BOX_BAR 207

//传送门部分 251~299

#define TAG_OG_SAFEMAP_DOOR 251


//武器部分 300~349

#define TAG_OF_KNIGHT_INITIAL_WEAPON 300

//子弹部分 350~400
#define TAG_OF_BULLET_01 350




#endif // !_CONSTANT_H_

