//这是安全地图

#include "Scene/startScene.h"
#include "Scene/startScene2.h"
#include "Scene/firstStage.h"
#include"Scene/chooseKnightScene.h"

USING_NS_CC;

Scene* firstStage::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setGravity(Vec2(0.0f, 0.0f));//取消重力场
	auto layer = firstStage::create();
	scene->addChild(layer);
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
	TMXTiledMap* map = TMXTiledMap::create("Backgrounds/safeMap.tmx");//地图
	//改变位置
	
	//获取地图属性
	addChild(map, 0);
	//改变地图大小，参数为倍数
	
	//获取图层属性
	auto sceneLayer = map->getLayer("ground");
	auto layerProperties = sceneLayer->getProperties();
	CCLOG("layer pro:%s", layerProperties["type"].asString().c_str());
	//获取图块属性
	
	
	//获取对象属性
	auto objectGroup = map->getObjectGroup("object");
	auto obj = objectGroup->getObject("knight");

	CCLOG("tile pro:%s", obj["type"].asString().c_str());

	//修改指定区域的颜色
	auto colorObj = objectGroup->getObject("pass");
	auto colorObjX = colorObj["x"].asInt() / 32;
	auto colorObjY = colorObj["y"].asInt() / 32;
	auto colorObjW = colorObj["width"].asInt() / 32;
	auto colorObjH = colorObj["height"].asInt() / 32;
	for (int x = colorObjX; x < colorObjX + colorObjW; x++) {
		for (int y = colorObjY; y < colorObjY + colorObjH; y++) {
			auto sprite = sceneLayer->getTileAt(Vec2(x, map->getMapSize().height - y));
			sprite->setColor(Color3B(225, 0, 0));
		}
	}
	this->setTag(TAG_OF_FIRST_STAGE);

/////////////////////////////////以下为人物属性设置////////////////////////////////////

	auto knight= Knight::create("Heros/unchosenKnight.png", "0", REMOTE);
// //设置碰撞属性
	auto body1 = PhysicsBody::createBox(knight->getContentSize());
	body1->setCategoryBitmask(MY_HERO_1);
	body1->setCollisionBitmask(MY_HERO_2);
	knight->setPhysicsBody(body1);
// //
	knight->setPosition(Vec2(640, 480));
	knight->setTag(TAG_OF_KNIGHT);
	this->addChild(knight);
	Vec2 p=knight->getPosition();

//////////初次设计怪物
	auto monster = Creep::create("Creeps/monster3.png", NORMAL, REMOTE, 5, 3);
// //设置碰撞属性
	auto body2 = PhysicsBody::createBox(knight->getContentSize());
	body2->setCategoryBitmask(ENEMY_1);
	body2->setCollisionBitmask(ENEMY_2);
	monster->setPhysicsBody(body2);
// //
	monster->setTag(TAG_OF_ENEMY_1);
	monster->setPosition(Vec2(900, 400));
	this->addChild(monster);


	this->scheduleUpdate();

	return true;
}


void firstStage::onEnter()//注册监听器
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

/////////////////////////////以下为碰撞监听器/////////////////////////////////////////
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

}


void firstStage::onExit()//注销监听器
{
	Layer::onExit();

}


void firstStage::update(float delta)
{
	if (this->_knightBeenSelected == true)
	{
		int offsetX = 0, offsetY = 0;

		if (keys[EventKeyboard::KeyCode::KEY_D])
		{
			offsetX = 5;
		}
		if (keys[EventKeyboard::KeyCode::KEY_A])
		{
			offsetX = -5;
		}
		if (keys[EventKeyboard::KeyCode::KEY_S])
		{
			offsetY = -5;
		}
		if (keys[EventKeyboard::KeyCode::KEY_W])
		{
			offsetY = 5;
		}

		Node* knight = this->getChildByTag(TAG_OF_KNIGHT);

		auto moveTo = MoveTo::create(0.3, Vec2(knight->getPositionX() + offsetX, knight->getPositionY() + offsetY));

		knight->runAction(moveTo);//角色移动

// //简单的练习尝试
		auto monster = this->getChildByTag(TAG_OF_ENEMY_1);

		Vec2 hero = knight->getPosition();
		Vec2 enemy = monster->getPosition();
		if ((enemy.x >= hero.x - REMOTE) && (enemy.x <= hero.x + REMOTE))
		{
			if ((enemy.y >= hero.y - REMOTE) && (enemy.y <= hero.y + REMOTE))
				this->setInAttackRange(true);
		}

	}
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
		
		Director::getInstance()->replaceScene(reScene);
	}
}


bool firstStage::onTouchBegan(Touch* touch, Event* event)
{
	if (this->getKnightBeenSelected())
	{
		auto knight = getChildByTag(TAG_OF_KNIGHT);
		Vec2 p=knight->getPosition();
		auto bullet = Bullet::create("Bullets/bullet1.png", 3, NORMAL);

/// ///////////设置碰撞属性
		auto body = PhysicsBody::createBox(bullet->getContentSize());
		body->setCategoryBitmask(MY_BULLET_1);//0010
		body->setCollisionBitmask(MY_BULLET_2);//0001
		bullet->setPhysicsBody(body);
		bullet->setPosition(Vec2(p));
		this->addChild(bullet);
		
/// ///////////////以下为攻击范围内无敌人的攻击方式——随机向某个方向攻击
		if (!this->getInAttackRange())//不在攻击范围内
		{
			float tempAngle = CCRANDOM_0_1() * 2 * PI;
			float x = 250 * cos(tempAngle);
			float y = 250 * sin(tempAngle);
			bullet->runAction(Sequence::create(MoveBy::create(0.5f, Vec2(x, y)), CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, bullet)), NULL));
		}
		else//在攻击范围内
		{
			auto enemy = getChildByTag(TAG_OF_ENEMY_1);
			Vec2 p = enemy->getPosition();
			bullet->runAction(Sequence::create(MoveTo::create(0.5f,p), CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, bullet)), NULL));
			this->setInAttackRange(false);
		}
		return false;
	}
	return false;
}


void firstStage::removeFromParent(Node* bullet)//删除子弹的回调函数
{
	bullet->removeFromParent();
}