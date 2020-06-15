//这是安全地图

#include "Scene/startScene.h"
#include "Scene/startScene2.h"
#include "Scene/firstStage.h"
#include"Scene/chooseKnightScene.h"
#include"Settings/SoundAndMusic.h"
#include"Settings/pauseControl.h"
#include"Settings/CreateDoor.h"
#include"Function/CommonFunction.h"


Scene* firstStage::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setGravity(Vec2(0.0f, 0.0f));//取消重力场
	scene->setTag(TAG_OF_FIRST_STAGE_SCENE);
	auto layer = firstStage::create();
	scene->addChild(layer, 0);

// ////////////////////////////设置暂停按钮////////////////////////////////////////////
	auto pauseMenuItem = MenuItemImage::create(
		"Buttons/buttonPause.png", "Buttons/buttonPauseClicked.png", CC_CALLBACK_1(firstStage::menuPauseCallback, layer));
	pauseMenuItem->setPosition(Vec2(1200, 900));
	float length = 120;
	auto buttonSize = pauseMenuItem->getContentSize();
	float scaleSize = length / buttonSize.width;
	pauseMenuItem->setScale(scaleSize);

	auto startMenu = Menu::create(pauseMenuItem, NULL);
	startMenu->setPosition(Vec2::ZERO);
	scene->addChild(startMenu,1);
	// //////////////////////////////////////////////////////////////////////////////
	
	return scene;
}

static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool firstStage::init()
{

	if (!Layer::init())
	{
		return false;
	}
////////////////////////////以下为firstStage类成员变量初始化/////////////////////////////////

	this->setKnightBeenSelected(false);
	this->setInAttackRange(false);
////////////////////////////以下为定义物理世界(引擎)///////////////////////////////////////////////
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto body = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 5.0f);
	auto edgeNode = Node::create();
	edgeNode->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	edgeNode->setPhysicsBody(body);
	this->addChild(edgeNode);
	setTouchEnabled(true);
	setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
///////////////////////////以下为设置地图属性/////////////////////////
	 map = TMXTiledMap::create("Backgrounds/safeMap.tmx");//地图
	//改变位置

	map->setScale(2);

	//获取地图属性
	addChild(map, 0);

	//放置传送门
	auto door = setDoor(1600, 636, 200);
	this->addChild(door);
	
	TMXObjectGroup* group = map->getObjectGroup("obj");

	ValueMap spawnPoint = group->getObject("player");

	float x = spawnPoint["x"].asFloat();

	float y = spawnPoint["y"].asFloat();

	collidable = map->getLayer("collidable");

	collidable->setVisible(false);


	this->setTag(TAG_OF_FIRST_STAGE_LAYER);

/////////////////////////////////以下为人物属性设置////////////////////////////////////

	auto knight= Sprite::create("Heroes/unchosenKnight.png");//注意这是角色未被选择时的图片，仅为一张贴图而已
// //设置碰撞属性
// //
	knight->setPosition(Vec2(640, 480));
	log("%f", knight->getPosition().x);
	log("%f", knight->getPosition().y);

	knight->setTag(TAG_OF_KNIGHT);

	this->addChild(knight);
		
	this->scheduleUpdate();
	return true;
}

void firstStage::onEnter()//注册监听器，设置音乐
{
	Layer::onEnter();
/////////////////////////////以下为角色选择监听器///////////////////////////////////
	
	auto KnightSelectedListener = EventListenerTouchOneByOne::create();
	KnightSelectedListener->setSwallowTouches(true);
	KnightSelectedListener->onTouchBegan = CC_CALLBACK_2(firstStage::chooseKnightTouchBegan, this);
	
	KnightSelectedListener->onTouchEnded = CC_CALLBACK_2(firstStage::chooseKnightTouchEnded, this);
	
	// 注册监听器
	EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
	eventDispatcher->addEventListenerWithSceneGraphPriority(KnightSelectedListener, getChildByTag(TAG_OF_KNIGHT));



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

		playMusic("sound/SafeMapBGM.mp3", true);	
}

void firstStage::onEnterTransitionDidFinish()
{
Layer::onEnterTransitionDidFinish();
	log("firstStage onEnterTransitionDidFinish");
}

void firstStage::onExitTransitionDidStart()
{
	Layer::onExitTransitionDidStart();
	log("firstStage onExitTransitionDidStart");
}

void firstStage::onExit()//注销监听器
{
	Layer::onExit();

}

void firstStage::cleanup()
{
	Layer::cleanup();
	log("firstStage cleanup");
	//playMusic("sound/SafeMapBGM.mp3", true, 1);
}

void firstStage::menuPauseCallback(cocos2d::Ref* pSender)//暂停按钮的回调
{
	log("menuPauseCallback touched");
	//SimpleAudioEngine::getInstance()->pauseBackgroundMusic();

	auto scene = Pause::createScene();
	Director::getInstance()->pushScene(scene);
	playSound("sound/ClickSound.mp3");
}

bool firstStage::chooseKnightTouchBegan(Touch* touch, Event* event)//选择英雄-骑士（判断是否点击相应图标）
{
	//获取事件所绑定的target
	auto target = static_cast<Sprite*>(event->getCurrentTarget());
	Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
	Size s = target->getContentSize();
	Rect rect = Rect(0, 0, s.width, s.height);

	//单击范围判断检测,选择角色时的场景切换
	if (rect.containsPoint(locationInNode))
	{
		return true;
	}
	return false;
}

