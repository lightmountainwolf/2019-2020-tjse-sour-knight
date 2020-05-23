#pragma once
#ifndef CREEP_H_
#define CREEP_H_

#include"Constant/Constant.h"
#include"Actor.h"
#include"Component/Debuff.h"
#include<iostream>

class Creep :public Actor
{
public:
	virtual bool init(const std::string& filename,
		const EDebuffType debufftype,
		const EAttackMode attackmode,
		const float attackradius,
		const int HP,
		const int attack);
	static Creep* create(const std::string &filename,
		                 const EDebuffType debufftype,
		                 const EAttackMode attackmode,
		                 const float attackradius,
		                 const int HP,
		                 const int attack);
};



#endif
