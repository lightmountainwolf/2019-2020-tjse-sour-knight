#pragma once
#ifndef  PROPS_H_
#define PROPS_H_

#include"cocos2d.h"
#include "Constant/constant.h"
#include "Actor/Hero.h"
#include "Function/CommonFunction.h"

USING_NS_CC;

class Props :public Sprite
{
	int addHP;
	int addMP;
	int addGold;
	int type;
	int xOrigion;
	int yOrigion;
	int radius;
	bool isUsed;
	int price;

public:
	virtual bool init(const std::string& filename, int type,int x, int y, int radius);
    
	static Props* create(const std::string& filename, int type, int x, int y, int radius);

	bool isInRange(Vec2 playerPos);

	void makeEffect(Layer* p, Hero* hero);

	int getPrice();
};
#endif // ! PROPS_H_

