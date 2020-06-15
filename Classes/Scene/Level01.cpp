#include "Scene/Level01.h"
#include "Actor/Creep.h"



Scene* Level01::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setGravity(Vec2(0.0f, 0.0f));//取消重力场
	scene->setTag(TAG_OF_FIRST_STAGE_SCENE);
	auto layer = Level01::create();
	scene->addChild(layer, 0);
	// ////////////////////////////设置暂停按钮////////////////////////////////////////////
	auto pauseMenuItem = MenuItemImage::create(
		"Buttons/buttonPause.png", "Buttons/buttonPauseClicked.png", CC_CALLBACK_1(Level01::menuPauseCallback, layer));
	pauseMenuItem->setPosition(Vec2(1200, 900));
	float length = 120;
	auto buttonSize = pauseMenuItem->getContentSize();
	float scaleSize = length / buttonSize.width;
	pauseMenuItem->setScale(scaleSize);

	auto startMenu = Menu::create(pauseMenuItem, NULL);
	startMenu->setPosition(Vec2::ZERO);
	scene->addChild(startMenu, 1);
	// //////////////////////////////////////////////////////////////////////////////

	return scene;
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}


bool Level01::init()
{

	if (!Layer::init())
	{
		return false;

	}
////////////////////////////以下为Lavel01类成员变量初始化/////////////////////////////////

	this->setKnightBeenSelected(false);
	this->setKnight(nullptr);
	this->setWeapon(nullptr);
	this->setBullet(nullptr);
	this->setInAttackRange(false);
////////////////////////////以下为定义物理世界(引擎)///////////////////////////////////////////////
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();
	auto body = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 5.0f);
	auto edgeNode = Node::create();
	edgeNode->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	edgeNode->setPhysicsBody(body);
	this->addChild(edgeNode);
	setTouchEnabled(true);
	setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
	///////////////////////////以下为设置地图属性/////////////////////////

	map = TMXTiledMap::create("Backgrounds/forM.tmx");	//地图！

	map->setScale(2);

	addChild(map,0);											


	TMXObjectGroup* group = map->getObjectGroup("obj");					

	ValueMap spawnPoint = group->getObject("player");								

	float x = spawnPoint["x"].asFloat();										

	float y = spawnPoint["y"].asFloat();	

	collidable = map->getLayer("collidable");

	collidable->setVisible(false);

	this->setTag(TAG_OF_LEVEL_01);

	//一个简单的测试
// ////////////////////////////////////////////////////////////////





// ////////////////////////////////////////////////////////////////////


	//生成小怪
	int tagArr[5] = {55,56,57,58,59};

	char monsters[5][3] = { "m1","m2" ,"m3" ,"m4" ,"m5" };

	for (int i = 0; i < 5; i++)
	{
		ValueMap mPoint = group->getObject(monsters[i]);

		float x = 2 * mPoint["x"].asFloat();

		float y = 2 * mPoint["y"].asFloat();

		auto monsterTemp = Creep::create("Creeps/monster3.png", NORMAL, REMOTE, 5, 3);

		auto body2 = PhysicsBody::createBox(monsterTemp->getContentSize());
		body2->setCategoryBitmask(ENEMY_1);
		body2->setCollisionBitmask(ENEMY_2);
		monsterTemp->setPhysicsBody(body2);

		monsterTemp->setPosition(x, y);

		monsterTemp->setTag(tagArr[i]);

		this->addChild(monsterTemp);


		creepsVec.pushBack(monsterTemp);
	}

	this->scheduleUpdate();

	this->schedule(schedule_selector(Level01::myUpData1), 1, -1, 2);

	return true;

}

void Level01::myUpData1(float delta)
{
	creepMove();
}
		
