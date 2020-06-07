#include"Scene/chooseKnightScene.h"

Scene* chooseKnightScene::createScene()
{
	return chooseKnightScene::create();
}


bool chooseKnightScene::init()
{
	if (!Scene::init())
		return false;

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto bg = Sprite::create("Backgrounds/chooseKnightScene.png");
	bg->setPosition((Vec2(visibleSize.width / 2, visibleSize.height / 2)));
	this->addChild(bg);


	knight= Sprite::create("Heros/choosingKnight.png");
	knight->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(knight);

	auto backMenuItem = MenuItemImage::create("Buttons/buttonExit.png", "Buttons/buttonExitClicked.png", CC_CALLBACK_1(chooseKnightScene::backMenu, this));
	backMenuItem->setPosition(Director::getInstance()->convertToGL(Vec2(120, 100)));
	auto goMenuItem = MenuItemImage::create("Buttons/buttonContinue.png", "Buttons/buttonContinueClicked.png", CC_CALLBACK_1(chooseKnightScene::goMenu, this));
	goMenuItem->setPosition(visibleSize.width / 2, 100);
	Menu* mn = Menu::create(backMenuItem, goMenuItem, NULL);
	mn->setPosition(Vec2::ZERO);
	this->addChild(mn);
	
	return true;

}

void chooseKnightScene::backMenu(Ref* pSender)
{
	auto sc = firstStage::createScene();
	
	auto reScene = TransitionPageTurn::create(0.5f, sc,true);
	Director::getInstance()->replaceScene(reScene);
}


void chooseKnightScene::goMenu(Ref *pSender)
{
	auto sc = firstStage::createScene();
	
	sc->removeChildByTag(TAG_OF_KNIGHT);
	sc->removeChildByTag(TAG_OF_FIRST_STAGE);
	
	auto stage = firstStage::create();
	stage->setKnightBeenSelected(true);
	stage->setTag(TAG_OF_FIRST_STAGE);
	stage->removeChildByTag(TAG_OF_KNIGHT);

	auto knight= Knight::create("Heros/knight.png", "0", REMOTE);
///ÉèÖÃÅö×²ÐÔÖÊ
	auto body = PhysicsBody::createBox(knight->getContentSize());
	body->setCategoryBitmask(0x01);
	body->setCollisionBitmask(0x02);
	knight->setPhysicsBody(body);

//////
	knight->setPosition(Vec2(640, 480));
	knight->setTag(TAG_OF_KNIGHT);

	stage->addChild(knight);
	sc->addChild(stage);
	
	auto reScene = TransitionProgressOutIn::create(0.5f, sc);
	Director::getInstance()->replaceScene(reScene);



}


