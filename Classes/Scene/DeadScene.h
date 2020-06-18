#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#pragma once
#ifndef __DEAD_SCENE_H__
#define __DEAD_SCENE_H__

class Dead : public cocos2d::Scene
{
private:
    int clickNum;
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // click to start 's callback
    void menuContinueCallback(cocos2d::Ref* pSender);


    // implement the "static create()" method manually
    CREATE_FUNC(Dead);
};

#endif // __DEAD_SCENE_H__
