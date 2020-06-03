//这是安全地图

#include "StartScene.h"
#include "StartScene2.h"
#include "firstStage.h"
#include "SimpleAudioEngine.h"
#include "SoundAndMusic.h"

using namespace CocosDenshion;
USING_NS_CC;

/*Scene* firstMap::createScene() {
	Scene* scene = Scene::create();
	firstMap* layer = firstMap::create();
	scene->addChild(layer);
	return scene;
}
bool firstMap::init() {
	TMXTiledMap* tmx = TMXTiledMap::create("firstMap.tmx");//地图
	addChild(tmx);
	return true;
}*/
/*Scene* HelloWorld::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	auto layer = HelloWorld::create();
	scene->addChild(layer);
	return scene;
}*/

Scene* firstStage::createScene()
{

	return firstStage::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}



// on "init" you need to initialize your instance
bool firstStage::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	TMXTiledMap* map = TMXTiledMap::create("safeMap.tmx");//地图
	//改变位置
	/*tmx->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	CCLOG("%f,%f", visibleSize.width / 2, visibleSize.height / 2);
	tmx->setAnchorPoint(Vec2(0.5, 0.5));
	tmx->setScale(Director::getInstance()->getContentScaleFactor());*/
	//获取地图属性
	addChild(map, 0);
	//改变地图大小，参数为倍数
	//map->setScale(1.5);
	//auto mapProperties = map->getProperties();
	//auto str = mapProperties["type"].asString();
	//CCLOG("tmx pro:%s", str.c_str());
	//获取图层属性
	auto sceneLayer = map->getLayer("ground");
	auto layerProperties = sceneLayer->getProperties();
	CCLOG("layer pro:%s", layerProperties["type"].asString().c_str());
	//获取图块属性
	//auto tilePro = map->getPropertiesForGID(1).asValueMap();
	//CCLOG("tile pro:%s", tilePro["type"].asString().c_str());
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
	

	auto knight1 = Sprite::create("knight1.png");

	knight1->setPosition(Vec2(640, 480));

	knight1->setTag(2);

	this->addChild(knight1, 2);
		
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

	return true;
}
/*
void HelloWorld::onEnter() {


	addEdges();

}

void HelloWorld::addEdges() {
	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto body = PhysicsBody::createEdgeBox(visibleSize,PHYSICSBODY_MATERIAL_DEFAULT,3);

	auto edgeShape = Node::create();

	edgeShape->setPhysicsBody(body);
	edgeShape->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(edgeShape);

}
*/





void firstStage::update(float delta)
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
	Node* knight = this->getChildByTag(2);

	

	//Node* wall = this->getChildByTag(4);

	auto moveTo = MoveTo::create(0.3, Vec2(knight->getPositionX() + offsetX, knight->getPositionY() + offsetY));

	//if ()
	//{
		knight->runAction(moveTo);
	//}

	//Node* door = this->getChildByTag(1);

	/*if (door->getBoundingBox().containsPoint(Vec2(640, 480)))
	{
		Director::getInstance()->replaceScene(startScene::createScene());
	}*/

}

///////////////////////////////////////////////////////////////////////////////
void firstStage::onEnter()
{
	Scene::onEnter();
	log("firstStage onEnter");
	//playMusic("sound/SafeMapBGM.mp3", true);
	//SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/SafeMapBGM.mp3");
}

void firstStage::onEnterTransitionDidFinish()
{
	Scene::onEnterTransitionDidFinish();
	log("firstStage onEnterTransitionDidFinish");
	playMusic("sound/SafeMapBGM.mp3",true);
	//SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/SafeMapBGM.mp3");
}

void firstStage::onExit()
{
	Scene::onExit();
	log("firstStage onExit");
}

void firstStage::onExitTransitionDidStart()
{
	Scene::onExitTransitionDidStart();
	log("firstStage onExitTransitionDidStart");
}

void firstStage::cleanup()
{
	Scene::cleanup();
	log("firstStage cleanup");
	//playMusic("sound/SafeMapBGM.mp3", true, 1);
}

///////////////////////////////////////////////////////////////////////////
