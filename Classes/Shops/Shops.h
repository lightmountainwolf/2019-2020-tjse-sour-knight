#pragma once
#ifndef  SHOP_H_
#define SHOP_H_

#include"cocos2d.h"


USING_NS_CC;

class Shops :public Sprite
{
	CC_SYNTHESIZE(int, _x, X);
	CC_SYNTHESIZE(int, _y, Y);

public:
	virtual bool init(const std::string& filename, int x, int y);

	static Shops* create(const std::string& filename, int x, int y);

	int getLocation1X();
	int getLocation2X();
	int getLocation3X();
	int getLocationY();

};
#endif // ! SHOP_H_

