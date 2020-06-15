#include"Function/CommonFunction.h"


//1.informationBox的建立（左上角能量槽）
//参数介绍：layer:需要将这一信息栏放在哪个场景中，hero:关于谁的信息
 void createInformationBox(Layer* layer, const Hero* hero)
{
	 Scene* scene=static_cast<Scene*>(layer->getParent());
	auto informationBox = Sprite::create("Infos/informationBox.png");
	informationBox->setPosition(Vec2(150, 890));
	int maxHP = HP_OF_KNIGHT, maxArmor = ARMOR_OF_KNIGHT, maxMP = MP_OF_KNIGHT;

	//设置进度条百分比
	float mp = hero->getMP();
	float percentMP = mp / maxMP * 100;

	float hp = hero->getHP();
	float percentHP = hp / maxHP * 100;

	float Armor = hero->getArmor();
	float percentArmor = Armor / maxArmor * 100;

	//HP
	auto HP = LoadingBar::create("Infos/HP.png");
	HP->setPosition(Vec2(167, 925));
	HP->setDirection(LoadingBar::Direction::LEFT);
	HP->setPercent(percentHP);
	HP->setTag(TAG_OF_HP_BAR);

	auto labelHP = Label::create("labelHP", "fonts/arial", 30);
	labelHP->setString(StringUtils::format("%d/%d", hero->getHP(), maxHP));
	labelHP->setPosition(Vec2(167, 925));
	labelHP->setColor(Color3B(255, 255, 0));
	labelHP->setTag(TAG_OF_LABEL_HP);

	//armor
	auto armor = LoadingBar::create("Infos/Armor.png");
	armor->setPosition(Vec2(167, 894));
	armor->setDirection(LoadingBar::Direction::LEFT);
	armor->setPercent(percentArmor);
	armor->setTag(TAG_OF_ARMOR_BAR);

	auto labelArmor = Label::create("labelArmor", "fonts/arial", 30);
	labelArmor->setString(StringUtils::format("%d/%d", hero->getArmor(), maxArmor));
	labelArmor->setPosition(Vec2(167, 894));
	labelArmor->setColor(Color3B(255, 255, 0));
	labelArmor->setTag(TAG_OF_LABEL_ARMOR);
	//MP
	auto MP = LoadingBar::create("Infos/MP.png");
	MP->setPosition(Vec2(167, 860));
	MP->setDirection(LoadingBar::Direction::LEFT);
	MP->setPercent(percentMP);
	MP->setTag(TAG_OF_MP_BAR);

	auto labelMP = Label::create("labelMP", "fonts/arial", 30);
	labelMP->setString(StringUtils::format("%d/%d", hero->getMP(), maxMP));
	labelMP->setPosition(Vec2(167, 860));
	labelMP->setColor(Color3B(255, 255, 0));
	labelMP->setTag(TAG_OF_LABEL_MP);

	scene->addChild(informationBox,1);
	scene->addChild(HP,1);
	scene->addChild(labelHP,1);
	scene->addChild(MP,1);
	scene->addChild(labelMP,1);
	scene->addChild(armor,1);
	scene->addChild(labelArmor,1);
}

//2.informationBox的更新（蓝值的更新）
//参数介绍：layer:需要将这一信息栏放在哪个场景中，hero:关于谁的信息

 void updateInformationMP(Layer* layer, Hero* hero)
 {
	 Scene* scene = static_cast<Scene*>(layer->getParent());
	 hero->consumeMP();
	 scene->removeChildByTag(TAG_OF_MP_BAR);
	 scene->removeChildByTag(TAG_OF_LABEL_MP);

	 int  maxMP = MP_OF_KNIGHT;
	 float mp = hero->getMP();
	 float percent = mp / maxMP * 100;

	 //MP
	 auto MP = LoadingBar::create("Infos/MP.png");
	 MP->setPosition(Vec2(167, 860));
	 MP->setDirection(LoadingBar::Direction::LEFT);
	 MP->setPercent(percent);
	 MP->setTag(TAG_OF_MP_BAR);

	 auto labelMP = Label::create("labelMP", "fonts/arial", 30);
	 labelMP->setString(StringUtils::format("%d/%d", hero->getMP(), maxMP));
	 labelMP->setPosition(Vec2(167, 860));
	 labelMP->setColor(Color3B(255, 255, 0));
	 labelMP->setTag(TAG_OF_LABEL_MP);

	 scene->addChild(MP,1);
	 scene->addChild(labelMP,1);
 }
	