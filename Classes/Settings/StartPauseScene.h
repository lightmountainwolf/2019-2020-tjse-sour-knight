#pragma once
#include "cocos2d.h"

#ifndef __START_PAUSE_SCENE_H__
#define __START_PAUSE_SCENE_H__

//extern bool doContinueGame;

class StartPause : public cocos2d::Scene
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

    // implement the "static create()" method manually
    CREATE_FUNC(StartPause);
};

#endif // __START_PAUSE_SCENE_H__
