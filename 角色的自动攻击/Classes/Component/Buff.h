#pragma once
#ifndef BUFF_H_
#define BUFF_H_

#include <iostream>
#include"cocos2d.h";
USING_NS_CC;

const enum EBuff
{
	ICE_SHIELD,      //冰甲
	POISON_SHIELD,    //毒甲
	FIRE_SHIELD,      //火甲
	ADD_ARMOR,       //提升护甲值
	ADD_HP,          //提升血量
	ADD_MP           //提升能量
};

//Buff类
class Buff :public Sprite
{
	CC_SYNTHESIZE(int, _addArmor, AddArmor);//增加护甲值
	CC_SYNTHESIZE(int, _addHP, AddHP);//增加生命值
	CC_SYNTHESIZE(int, _addMP, AddMP);//增加能量值
	CC_SYNTHESIZE(bool, _iceShield, IceShield);
	CC_SYNTHESIZE(bool, _poisonShield, PoisonShield);
	CC_SYNTHESIZE(bool, _fireShield, FireShield);

public:
	virtual bool init(const std::string& filename,EBuff Typebuff);
	static Buff* create(const std::string& filename,EBuff Typebuff);
};
#endif // !BUFF_H_

