#pragma once
#ifndef BULLET_H_
#define BULLET_H_

#include"cocos2d.h"
#include"Component/Debuff.h"

USING_NS_CC;

class Bullet :public Sprite
{
	CC_SYNTHESIZE(int, _attack, Attack);//攻击力
	CC_SYNTHESIZE(EDebuffType, _debuff, DebuffType);//释放Debuff的类型
public:
	virtual bool init(const std::string& filename,int attack,EDebuffType debufftype);
	static Bullet* create(const std::string& filename,int attack,EDebuffType debufftype);
};


#endif