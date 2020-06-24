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
#define GROUNDATTACK_1 1

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

#define MONSTER_ATTACK_LOW 2
#define MONSTER_ATTACK_MEDIUM 3
#define MONSTER_ATTACK_HIGH 4

//人物的攻击力
#define HERO_ATTACK_LOW 3
#define HERO_ATTACK_MEDIUM 4
#define HERO_ATTACK_HIGH 5

//角色攻击频率
#define ATTACK_FREQUENCY_1 1
#define ATTACK_FREQUENCY_2 2
#define ATTACK_FREQUENCY_3 3
#define ATTACK_FREQUENCY_4 4
#define ATTACK_FREQUENCY_5 5

//攻击耗蓝值
#define CONSUMPTION_0 0
#define CONSUMPTION_1 1
#define CONSUMPTION_2 2
#define CONSUMPTION_3 3
#define CONSUMPTION_4 4
#define CONSUMPTION_5 5



//buff与debuff
#define DEBUFF_ATTACK 1
#define NONE_DEBUFF 0


//攻击方式
enum  EAttackMode 
{
	HERO_MELEE = 150,//近战
	HERO_MELEE_1 = 200,
	HERO_MELEE_2 = 250,
	HERO_MELEE_3 = 300,
	HERO_MELEE_4 = 399,
	ENEMY_REMOTE = 300,//远程攻击
	ENEMY_REMOTE2 = 600,
	ENEMY_MELEE = 299,
	HERO_REMOTE = 400,//英雄-远程攻击范围
	HERO_REMOTE_1 = 450,
	HERO_REMOTE_2 = 500,
	HERO_REMOTE_3 = 550

};



//英雄的信息
//Knight
#define HP_OF_KNIGHT 7
#define ARMOR_OF_KNIGHT 6
#define MP_OF_KNIGHT 200
#define SKILL_POINT_OF_KNIGHT 200

//Tag部分

//场景部分（安全地图与关卡）1~34
#define TAG_OF_FIRST_STAGE_LAYER 1
#define TAG_OF_FIRST_STAGE_SCENE 2
#define TAG_OF_LEVEL_01 3
#define TAG_OF_LEVEL_02 4
#define TAG_OF_LEVEL_03 5
#define TAG_OF_LEVEL_04 6

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

//目前排到了96
#define MAX_TAG_OF_MONSTER 96


//信息栏部分（HP，MP，护甲）201~250
#define TAG_OF_LABEL_HP 201
#define TAG_OF_LABEL_ARMOR 202
#define TAG_OF_LABEL_MP 203

#define TAG_OF_HP_BAR 204
#define TAG_OF_ARMOR_BAR 205
#define TAG_OF_MP_BAR 206
#define TAG_OF_INFORMATION_BOX_BAR 207

#define TAG_OF_SKILL_BACKGROUND 208
#define TAG_OF_SKILL_POINT 209
#define TAG_OF_LABEL_GOLD 210

//传送门部分 251~299

#define TAG_OG_SAFEMAP_DOOR 251


//武器部分 300~349

#define TAG_OF_KNIGHT_INITIAL_WEAPON 300

//子弹部分 350~400
#define TAG_OF_BULLET_01 350

//道具部分
#define PROPS_DRUG_HP 401
#define PROPS_DRUG_MP 402
#define PROPS_DRUG_HPMP 403
#define PROPS_GOLD 404
#define TAG_OF_PROPS_HP 405
#define TAG_OF_PROPS_MP 406
#define PROPS_DRUG_HP_FULL 407
#define PROPS_DRUG_MP_FULL 408
#define EMPTY 409
#define PRICE_OF_DRUG_HP 18
#define PRICE_OF_DRUG_MP 12
#define PRICE_OF_DRUG_HPMP 30


//死亡场景部分
#define TAG_OF_PLAYER 410

#endif // !_CONSTANT_H_

