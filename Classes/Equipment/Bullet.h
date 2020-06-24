#pragma once
#ifndef BULLET_H_
#define BULLET_H_

#include"cocos2d.h"
#include"Component/Debuff.h"

USING_NS_CC;

//当你需要创建子弹时，你需要：auto bullet=Bullet::create(const std::string& filename,int attack,EDebuffType debufftype);
//分别代表着文件路径、该子弹会造成的伤害，debuff类型。注意！！！子弹在攻击力与debuff上应该与武器保持一致

class Bullet :public Sprite
{
	CC_SYNTHESIZE(std::string, bulletFilename, BulletFilename);
	CC_SYNTHESIZE(int, _attack, Attack);//攻击力
	CC_SYNTHESIZE(int, _attackFrequncy, AttackFrequency);//攻击频率
	CC_SYNTHESIZE(EDebuffType, _debuff, DebuffType);//释放Debuff的类型
public:
	virtual bool init(const std::string& filename, int attack, int frequency, EDebuffType debufftype);
	static Bullet* create(const std::string& filename, int attack, int frequency, EDebuffType debufftype);

	virtual bool init(const std::string& filename, Bullet* bullet);
	static Bullet* create(const std::string& filename, Bullet* bullet);
};


#endif