void Level01::onEnter()//注册监听器，设置音乐
{
	Layer::onEnter();
	
	/////////////////////////////以下为角色移动监听器///////////////////////////////////
	auto knightMoveListener = EventListenerKeyboard::create();

	knightMoveListener->onKeyPressed = [=](EventKeyboard::KeyCode code, Event* e)
	{
		keys[code] = true;
	};

	knightMoveListener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event)
	{
		keys[keyCode] = false;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(knightMoveListener, this);

	/////////////////////////////以下为碰撞监听器(暂时还没有添加)/////////////////////////////////////////
	auto listener = EventListenerPhysicsContact::create();
	listener->onContactBegin = [](PhysicsContact& contact)
	{
		return true;
	};
	listener->onContactPreSolve = [](PhysicsContact& contact, PhysicsContactPreSolve& solve)
	{

		return true;
	};
	listener->onContactPostSolve = [](PhysicsContact& contact, const PhysicsContactPostSolve& solve)
	{

	};
	listener->onContactSeparate = [](PhysicsContact& contact)
	{
		auto spriteA = (Sprite*)contact.getShapeA()->getBody()->getNode();
		auto spriteB = (Sprite*)contact.getShapeB()->getBody()->getNode();

		spriteA->runAction(CCBlink::create(3.0f, 10));
		spriteB->runAction(CCBlink::create(3.0f, 10));
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 1);

	playMusic("sound/FightMapCaveBGM.mp3", true);
}

void Level01::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
	log("firstStage onEnterTransitionDidFinish");
}

void Level01::onExitTransitionDidStart()
{
	Layer::onExitTransitionDidStart();
	log("firstStage onExitTransitionDidStart");
}

void Level01::onExit()//注销监听器
{
	Layer::onExit();

}

void Level01::cleanup()
{
	Layer::cleanup();
	log("Level01 cleanup");
	//playMusic("sound/SafeMapBGM.mp3", true, 1);
}

void Level01::menuPauseCallback(cocos2d::Ref* pSender)//暂停按钮的回调
{
	log("menuPauseCallback touched");
	//SimpleAudioEngine::getInstance()->pauseBackgroundMusic();

	auto scene = Pause::createScene();
	Director::getInstance()->pushScene(scene);
	playSound("sound/ClickSound.mp3");
}

bool Level01::onTouchBegan(Touch* touch, Event* event)//鼠标点击，骑士攻击
{
	if ( this->getKnight()->getMP())
	{
		Vec2 p = this->getWeapon()->getPosition();
		auto bullet = Bullet::create("Bullets/bullet1.png", 3, NORMAL);
		this->setBullet(bullet);
		/// ///////////设置碰撞属性
		auto body = PhysicsBody::createBox(bullet->getContentSize());
		body->setCategoryBitmask(MY_BULLET_1);//0010
		body->setCollisionBitmask(MY_BULLET_2);//0001
		bullet->setPhysicsBody(body);
		bullet->setPosition(p);
		this->addChild(bullet);

		/// ///////////////以下为攻击范围内无敌人的攻击方式——随机向某个方向攻击
		float tempAngle = CCRANDOM_0_1() * 2 * PI;
		float x = 250 * cos(tempAngle);
		float y = 250 * sin(tempAngle);
		bullet->runAction(Sequence::create(MoveBy::create(0.3f, Vec2(x, y)), CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, bullet)), NULL));
		updateInformationMP(this, this->getKnight());
		log("%d", this->getKnightBeenSelected());
		return false;
	}
	return false;
}

void Level01::removeFromParent(Node* bullet)//删除子弹的回调函数
{
	bullet->removeFromParent();
}

void Level01::update(float delta)
{
	if (this->getKnightBeenSelected())
	{
		knightMove();

	}

	
	
}

