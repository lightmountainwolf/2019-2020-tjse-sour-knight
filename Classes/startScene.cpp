#include "startScene.h"

USING_NS_CC;

Scene* startScene::createScene()
{
	Scene* scene = Scene::create();
	startScene* layer = startScene::create();
	scene->addChild(layer);
	return scene;
}


bool startScene::init()
{

	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	auto label = Label::createWithTTF("First Scene", "fonts/Marker Felt.ttf", 28);
	
		// position the label on the center of the screen
		label->setPosition(Vec2(origin.x + visibleSize.width / 2,
			origin.y + visibleSize.height - label->getContentSize().height));

		// add the label as a child to this layer
		this->addChild(label, 1);
	

	auto sprite = Sprite::create("img.jpg");
	
		sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

		this->addChild(sprite, 0);
	



	return true;
}

