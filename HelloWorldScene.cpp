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

CCScene* HelloWorld::createScene()
{
	CCScene* s = CCScene::create();
	HelloWorld* layer = HelloWorld::create();
	s->addChild(layer);
	return s;
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

	if (!Layer::init())
	{
		return false;

	}

	Size visibleSize = Director::getInstance()->getVisibleSize();

	Point origin = Director::getInstance()->getVisibleOrigin();


	map = TMXTiledMap::create("forM.tmx");	


	map->setScale(2);

		addChild(map,0,100);											


		TMXObjectGroup* group = map->getObjectGroup("obj");					

		ValueMap spawnPoint = group->getObject("player");								

		float x = spawnPoint["x"].asFloat();										

		float y = spawnPoint["y"].asFloat();										


		player = Sprite::create("fox.png");

		
		player->setScale(4);


		player->setPosition(Point(x, y));											
		this->addChild(player);
		//addChild(_player, 2, 200);

	
		collidable = map->getLayer("collidable");									

			collidable->setVisible(false);


			auto knightListener = EventListenerKeyboard::create();

			knightListener->onKeyPressed = [=](EventKeyboard::KeyCode code, Event* e)
			{
				log("key code : %d  , code");
				keys[code] = true;
			};

			knightListener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event)
			{
				keys[keyCode] = false;
			};
			_eventDispatcher->addEventListenerWithSceneGraphPriority(knightListener, this);

			this->scheduleUpdate();

	return true;

}

void HelloWorld::update(float delta)
{
	Point playerPos = player->getPosition();

	
	if (keys[EventKeyboard::KeyCode::KEY_D])
	{
		playerPos.x += map->getTileSize().width/4;

		player->runAction(FlipX::create(false));
	}
	if (keys[EventKeyboard::KeyCode::KEY_A])
	{
		playerPos.x -= map->getTileSize().width/4;

		player->runAction(FlipX::create(true));
	}
	if (keys[EventKeyboard::KeyCode::KEY_S])
	{
		playerPos.y -= map->getTileSize().height/4;
	}
	if (keys[EventKeyboard::KeyCode::KEY_W])
	{
		playerPos.y += map->getTileSize().height/4;
	}
	

	this->setPlayerPosition(playerPos);
	this->screenRoll(playerPos);
	//_player->runAction(moveTo);

	}


void HelloWorld::setPlayerPosition(Point position)

{

	//从像素点坐标转化为瓦片坐标

	Point tileCoord = this->transPoision(position);
	//tileCoord.x = tileCoord.x / 2;
	//tileCoord.y = (_tileMap->getMapSize().height-tileCoord.y)/2;


		//获得瓦片的GID

		int tileGid = collidable->getTileGIDAt(tileCoord);								

		if (tileGid > 0) {
			

				Value prop = map->getPropertiesForGID(tileGid);							

				ValueMap propValueMap = prop.asValueMap();								


				std::string collision = propValueMap["Collidable"].asString();						



				if (collision == "true") { //碰撞检测成功									

					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("empty.wav");		

						return;

				}

		}

	player->setPosition(position);

}


Point HelloWorld::transPoision(Point pos)

{

	int x = 0.5*pos.x / map->getTileSize().width; 									

		int y = ((map->getMapSize().height * map->getTileSize().height) - 0.5* pos.y) /

		map->getTileSize().height; 		

		return Point(x, y);

}


void HelloWorld::screenRoll(Point position)

{

	Size visibleSize = Director::getInstance()->getVisibleSize();
					

		//屏幕中心点

		Point pointA = Point(visibleSize.width / 2, visibleSize.height / 2); 	
	
		Point pointB = position;
		//position

		log("目标位置 (%f ,%f) ", pointB.x, pointB.y);

	//地图移动偏移量

	Point offset = (pointA - pointB); 											

		log("offset (%f ,%f) ", offset.x, offset.y);

	this->setPosition(offset);												

}
