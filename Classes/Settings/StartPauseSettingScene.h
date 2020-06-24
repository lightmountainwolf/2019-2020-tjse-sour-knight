#pragma once
#include "cocos2d.h"
#include "Settings/StartPauseScene.h"
#include "SimpleAudioEngine.h"


#ifndef __START_PAUSE_SETTING_SCENE_H__
#define __START_PAUSE_SETTING_SCENE_H__

//extern bool doContinueGame;

class StartPauseSetting : public cocos2d::Scene
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

    //new game
    void menuNewGameCallback(cocos2d::Ref* pSender);

    //continue game
    void menuContinueGameCallback(cocos2d::Ref* pSender);

    //“Ù–ß
    void menuSoundToggleCallback(cocos2d::Ref* pSender);

    //“Ù¿÷
    void menuMusicToggleCallback(cocos2d::Ref* pSender);

    void menuMusicVolumnIncrease(cocos2d::Ref* pSender);
    void menuMusicVolumnDecrease(cocos2d::Ref* pSender);
    void menuSoundVolumnIncrease(cocos2d::Ref* pSender);
    void menuSoundVolumnDecrease(cocos2d::Ref* pSender);

    CREATE_FUNC(StartPauseSetting);
};

#endif // __START_PAUSE_SETIING_SCENE_H__
