#pragma once
#ifndef __START_SETTING_SCENE_H__
#define __START_SETTING_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"


class StartSetting : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    virtual void onEnter();
    virtual void onEnterTransitionDidFinish();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
    virtual void cleanup();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    //setting
    void menuSettingCallback(cocos2d::Ref* pSender);
    void menuSoundToggleCallback(cocos2d::Ref* pSender);
    void menuMusicToggleCallback(cocos2d::Ref* pSender);


    //new game
    void menuNewGameCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(StartSetting);
};

#endif // __START_SETTING_SCENE_H__

//#define __START2_SCENE_H__