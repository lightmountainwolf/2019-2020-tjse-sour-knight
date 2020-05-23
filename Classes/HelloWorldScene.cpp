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
#include "startScene.h"

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

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    auto label = Label::createWithTTF("next stage", "fonts/Marker Felt.ttf", 24);
	label->setTag(1);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }

    // add "soulknight" splash screen"
    /*auto sprite = Sprite::create("firstscene.jpeg");
    if (sprite == nullptr)
    {
        problemLoading("'firstscene.jpeg");
    }
    else
    {
        // position the sprite on the center of the screen
        sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

        // add the sprite as a child to this layer
        this->addChild(sprite, 0);
    }*/

	auto knight1 = Sprite::create("knight1.png");

	knight1->setPosition(Vec2(640, 480));

	knight1->setTag(2);

	this->addChild(knight1, 2);

	//进入游戏按钮
	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	listener-> onTouchBegan = [label](Touch* t, Event* e)
	{
		if (label->getBoundingBox().containsPoint(t->getLocation()))
		{
			Director::getInstance()->replaceScene(startScene::createScene());
		}
		return false;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, label);
	
	

	//移动
	auto knightListener = EventListenerKeyboard::create();

	knightListener->onKeyPressed = [=](EventKeyboard::KeyCode code, Event* e)
	{
		log("key code : %d  , code");
		keys[code] = true;
		/*if (keys[EventKeyboard::KeyCode::KEY_W])
		{
			auto UP = MoveTo::create(0.3, Vec2(knight1->getPositionX() - 0, knight1->getPositionY() +5));
			knight1->runAction(UP);
		}
		if (keys[EventKeyboard::KeyCode::KEY_S])
		{
			auto DOWN = MoveTo::create(0.3, Vec2(knight1->getPositionX() - 0, knight1->getPositionY() - 5));
			knight1->runAction(DOWN);
		}
		if (keys[EventKeyboard::KeyCode::KEY_A])
		{
			auto LEFT = MoveTo::create(0.3, Vec2(knight1->getPositionX() - 5, knight1->getPositionY() + 0));
			knight1->runAction(LEFT);
		}
		if (keys[EventKeyboard::KeyCode::KEY_D])
		{
			auto RIGHT = MoveTo::create(0.3, Vec2(knight1->getPositionX() + 5, knight1->getPositionY() + 0));
			knight1->runAction(RIGHT);
		}*/
	};

	knightListener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event)
	{
		keys[keyCode] = false;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(knightListener, this);

	this->scheduleUpdate();

	TMXTiledMap* tmx = TMXTiledMap::create("map.tmx");//地图
	tmx->setTag(3);
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


void HelloWorld::update(float delta)
{

	//视角跟随
	

	int offsetX = 0, offsetY = 0;
	if (keys[EventKeyboard::KeyCode::KEY_D])
	{
		offsetX = -5;
	}
	if (keys[EventKeyboard::KeyCode::KEY_A])
	{
		offsetX = 5;
	}
	if (keys[EventKeyboard::KeyCode::KEY_S])
	{
		offsetY = 5;
	}
	if (keys[EventKeyboard::KeyCode::KEY_W])
	{
		offsetY = -5;
	}
	Node* map = this->getChildByTag(3);

	auto moveTo = MoveTo::create(0.3, Vec2(map->getPositionX() + offsetX, map->getPositionY() + offsetY));
	map->runAction(moveTo);

	//
	Node* door = this->getChildByTag(1);

	if (door->getBoundingBox().containsPoint(Vec2(640, 480)))
	{
		Director::getInstance()->replaceScene(startScene::createScene());
	}

}



