#pragma once
#ifndef DEBUFF_H_
#define DEBUFF_H_

#include "cocos2d.h";
#include  "Constant/Constant.h"
#include <iostream>;
USING_NS_CC;

enum EDebuffType
{
	FROST, //±˘∂≥
	BURN,  //…’…À
	POSIONING,//÷–∂æ
	NORMAL//√ª”–debuff
};


class Debuff:public Sprite
{
	CC_SYNTHESIZE(int, _debuffAttack, DebuffAttack);
public:
	virtual bool init(const std::string &filename,EDebuffType debuff);
	virtual bool init(EDebuffType debuff);

	static Debuff* create(const std::string &filename,EDebuffType debuff);
	static Debuff* create(EDebuffType debuff);
};

#endif