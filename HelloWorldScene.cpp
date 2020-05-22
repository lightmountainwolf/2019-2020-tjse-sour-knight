/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	TMXTiledMap* tmx = TMXTiledMap::create("map.tmx");//地图
	//改变位置
	/*tmx->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	CCLOG("%f,%f", visibleSize.width / 2, visibleSize.height / 2);
	tmx->setAnchorPoint(Vec2(0.5, 0.5));
	tmx->setScale(Director::getInstance()->getContentScaleFactor());*/
	//获取地图属性
	addChild(tmx, 0);
	//改变地图大小，参数为倍数
	//tmx->setScale(0.5);
	auto mapProperties = tmx->getProperties();
	auto str = mapProperties["type"].asString();
	CCLOG("tmx pro:%s", str.c_str());
	//获取图层属性
	auto sceneLayer = tmx->getLayer("scene");
	auto layerProperties = sceneLayer->getProperties();
	CCLOG("layer pro:%s", layerProperties["type"].asString().c_str());
	//获取图块属性
	auto tilePro = tmx->getPropertiesForGID(1).asValueMap();
	CCLOG("tile pro:%s", tilePro["type"].asString().c_str());
	//获取对象属性
	auto objectGroup = tmx->getObjectGroup("object");
	auto obj = objectGroup->getObject("player");

	CCLOG("tile pro:%s", obj["type"].asString().c_str());

	//修改指定区域的颜色
	/*auto colorObj = objectGroup->getObject("color");
	auto colorObjX = colorObj["x"].asInt() / 32;
	auto colorObjY = colorObj["y"].asInt() / 32;
	auto colorObjW = colorObj["width"].asInt() / 32;
	auto colorObjH = colorObj["height"].asInt() / 32;
	for (int x = colorObjX; x < colorObjX + colorObjW; x++) {
		for (int y = colorObjY; y < colorObjY + colorObjH; y++) {
			auto sprite = sceneLayer->getTileAt(Vec2(x, tmx->getMapSize().height-y));
			sprite->setColor(Color3B(225, 0, 0));
		}
	}*/

	auto player = Sprite::create("sc.png");//这个是对象
	player->setPosition(obj["x"].asFloat(), obj["y"].asFloat());
	addChild(player);
	//这是鼠标监听
	auto eventListener = EventListenerTouchOneByOne::create();
	eventListener->onTouchBegan = [tmx, sceneLayer,player](Touch* touch, Event* event) {
		auto point = tmx->convertToNodeSpace(touch->getLocation());
		point.x = static_cast<int>(point.x / 32);
		point.y = tmx->getMapSize().height - static_cast<int>(point.y / 32)-1;

		auto t = sceneLayer->getTileAt(point);
		//检查监听是否正确
		//t->setColor(Color3B(225, 0, 0));

		//碰撞设置
		auto gid = sceneLayer->getTileGIDAt(point);
		auto p = tmx->getPropertiesForGID(gid).asValueMap();

		if (p["move"].isNull() != true && p["move"].asBool() == true){
			player->setPosition(t->getPosition().x, t->getPosition().y);
			}

		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, tmx);
	
	
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
