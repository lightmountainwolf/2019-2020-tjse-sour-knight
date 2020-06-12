


#ifndef __HELLOWORLD_SCENE_H__

#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include"Scene/HelloWorldSceneF.h"

class HelloWorld : public cocos2d::Layer

{

	cocos2d::TMXTiledMap* map;										

		cocos2d::Sprite* player; 	

		cocos2d::TMXLayer* collidable;

public:

	static cocos2d::Scene* createScene();

	virtual bool init();

	void setPlayerPosition(cocos2d::Point position);								

	cocos2d::Point transPoision(cocos2d::Point position);					

	void screenRoll(cocos2d::Point position);

	std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;

	void update(float delta);



	CREATE_FUNC(HelloWorld);
};
#endif // __HELLOWORLD_SCENE_H__
