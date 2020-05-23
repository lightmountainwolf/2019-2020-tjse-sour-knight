#pragma once
/*
声明：这一版本的任务角色有待于武器类的开发，
所以在实现了武器类的开发的时候会对此类进行补充
*/
#ifndef  KNIGHT_H_
#define KNIGHHT_H_

#include"Actor/Hero.h"
#include"Constant/Constant.h"
#include<iostream>

class Knight :public Hero
{
public:
	//第二个参数是装备的情况，以类的形式开发，将会在后几个版本实现
	virtual bool init(const std::string& filename, const::String& equipment, EAttackMode attackmode);
	//第二个参数是装备的情况，以类的形式开发，将会在后几个版本实现
	static Knight* create(const std::string& filename,const::String& equipment,EAttackMode attackmode);
     
	void skillOfKnight();
};



#endif // ! KNIGHT_H_

