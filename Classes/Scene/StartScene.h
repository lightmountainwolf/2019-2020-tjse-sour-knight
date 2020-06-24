#include "Scene/StartScene2.h"
#include "Settings/StartSetting.h"
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
    // ///////////////////////////////////////////////
    virtual void onEnter();
    virtual void onEnterTransitionDidFinish();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void cleanup();

    // ///////////////////////////////////////////////
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // click to start 's callback
    void menuItem1Callback(cocos2d::Ref* pSender);


    // implement the "static create()" method manually
    CREATE_FUNC(Start);
};

#endif // __HELLOWORLD_SCENE_H__
