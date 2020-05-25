#include "MapScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* Map1::createScene()
{
    return Map1::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in MapScene.cpp\n");
}

// on "init" you need to initialize your instance
bool Map1::init()
{
    if (!Scene::init())
    {
        return false;
    }
    //这个地方贴地图吧（挠头
    /*auto map = Sprite::create("start1.png");
    map->setAnchorPoint(Point(0, 0));
    map->setPosition(Point(0, 0));
    map->setScale(0.8);*/

    //贴上了传送门的动画
    auto doorcache = SpriteFrameCache::getInstance();
    doorcache->addSpriteFramesWithFile("door.plist");
    Vector<SpriteFrame*>vec;
    char name[20];
    memset(name, 0, 20);
    for(int i=0;i<17;i++)
    {
        sprintf(name, "door%04d", i);
        vec.pushBack(doorcache->getSpriteFrameByName(name));
    }
    Animation* doorAnimation = Animation::createWithSpriteFrames(vec, 0.1f);
    Animate *doorAnimate = Animate::create(doorAnimation);
    auto door = Sprite::create();
    addChild(door);
    //修改这个地方修改坐标
    door->setPosition(200, 200);
    //修改可以缩放
    //door->setScale(1);
    door->runAction(RepeatForever::create(doorAnimate));
    return true;
}