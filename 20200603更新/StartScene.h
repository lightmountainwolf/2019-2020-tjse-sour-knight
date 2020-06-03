#include "StartScene2.h"
#include "StartSetting.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#pragma once
#ifndef __START_SCENE_H__
#define __START_SCENE_H__

class Start : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // click to start 's callback
    void menuItem1Callback(cocos2d::Ref* pSender);


    // implement the "static create()" method manually
    CREATE_FUNC(Start);
};

#endif // __HELLOWORLD_SCENE_H__
