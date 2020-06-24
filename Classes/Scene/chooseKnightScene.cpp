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


	knight= Sprite::create("Heroes/choosingKnight.png");
	knight->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(knight);

	auto knightInfo = Sprite::create("Infos/infoKnight.png");
	knightInfo->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 350));
	this->addChild(knightInfo);

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
	playSound("sound/ClickSound.mp3");
}


void chooseKnightScene::goMenu(Ref *pSender)
{
	auto sc = firstStage::createScene();
//预处理	
	sc->removeChildByTag(TAG_OF_FIRST_STAGE_LAYER);
	
	auto stage = firstStage::create();
	stage->setKnightBeenSelected(true);
	stage->removeChildByTag(TAG_OF_KNIGHT);
// /
	//添加人物与武器,子弹
	auto weapon = Weapon::create("Weapons/weaponGun.png", HERO_ATTACK_LOW, CONSUMPTION_0, HERO_REMOTE, NORMAL);
	auto bullet = Bullet::create("Bullets/bullet4.png", HERO_ATTACK_LOW, ATTACK_FREQUENCY_1, NORMAL);
	auto knight = Knight::create("Heroes/knight1.1.png", weapon);
	
	knight->setPosition(Vec2(640, 480));
	knight->setTag(TAG_OF_KNIGHT);
	

	weapon->setPosition(Vec2(640, 455));
	weapon->setTag(TAG_OF_KNIGHT_INITIAL_WEAPON);

	bullet->setVisible(0);
	///设置碰撞性质
	auto heroBody = PhysicsBody::createBox(knight->getContentSize());
	heroBody->setCategoryBitmask(MY_HERO_1);
	heroBody->setCollisionBitmask(0);
	heroBody->setContactTestBitmask(MY_HERO_2);
	knight->setPhysicsBody(heroBody);

	auto weaponBody = PhysicsBody::createBox(weapon->getContentSize());
	weaponBody->setCategoryBitmask(WEAPON_1);
	weaponBody->setCollisionBitmask(0);
	weaponBody->setContactTestBitmask(WEAPON_2);
	weapon->setPhysicsBody(weaponBody);

	
// //角色的添加
	stage->addChild(knight,1);
	stage->addChild(weapon,20);
	stage->addChild(bullet,20);
	sc->addChild(stage,0);

	stage->setKnight(knight);
	stage->setWeapon(weapon);
	stage->setBullet(bullet);

	stage->setKnightFilename(knight->getActorFilename());
	stage->setWeaponFilename(weapon->getWeaponFilename());
	stage->setBulletFilename(bullet->getBulletFilename());

	////////创建信息栏
	createInformationBox(stage, knight);
	createSkillBox(stage, knight);
	createGoldBox(stage, knight);

// //////场景切换
	auto reScene = TransitionProgressOutIn::create(0.5f, sc);
	Director::getInstance()->replaceScene(reScene);
	playSound("sound/ClickSound.mp3");


}