void Level01::creepMove()
{
	int xx, yy, tileGid;

	Point playerPos = this->getKnight()->getPosition();

	

	for (const auto& sprite : this->creepsVec)
	{
		Point pos = sprite->getPosition();

		if ((pos.x >= playerPos.x - REMOTE) && (pos.x <= playerPos.x + REMOTE))
		{
			if ((pos.y >= playerPos.y - REMOTE) && (pos.y <= playerPos.y + REMOTE))
			{
				auto moveToKnight = MoveTo::create(1.0f, Vec2(playerPos.x, playerPos.y));
				sprite->runAction(moveToKnight);
				continue;
			}
		}
		
		float tempAngle = CCRANDOM_0_1() * 2 * PI;
		float x = 32 * cos(tempAngle);
		float y = 32 * sin(tempAngle);
		auto move = MoveBy::create(1.0f, Vec2(x, y));
		
		

		xx = pos.x + x;
		yy = pos.y + y;

		int xxx = 0.5 * xx / map->getTileSize().width;
		int yyy = ((map->getMapSize().height * map->getTileSize().height) - 0.5 * yy) /map->getTileSize().height;

		Point posAfter = Point(xxx, yyy);

		tileGid = collidable->getTileGIDAt(posAfter);
		if (tileGid > 0) 
		{


			Value prop = map->getPropertiesForGID(tileGid);

			ValueMap propValueMap = prop.asValueMap();

			std::string collision = propValueMap["Collidable"].asString();

			if (collision == "true")
			{
				auto moveBack = MoveBy::create(0.5f, Vec2(-x, -y));
				sprite->runAction(moveBack);
				continue;
			}
			
		}
		else
		{
			sprite->runAction(move);

		}
	}
}


void Level01::knightMove()//放置在update里的函数，实现骑士角色的移动
{
	Point playerPos = this->getKnight()->getPosition();

	if (keys[EventKeyboard::KeyCode::KEY_D])
	{
		playerPos.x += map->getTileSize().width/4;

		this->getKnight()->runAction(FlipX::create(false));
		this->getWeapon()->runAction(FlipX::create(false));
		log("D");
	}
	if (keys[EventKeyboard::KeyCode::KEY_A])
	{
		playerPos.x -= map->getTileSize().width/4;

		this->getKnight()->runAction(FlipX::create(true));
		this->getWeapon()->runAction(FlipX::create(true));
		log("A");
	}
	if (keys[EventKeyboard::KeyCode::KEY_S])
	{
		playerPos.y -= map->getTileSize().height/4;
		log("S");
	}
	if (keys[EventKeyboard::KeyCode::KEY_W])
	{
		playerPos.y += map->getTileSize().height/4;
		log("W");
	}
	
	this->setPlayerPosition(playerPos);
	this->screenRoll(playerPos);
}


void Level01::setPlayerPosition(Point position)
{

		//从像素点坐标转化为瓦片坐标

		Point tileCoord = this->transPoision(position);
		//tileCoord.x = tileCoord.x / 2;
		//tileCoord.y = (_tileMap->getMapSize().height-tileCoord.y)/2;

			//获得瓦片的GID

		int tileGid = collidable->getTileGIDAt(tileCoord);

		if (tileGid > 0)
		{
			Value prop = map->getPropertiesForGID(tileGid);

			ValueMap propValueMap = prop.asValueMap();

			std::string collision = propValueMap["Collidable"].asString();

			if (collision == "true") { //碰撞检测成功									

				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("empty.wav");

				return;

			}

		}

		this->getKnight()->setPosition(position);
		Point pos = Point(position.x, position.y - 25);
		this->getWeapon()->setPosition(pos);
	

}


Point Level01::transPoision(Point pos)
{
	int x = 0.5*pos.x / map->getTileSize().width; 									
	int y = ((map->getMapSize().height * map->getTileSize().height) - 0.5* pos.y) /

	map->getTileSize().height; 		

	return Point(x, y);
}


void Level01::screenRoll(Point position)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
					
	//屏幕中心点

	Point pointA = Point(visibleSize.width / 2, visibleSize.height / 2); 	
	
	Point pointB = position;
	//position

	//地图移动偏移量

	Point offset = (pointA - pointB); 											

	this->setPosition(offset);												

}
