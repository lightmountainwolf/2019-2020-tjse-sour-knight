#pragma once

#ifndef BOX_H_
#define BOX_H_

#include"cocos2d.h"
#include"Component/Buff.h"
#include"Component/Debuff.h"
#include"Constant/Constant.h"
#include"Equipment/Bullet.h"
#include<iostream>

USING_NS_CC;

class Box :public Sprite
{

	CC_SYNTHESIZE(int, _HP, HP);//–°∫Ï∆ø
	CC_SYNTHESIZE(int, _MP, MP);//–°¿∂∆ø
	CC_SYNTHESIZE(int, _GOLD, GOLD);//«Æ«Æ
	CC_SYNTHESIZE(int, _BULE, BULE);//¿∂¿∂
	CC_SYNTHESIZE(bool, _open, Open);//±¶œ‰ «∑Òø…“‘¥Úø™
	CC_SYNTHESIZE(std::string, _weaponIndex, weaponIndex);//Œ‰∆˜
	cocos2d::Vector<Sprite*> insideVec;

public:
	int getInside();

	void addInside() {
		for (int i = 0; i < getInside(); i++)
			addChild(insideVec.at(i));
	}

	void setInP() {
		for (int i = 0; i < getInside(); i++)
			insideVec.at(i)->setPosition(0.5 * this->getPosition());
	}
	void setInsideUn() {
		for (int i = 0; i < getInside(); i++)
			insideVec.at(i)->setVisible(false);
	}
	void setInsideV() {
		for (int i = 0; i < getInside(); i++)
			insideVec.at(i)->setVisible(true);
	}
	virtual bool init(const std::string& filename,
		const int allHp,
		const int allMp,
		const int GOLD,
		const int BULE,
		const std::string& weaponIndex);

	static Box* create(const std::string& filename,
		const int allHp,
		const int allMp,
		const int GOLD,
		const int BULE,
		const std::string& weaponIndex);
	void insertMP();
	void insertHP();
	void insertGOLD();
	void insertBULE();
	void insertWeapon(const std::string& weaponIndex);

	void initData();
};


#endif

