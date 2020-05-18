#ifndef __START_SCENE_H__
#define __START_SCENE_H__

#include "cocos2d.h"

class startScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	

	// implement the "static create()" method manually
	CREATE_FUNC(startScene);
};

#endif