void firstStage::chooseKnightTouchEnded(Touch* touch, Event* event)//选择英雄
{
	if (this->_knightBeenSelected == false)
	{
		auto sc = chooseKnightScene::create();
		auto reScene = TransitionProgressInOut::create(0.3f, sc);
		playSound("sound/ClickSound.mp3");
		Director::getInstance()->replaceScene(reScene);
	}
}


bool firstStage::onTouchBegan(Touch* touch, Event* event)//鼠标点击，骑士攻击
{
	if (this->getKnightBeenSelected() && this->getKnight()->getMP())
	{
		Vec2 p = this->getWeapon()->getPosition();
		auto bullet = Bullet::create("Bullets/bullet1.png", 3, NORMAL);
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
			updateInformationMP(this ,this->getKnight());
			

		return false;
	}
	return false;
}


void firstStage::removeFromParent(Node* bullet)//删除子弹的回调函数
{
	bullet->removeFromParent();
}

void firstStage::update(float delta)
{
	if (this->_knightBeenSelected)
	{
		knightMove();

	}
}

void firstStage::knightMove()//放置在update里的函数，实现骑士角色的移动
{
	Point playerPos = this->getKnight()->getPosition();


	if (keys[EventKeyboard::KeyCode::KEY_D])
	{
		playerPos.x += map->getTileSize().width / 4;

		this->getKnight()->runAction(FlipX::create(false));
		this->getWeapon()->runAction(FlipX::create(false));
	}
	if (keys[EventKeyboard::KeyCode::KEY_A])
	{
		playerPos.x -= map->getTileSize().width / 4;

		this->getKnight()->runAction(FlipX::create(true));
		this->getWeapon()->runAction(FlipX::create(true));
	}
	if (keys[EventKeyboard::KeyCode::KEY_S])
	{
		playerPos.y -= map->getTileSize().height / 4;
	}
	if (keys[EventKeyboard::KeyCode::KEY_W])
	{
		playerPos.y += map->getTileSize().height / 4;
	}


	this->setPlayerPosition(playerPos);
	this->screenRoll(playerPos);




}

void firstStage::setPlayerPosition(Point position)

{
	if (this->getKnightBeenSelected())
	{
		//从像素点坐标转化为瓦片坐标

		Point tileCoord = this->transPoision(position);
		//tileCoord.x = tileCoord.x / 2;
		//tileCoord.y = (_tileMap->getMapSize().height-tileCoord.y)/2;


			//获得瓦片的GID

		const int tileGid = collidable->getTileGIDAt(tileCoord);

		if (tileGid > 0) {


			Value prop = map->getPropertiesForGID(tileGid);

			ValueMap propValueMap = prop.asValueMap();


			std::string collision = propValueMap["Collidable"].asString();

			std::string pass = propValueMap["pass"].asString();

			if (collision == "true") { //碰撞检测成功									

				return;

			}
			if (pass == "true") 
			{
				auto scene = Level01::createScene();
				////预处理
				scene->removeChildByTag(TAG_OF_LEVEL_01);
				//

			  auto stage = Level01::create();

			    auto knight=Knight::create("Heroes/knight1.1.png",this->getKnight());
				auto weapon =Weapon::create("Weapons/weaponGun.png",this->getWeapon());

				knight->setPosition(Vec2(640, 480));
				weapon->setPosition(Vec2(640, 455));

				knight->setTag(TAG_OF_KNIGHT);
				weapon->setTag(TAG_OF_KNIGHT_INITIAL_WEAPON);
				//stage->setTag(TAG_OF_LEVEL_01);

				//设置碰撞性质
				auto heroBody = PhysicsBody::createBox(knight->getContentSize());
				heroBody->setCategoryBitmask(MY_HERO_1);
				heroBody->setCollisionBitmask(MY_HERO_2);
				knight->setPhysicsBody(heroBody);

				auto weaponBody = PhysicsBody::createBox(weapon->getContentSize());
				weaponBody->setCategoryBitmask(WEAPON_1);
				weaponBody->setCollisionBitmask(WEAPON_2);
				weapon->setPhysicsBody(weaponBody);
				////角色的添加
				stage->addChild(knight);
				stage->addChild(weapon);
		        stage->setKnight(knight);
				stage->setWeapon(weapon);
				if (this->getKnightBeenSelected())
				{
					stage->setKnightBeenSelected(true);
				}
				scene->addChild(stage, 0);

				//////////创建InformationBox
				createInformationBox(stage, knight);


				
				auto reScene = TransitionProgressOutIn::create(0.5f, scene);
				Director::getInstance()->replaceScene(reScene);

				//CCLOG("aaaaaaaaaaaaaaa");
			}

		}
		this->getKnight()->setPosition(position);
		Point pos = Point(position.x , position.y - 25);
		this->getWeapon()->setPosition(pos);
	}

}


Point firstStage::transPoision(Point pos)

{
	if (this->getKnightBeenSelected())
	{
		int x = 0.5 * pos.x / map->getTileSize().width;
		int y = ((map->getMapSize().height * map->getTileSize().height) - 0.5 * pos.y) /

		map->getTileSize().height;

		return Point(x, y);
	}

}


void firstStage::screenRoll(Point position)

{
	if (this->getKnightBeenSelected())
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

}