#pragma once
#ifndef CREEP_H_
#define CREEP_H_

#include"Constant/Constant.h"
#include"Actor.h"
#include"Component/Debuff.h"
#include<iostream>

//说明：如果你想设置一个小怪，只需auto creep=Creep::create(filename,debuffType,attackMode,HP,attack)即可
//参数分别代表：文件路径、debuff效果，攻击方式，血量，攻击力，注意其中的枚举类型参数
class Creep :public Actor
{
public:
	virtual bool init(const std::string& filename,
		const EDebuffType debufftype,
		const EAttackMode attackmode,
		const int HP,
		const int attack,
		bool active);
		bool active;//active代表是否活跃
	static Creep* create(const std::string &filename,
		                 const EDebuffType debufftype,
		                 const EAttackMode attackmode,
		                 const int HP,
		                 const int attack,
						 bool active);
};



#endif
