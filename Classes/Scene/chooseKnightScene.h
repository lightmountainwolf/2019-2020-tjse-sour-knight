#pragma once
#ifndef CHOOSE_KNIGHT_SCENE_H
#define CHOOSE_KNIGHT_SCNEN_H

#include"cocos2d.h"
#include"Scene/firstStage.h"
#include"Settings/SoundAndMusic.h"
#include"ui/CocosGUI.h"
#include"Constant/Constant.h"
#include"Equipment/Weapon.h"
#include"Function/CommonFunction.h"

using namespace ui;
USING_NS_CC;

class chooseKnightScene :public Scene
{
	Sprite* knight;
public:
	virtual bool init();
	static Scene* createScene();
	
	CREATE_FUNC(chooseKnightScene);
	void goMenu(Ref* pSender);
	void backMenu(Ref* pSender);
};

#endif