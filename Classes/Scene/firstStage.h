
//���ǰ�ȫ��ͼ
#pragma once
#ifndef __FIRST_STAGE_H__
#define __FIRST_STAGE_H__

#include"Scene/startScene.h"
#include"cocos2d.h"
#include"Hero/Knight.h"
#include"Constant/Constant.h"
#include"Equipment/Bullet.h"
#include"SimpleAudioEngine.h"
#include"Equipment/Weapon.h"
#include"Scene/Level01.h"
#include"Scene/Level02.h"
#include"Scene/Level03.h"
#include"Scene/Level04.h"
#include"Scene/DeadScene.h"
#include"Global/GlobalVariables.h"

using namespace CocosDenshion;
USING_NS_CC;


class firstStage : public cocos2d::Layer
{
	cocos2d::TMXTiledMap* map;

	cocos2d::TMXLayer* collidable;

	CC_SYNTHESIZE(Knight*, _knight, Knight);//��ɫ--��ʿ
	CC_SYNTHESIZE(Weapon*, _weapon, Weapon);//����
	CC_SYNTHESIZE(Bullet*, _bullet, Bullet);//�ӵ�
	CC_SYNTHESIZE(std::string, _knightFilename, KnightFilename);//��ʿ�ļ���
	CC_SYNTHESIZE(std::string, _weaponFilename, WeaponFilename);//�����ļ���
	CC_SYNTHESIZE(std::string, _bulletFilename, BulletFilename);//�ӵ��ļ���

	CC_SYNTHESIZE(bool, _knightBeenSelected, KnightBeenSelected);//��ɫ��ʿ�Ƿ�ѡ��
	CC_SYNTHESIZE(bool, _inAttackRange, InAttackRange);//�жϵ����Ƿ��ڹ�����Χ��
public:
	void update(float delta);
	 void knightMove();//��ʿ��ɫ���ƶ�

	static cocos2d::Scene* createScene();//��������
	virtual bool init();//��ʼ��

	virtual void onEnter();//ע�������
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();//ע��������
	virtual void onExitTransitionDidStart();
	virtual void cleanup();


	void menuPauseCallback(cocos2d::Ref* pSender);

	bool chooseKnightTouchBegan(Touch* touch, Event* event);//ѡ��Ӣ��-��ʿ����ʼ��
	void chooseKnightTouchEnded(Touch* touch, Event* event);//ѡ��Ӣ��-��ʿ��������

	
	bool onTouchBegan(Touch* touch, Event* event);
	void removeFromParent( Node* m);
	
	void attackRandomly(Vec2 enemy, Hero* hero);
	void nextScene();
// ///////////////////////////////////////////

	void setPlayerPosition(cocos2d::Point position);

	cocos2d::Point transPoision(cocos2d::Point position);

	void screenRoll(cocos2d::Point position);

// //////////////////////////////////////////

	CREATE_FUNC(firstStage);

private:
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;
	std::vector<cocos2d::EventListener*> listenerVec;
};


#endif // __FIRST_STAGE_H__
