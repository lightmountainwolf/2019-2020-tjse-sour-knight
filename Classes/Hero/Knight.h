#pragma once

#ifndef  _KNIGHT_H_
#define _KNIGHHT_H_

#include"Actor/Hero.h"
#include"Constant/Constant.h"
#include<iostream>
#include"Equipment/Weapon.h"

//说明：若建立一个骑士英雄，只需auto knight=Knight::create(const std::string& filename,Weapon* weapon)
//前者为文件路径，后者为骑士所装备的武器
//注意！！！！所有英雄暂时不支持武器的切换
class Knight :public Hero
{

public:
	virtual bool init(const std::string& filename,Weapon* weapon);

	virtual bool init(const std::string& filename, Knight* knight);

	static Knight* create(const std::string& filename,Weapon* weapon);

	static Knight* create(const std::string& filename, Knight* kt);

	void updateSkill();
	void releaseSkill();
	
};



#endif // ! KNIGHT_H_

