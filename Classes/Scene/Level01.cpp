#include "Scene/Level01.h"
#include "Scene/Level02.h"

Scene* Level01::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setGravity(Vec2(0.0f, 0.0f));//取消重力场
	
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

	smallMap = Sprite::create("Props/smallMap1.png");
	smallK = Sprite::create("Props/star.png");

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
	addChild(map, 0);


	TMXObjectGroup* group = map->getObjectGroup("obj");
	ValueMap spawnPoint = group->getObject("player");
	float x = spawnPoint["x"].asFloat();
	float y = spawnPoint["y"].asFloat();

// //////////////////小地图的设置
	smallK->setPosition(x + 2600, y + 2600);
	smallMap->setPosition(x + 1500, y + 1500);
	addChild(smallMap);
	addChild(smallK);

	collidable = map->getLayer("collidable");
	collidable->setVisible(false);
	this->setTag(TAG_OF_LEVEL_01);

	ValueMap spawnPoint2 = group->getObject("sculpture");
	
	spawnPoint2 = group->getObject("theS");
	s = Sprite::create("Statues/statueWizard.png");
	s->setPosition(2 * spawnPoint2["x"].asFloat(), 2 * spawnPoint2["y"].asFloat());
	addChild(s);

	s = Sprite::create("Props/nine1.png");
	s->setPosition(2 * spawnPoint2["x"].asFloat(), 2 * spawnPoint2["y"].asFloat());
	addChild(s);
	s->setVisible(false);

	////////////////////////
//可以被打掉的木块的设置
	Creep* wood;
	ValueMap mPoint;
	std::string woods[12] = { "w1","w2","w3","w4" ,"w5","w6","w7","w8","w9","w10","w11","w12" };
	for (int i = 0; i < 12; i++) {
		wood = Creep::create("Creeps/wood.png", NORMAL, ENEMY_REMOTE, 1, MONSTER_ATTACK_LOW, true);
		mPoint = group->getObject(woods[i]);

		auto bodyW = PhysicsBody::createBox(wood->getContentSize());
		bodyW->setCategoryBitmask(ENEMY_1);
		bodyW->setCollisionBitmask(0);
		bodyW->setContactTestBitmask(ENEMY_2);
		wood->setPhysicsBody(bodyW);

		wood->setPosition(2 * mPoint["x"].asFloat(), 2 * mPoint["y"].asFloat());
		woodsVec.pushBack(wood);

		woodsVec.at(i)->setScale(2);

		this->addChild(woodsVec.at(i), 100);

		woodsVec.at(i)->setVisible(true);

		woodsVec.at(i)->setTag(85 + i);
	}


	/////////

	//宝箱的设置
	///////////////////////////////////////
	ValueMap spawnPoint1;
	Box* box;
	std::string boxNum[4] = { "box0","box1","box2","box3" };//box3是装武器的
	for (int i = 0; i < 4; i++) {
		spawnPoint1 = group->getObject(boxNum[i]);
		box = Box::create("Props/box.png",0,0,0,0, "Weapons/weaponBasketball.png");
		boxVec.pushBack(box);
		boxVec.at(i)->setPosition(2 * spawnPoint1["x"].asFloat(), 2 * spawnPoint1["y"].asFloat());
		boxPositionVec.push_back(Vec2(2 * spawnPoint1["x"].asFloat(), 2 * spawnPoint1["y"].asFloat()));
		addChild(boxVec.at(i));

		boxVec.at(i)->setVisible(false);
	}
	boxVec.at(3)->setVisible(true);
	///////////////////////////////////////////////////以下为小怪的设置
		//生成小怪

	char monsters[5][4] = { "m1","m2" ,"m3" ,"m4" ,"m5" };

	char monstersGroup2[5][4] = { "m6","m7" ,"m8" ,"m9" ,"m10" };

	char monstersGroup1[5][4] = { "m11","m12" ,"m13" ,"m14" ,"m15" };

	createMonster(monsters, "Creeps/monster3.png", 0);
	createMonster(monstersGroup2, "Creeps/monster2.png", 5);
	createMonster(monstersGroup1, "Creeps/monster1.png", 10);
	createMonster(monsters, "Creeps/monster2.png", 15);
	createMonster(monstersGroup2, "Creeps/monster1.png", 20);

	for (int i = 0; i < 15; i++)
	{
		creepDieArr[i] = false;
	}

	for (int j = 0; j < 3; j++)
	{
		littleMapClear[j] = 0;
		littleMapWave[j] = 0;
	}
	deadCreeps = 0;
	allClear = false;
//////////////////////////////////////插入传送门
	ValueMap doorPoint = group->getObject("transfer");

	float xDoor = 2 * doorPoint["x"].asFloat();

	float yDoor = 2 * doorPoint["y"].asFloat();

	auto door = setDoor(xDoor, yDoor, 200);
	door->setTag(TAG_OG_SAFEMAP_DOOR);
	this->addChild(door);
	door->setVisible(false);
// //////////////道具、武器的初始化
	initWeapon();
	initProps();
	
	
	// ////////////////////////////////////////////////////////////////////uodate相关函数
	this->schedule(schedule_selector(Level01::enemyAttackUpdate), 1.0f, kRepeatForever, 0);//敌人的攻击
	this->schedule(schedule_selector(Level01::enemyMoveUpdate), 2.0f, -1, 2);//敌人的移动
	this->schedule(schedule_selector(Level01::armorRecoverUpdate), 2.0f, kRepeatForever, 0);//护甲的恢复
	this->schedule(schedule_selector(Level01::heroDieUpdate), 3.0f, kRepeatForever, 2.0f);
	this->scheduleUpdate();

	return true;

}

void Level01::createMonster(char arr[5][4], const std::string& location, int num)
{
	int tagArr[5] = { 55 + num,56 + num,57 + num,58 + num,59 + num };
	for (int i = 0; i < 5; i++)
	{
		TMXObjectGroup* group = map->getObjectGroup("obj");

		ValueMap mPoint = group->getObject(arr[i]);

		float x = 2 * mPoint["x"].asFloat();

		float y = 2 * mPoint["y"].asFloat();

		Creep* monsterTemp;
		if (num / 5 == 0)
			monsterTemp = Creep::create(location, NORMAL, ENEMY_REMOTE, CREEP_HP_1, MONSTER_ATTACK_LOW,true);
		else if (num / 5 == 1)
			monsterTemp = Creep::create(location, NORMAL, ENEMY_MELEE, CREEP_HP_2, MONSTER_ATTACK_MEDIUM,true);
		else if (num / 5 == 2)
			monsterTemp = Creep::create(location, NORMAL, ENEMY_REMOTE, CREEP_HP_2, MONSTER_ATTACK_LOW,true);
		else if (num / 5 == 3)
			monsterTemp = Creep::create(location, NORMAL, ENEMY_MELEE, CREEP_HP_2, MONSTER_ATTACK_MEDIUM ,false);
		else if (num / 5 == 4)
			monsterTemp = Creep::create(location, NORMAL, ENEMY_REMOTE, CREEP_HP_1, MONSTER_ATTACK_LOW, false);

		auto body = PhysicsBody::createBox(monsterTemp->getContentSize()*1.5);
		body->setCategoryBitmask(ENEMY_1);
		body->setCollisionBitmask(0);
		body->setContactTestBitmask(ENEMY_2);
		monsterTemp->setPhysicsBody(body);


		monsterTemp->setPosition(x, y);
		monsterTemp->setTag(tagArr[i]);
		this->addChild(monsterTemp);

		if (!monsterTemp->getActive())
		{
			monsterTemp->setVisible(false);

		}
		creepsVec.pushBack(monsterTemp);
	}
}

void Level01::creepDie(Creep* creep)
{
	int tag = creep->getTag();

	if ((tag >= TAG_OF_MONSTER_1) && (tag <= TAG_OF_MONSTER_5))
	{
		creep->initWithFile("Creeps/monster3Dead.png");
		creepDieArr[tag - 55] = true;
		littleMapClear[0]++;
		deadCreep[0]++;
		deadCreeps++;
	}
	else if ((tag >= TAG_OF_MONSTER_1 + 5) && (tag <= TAG_OF_MONSTER_5 + 5))
	{
		creep->initWithFile("Creeps/monster2Dead.png");
		creepDieArr[tag - 55] = true;
		littleMapClear[1]++;
		deadCreep[1]++;
		deadCreeps++;

	}
	else if ((tag >= TAG_OF_MONSTER_1 + 10) && (tag <= TAG_OF_MONSTER_5 + 10))
	{
		creep->initWithFile("Creeps/monster1Dead.png");
		creepDieArr[tag - 55] = true;
		littleMapClear[2]++;
		deadCreep[2]++;
		deadCreeps++;
	}
	else if ((tag >= TAG_OF_MONSTER_1 + 15) && (tag <= TAG_OF_MONSTER_5 + 15))
	{
		creep->initWithFile("Creeps/monster2Dead.png");
		creepDieArr[tag - 55] = true;
		littleMapClear[0]++;
		deadCreep[0]++;
		deadCreeps++;
	}
	else if ((tag >= TAG_OF_MONSTER_1 + 20) && (tag <= TAG_OF_MONSTER_5 + 20))
	{
		creep->initWithFile("Creeps/monster1Dead.png");
		creepDieArr[tag - 55] = true;
		littleMapClear[1]++;
		deadCreep[1]++;
		deadCreeps++;
	}
	for (int i = 0; i < 2; i++)
	{
		if (littleMapClear[i] >= 5)
		{
			littleMapClear[i] = 0;
			for (int j = 15 + i * 5; j < 20 + i * 5; j++)
			{
				Creep* monster = creepsVec.at(j);
				monster->setActive(true);
				monster->setVisible(true);
			}
			if (littleMapWave[i] == 0)
			{
				littleMapWave[i]++;
			}

		}
	}
	if (deadCreep[0] == 10) {

		boxVec.at(0)->setVisible(true);
		boxVec.at(0)->setOpen(true);

	}
	if (deadCreep[1] == 10) {

		boxVec.at(1)->setVisible(true);
		boxVec.at(1)->setOpen(true);

	}
	if (deadCreep[2] == 5) {

		boxVec.at(2)->setVisible(true);
		boxVec.at(2)->setOpen(true);
	}
	if (deadCreeps >= 25)
	{
		allClear = true;
		auto door = this->getChildByTag(TAG_OG_SAFEMAP_DOOR);
		door->setVisible(true);
	}

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

	/////////////////////////////以下为碰撞监听器/////////////////////////////////////////
	auto monsterListener = EventListenerPhysicsContact::create();
	monsterListener->onContactBegin = [&](PhysicsContact& contact)
	{
		auto bullet = static_cast<Bullet*>(contact.getShapeA()->getBody()->getNode());
		auto monster = static_cast<Creep*>(contact.getShapeB()->getBody()->getNode());
		if (bullet && bullet->getTag() == TAG_OF_BULLET_01 && monster && 
		(monster->getTag() >= TAG_OF_MONSTER_1) && (monster->getTag() <= MAX_TAG_OF_MONSTER)&&(monster->getActive()))
		{
			if (!monster->getAlreadyDead())
			{
				monster->setColor(Color3B::RED);
				monster->takeDamage(bullet);
				//DEBUFF
				if (bullet->getDebuffType() == BURN)
				{
					float seed = CCRANDOM_0_1();
					if (seed >= 0.5)
					{
						monster->setReleaseDebuff(BURN);
						monster->setColor(Color3B::RED);
					}
				}
				else if (bullet->getDebuffType() == FROST)
				{
					float seed = CCRANDOM_0_1();
					if (seed >= 0.5)
					{
						monster->setReleaseDebuff(FROST);
						monster->setColor(Color3B::BLUE);
					}
				}
				bullet->removeFromParent();

				if (monster->getAlreadyDead())
				{
					creepDie(monster);
				}
			}
		}

		return true;
	};
	monsterListener->onContactPreSolve = [](PhysicsContact& contact, PhysicsContactPreSolve& solve)
	{

		return true;
	};
	monsterListener->onContactPostSolve = [](PhysicsContact& contact, const PhysicsContactPostSolve& solve)
	{
	};

	monsterListener->onContactSeparate = [&](PhysicsContact& contact)
	{
		auto monster = (Creep*)contact.getShapeB()->getBody()->getNode();
		if (monster && (monster->getTag() >= TAG_OF_MONSTER_1) && (monster->getTag() <= MAX_TAG_OF_MONSTER))
			monster->setColor(Color3B::WHITE);
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(monsterListener, 1);
	/////////////
	auto openBoxListener = EventListenerKeyboard::create();

	openBoxListener->onKeyPressed = [=](EventKeyboard::KeyCode code, Event* e)
	{
		keys[code] = true;
	};

	openBoxListener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event)
	{
		keys[keyCode] = false;
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(openBoxListener, this);

	///////////
	// ///////////////////////////////////////////////////////////第二个碰撞监听器

	auto heroListener = EventListenerPhysicsContact::create();
	heroListener->onContactBegin = [&](PhysicsContact& contact)
	{
		auto bullet = static_cast<Bullet*>(contact.getShapeA()->getBody()->getNode());
		auto hero = static_cast<Hero*>(contact.getShapeB()->getBody()->getNode());
		if (bullet && bullet->getTag() == TAG_OF_BULLET_01 && hero && hero->getTag() == TAG_OF_KNIGHT)
		{
			if (!hero->getAlreadyDead())
			{
				hero->setColor(Color3B::RED);
				;
				hero->takeDamage(bullet);
				bullet->removeFromParent();

				if (hero->getAlreadyDead())
				{
					hero->initWithFile("Heroes/knight1.1Dead.png");
					hero->stopAllActions();
				}

			}
		}

		return true;
	};
	heroListener->onContactPreSolve = [&](PhysicsContact& contact, PhysicsContactPreSolve& solve)
	{

		return true;
	};
	heroListener->onContactPostSolve = [&](PhysicsContact& contact, const PhysicsContactPostSolve& solve)
	{

	};

	heroListener->onContactSeparate = [&](PhysicsContact& contact)
	{
		auto hero = (Hero*)contact.getShapeB()->getBody()->getNode();
		if (this->getKnightBeenSelected())
		{
			if (hero && (hero->getTag() == this->getKnight()->getTag()))
				hero->setColor(Color3B::WHITE);
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(heroListener, 1);

	// //////////////////////////////////////////////////////////////////////////////////////////
	this->listenerVec.pushBack(knightMoveListener);
	this->listenerVec.pushBack(monsterListener);
	this->listenerVec.pushBack(heroListener);
	/// ///////////////////////////////////////////////////////////////////////
	playMusic("sound/FightMapCaveBGM.mp3", true);
}

void Level01::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();

}

void Level01::onExitTransitionDidStart()
{
	Layer::onExitTransitionDidStart();

}

void Level01::onExit()//注销监听器
{
	Layer::onExit();
	for (auto listener : listenerVec)
		Director::getInstance()->getEventDispatcher()->removeEventListener(listener);

}

void Level01::cleanup()
{
	Layer::cleanup();

}

void Level01::menuPauseCallback(cocos2d::Ref* pSender)//暂停按钮的回调
{
	auto scene = Pause::createScene();
	Director::getInstance()->pushScene(scene);
	playSound("sound/ClickSound.mp3");
}

bool Level01::onTouchBegan(Touch* touch, Event* event)//鼠标点击，骑士攻击
{
	Vec2 position = convertTouchToNodeSpace(touch);
	if ((this->getKnightBeenSelected()) && (!this->getKnight()->getAlreadyDead()))//骑士被选择并且没有死
	{
		if ((this->getKnight()->getMP())||((!this->getKnight()->getMP())&&(!this->getWeapon()->getMPConsuming())))//如果蓝未耗完或蓝已耗完但武器不耗蓝
		{
			if (this->getKnight()->getAttackMode() <= HERO_MELEE_4)//近程攻击
			{
				if (!attackTowardsTarget(this->getKnight()))
				{
					attackMelee(this->getKnight());
				}
			}
			else attackRemotely(position,this->getKnight());
		return false;	
		}
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
		updateInformationArmor(this, this->getKnight());
		updateInformationHP(this, this->getKnight());
		this->getKnight()->updateSkill();
		updateSkillBox(this, this->getKnight());
		if ((!this->getKnight()->getAlreadyDead()))
		{
			knightMove();
		}
	}
	//打破木箱
	for (int i = 0; i < 12; i++) {
		if (woodsVec.at(i)->getAlreadyDead() && f[i] == 0) {
			f[i] = 1;
			woodsVec.at(i)->setVisible(false);
			//collidable->setTileGID(0, transPoision(p));
			collidable->removeTileAt(transPoision(woodsVec.at(i)->getPosition()));
		}
	}
}

void Level01::heroDieUpdate(float delta)
{
	if (this->getKnightBeenSelected() && this->getKnight()->getAlreadyDead())
	{
		auto deadScene = Dead::createScene();
		auto reScene = CCTransitionMoveInT::create(0.5f, deadScene);
		Director::getInstance()->replaceScene(reScene);
	}
}

void Level01::enemyAttackUpdate(float delta)
{
	int tileGid;
	float relativeX, relativeY, relativeR, searchX, searchY;
	float cosAlpha, sinAlpha;//角度
	bool hit;
	hit = false;
	Vec2 hero;
	if ((this->getKnightBeenSelected()) && (!this->getKnight()->getAlreadyDead()))
	{
		hero = this->getKnight()->getPosition();
		for (const auto& monster : this->creepsVec)
		{
			if ((!monster->getAlreadyDead()) && (monster->getActive()))
			{
				if (monster->getAttackMode() >=ENEMY_REMOTE)
				{
					Vec2 enemy = monster->getPosition();
					if ((enemy.x >= hero.x - ENEMY_REMOTE) && (enemy.x <= hero.x + ENEMY_REMOTE) &&
						(enemy.y >= hero.y - ENEMY_REMOTE) && (enemy.y <= hero.y + ENEMY_REMOTE))
					{
						hit = false;
						relativeX = hero.x - enemy.x;
						relativeY = hero.y - enemy.y;
						relativeR = sqrt(relativeX * relativeX + relativeY * relativeY);
						cosAlpha = relativeX / relativeR;
						sinAlpha = relativeY / relativeR;
						searchX = enemy.x;
						searchY = enemy.y;
						while (relativeR > 0)
						{
							relativeR -= 20;
							searchX += 20 * cosAlpha;
							searchY += 20 * sinAlpha;
							int xxx = 0.5 * searchX / map->getTileSize().width;
							int yyy = ((map->getMapSize().height * map->getTileSize().height) - 0.5 * searchY) / map->getTileSize().height;

							Point posAfter = Point(xxx, yyy);

							tileGid = collidable->getTileGIDAt(posAfter);
							if (tileGid > 0)
							{
								Value prop = map->getPropertiesForGID(tileGid);

								ValueMap propValueMap = prop.asValueMap();

								std::string collision = propValueMap["Collidable"].asString();

								if (collision == "true")
								{
									hit = true;
									break;
								}
							}
						}
						this->setInAttackRange(true);
						auto enemyBullet = Bullet::create("Bullets/bullet1.png",monster->getAttack(), ATTACK_FREQUENCY_1, NORMAL);
						enemyBullet->setTag(TAG_OF_BULLET_01);

						auto Ebody = PhysicsBody::createBox(enemyBullet->getContentSize());
						Ebody->setCategoryBitmask(ENEMY_BULLET_1);//0010
						Ebody->setCollisionBitmask(0);
						Ebody->setContactTestBitmask(ENEMY_BULLET_2);
						enemyBullet->setPhysicsBody(Ebody);
						enemyBullet->setPosition(enemy);
						enemyBullet->runAction(Sequence::create(MoveTo::create(0.4f, Vec2(searchX, searchY)), CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, enemyBullet)), NULL));
						this->addChild(enemyBullet);
					}
				}
				else if (monster->getAttackMode() <=ENEMY_MELEE)
				{
					Vec2 enemy = monster->getPosition();
					if ((enemy.x >= hero.x - ENEMY_MELEE) && (enemy.x <= hero.x + ENEMY_MELEE) &&
						(enemy.y >= hero.y - ENEMY_MELEE) && (enemy.y <= hero.y + ENEMY_MELEE))
					{
						this->setInAttackRange(true);
						//this->setBeenAttacked(true);
						auto enemyBullet = Bullet::create("Bullets/bullet1.png", monster->getAttack(), ATTACK_FREQUENCY_1, NORMAL);
						enemyBullet->setTag(TAG_OF_BULLET_01);

						auto Ebody = PhysicsBody::createBox(enemyBullet->getContentSize());
						Ebody->setCategoryBitmask(ENEMY_BULLET_1);//0010
						Ebody->setCollisionBitmask(0);
						Ebody->setContactTestBitmask(ENEMY_BULLET_2);
						enemyBullet->setPhysicsBody(Ebody);


						enemyBullet->setPosition(enemy);
						enemyBullet->runAction(Sequence::create(MoveTo::create(0.4f, hero), CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, enemyBullet)), NULL));

						this->addChild(enemyBullet);
						enemyBullet->setVisible(false);
					}
				}
			}
		}
	}
}

void Level01::knightMove()//放置在update里的函数，实现骑士角色的移动
{
	Point playerPos = this->getKnight()->getPosition();

	if (keys[EventKeyboard::KeyCode::KEY_D])
	{
		playerPos.x += map->getTileSize().width /setV;

		this->getKnight()->runAction(FlipX::create(false));
		this->getWeapon()->runAction(FlipX::create(false));

	}
	if (keys[EventKeyboard::KeyCode::KEY_A])
	{
		playerPos.x -= map->getTileSize().width / setV;

		this->getKnight()->runAction(FlipX::create(true));
		this->getWeapon()->runAction(FlipX::create(true));

	}
	if (keys[EventKeyboard::KeyCode::KEY_S])
	{
		playerPos.y -= map->getTileSize().height / setV;

	}
	if (keys[EventKeyboard::KeyCode::KEY_W])
	{
		playerPos.y += map->getTileSize().height / setV;

	}
	if (keys[EventKeyboard::KeyCode::KEY_Q])
	{
		collectProps();
	}
	if (keys[EventKeyboard::KeyCode::KEY_R])
	{
		Vec2 hero;
		if (this->getKnightBeenSelected())
		{
			hero = this->getKnight()->getPosition();
			for (int i = 0; i < weaponVec.size(); i++)
			{
				Vec2 weapon = weaponVec.at(i)->getPosition();
				if (weaponVec.at(i) && (weapon.x) && (weapon.y)
					&& (abs(hero.x - weapon.x) <= 60) && (abs(hero.y - weapon.y) <= 60) && (weaponVec.at(i) != this->getWeapon()))
				{

					this->setWeapon(weaponVec.at(i));
					this->setWeaponFilename(weaponVec.at(i)->getWeaponFilename());
					this->setBullet(bulletVec.at(i));
					this->setBulletFilename(bulletVec.at(i)->getBulletFilename());
					this->getKnight()->changeWeapon(weaponVec.at(i));
					this->getWeapon()->setPosition(hero.x, hero.y - 25);
					this->getBullet()->setScale(0);
					break;
				}

			}
		}

	}
	if (keys[EventKeyboard::KeyCode::KEY_E])
	{
		this->getKnight()->releaseSkill();
		updateSkillBox(this, this->getKnight());
		updateInformationMP(this, this->getKnight());
	}
	this->setPlayerPosition(playerPos);
	this->screenRoll(playerPos);

}

void Level01::attackMelee(Hero* hero)//没有攻击目标时的随机攻击
{
	
	this->getKnight()->consumeMP();
	float tempAngle = CCRANDOM_0_1() * 2 * PI;
	float x = this->getKnight()->getAttackRadius() * cos(tempAngle);
	float y = this->getKnight()->getAttackRadius() * sin(tempAngle);
	for (int i = 0; i < this->getBullet()->getAttackFrequency(); i++)
	{
		auto bullet = Bullet::create(this->getBulletFilename(), this->getBullet());
		Vec2 p = this->getWeapon()->getPosition();
		bullet->setTag(TAG_OF_BULLET_01);
		bullet->setPosition(p);	
		bullet->setVisible(false);

		auto weaponcache = SpriteFrameCache::getInstance();
		// //
		std::string filename = this->getWeaponFilename();
		for (int j = 0; j< 4;j++)
		filename.pop_back();
		filename += "Attack.plist";
		weaponcache->addSpriteFramesWithFile(filename);
		// //
		Vector<SpriteFrame*>vec;
		char name[50] = { 0 };
		std::string file = this->getWeaponFilename();
		file.erase(0, 8);
		for (int i = 0; i < 6; i++)
		{
			sprintf(name, "%sAttack%04d",file.c_str() ,i);
			vec.pushBack(weaponcache->getSpriteFrameByName(name));
		}
		Animation* weaponAnimation = Animation::createWithSpriteFrames(vec, 0.01f);
		weaponAnimation->setRestoreOriginalFrame(true);
		Animate* weaponAnimate = Animate::create(weaponAnimation);
		this->getWeapon()->runAction(weaponAnimate);
		//设置碰撞属性
		auto body = PhysicsBody::createBox(bullet->getContentSize());
		body->setCategoryBitmask(MY_BULLET_1);//0010
		body->setCollisionBitmask(0);
		body->setContactTestBitmask(MY_BULLET_2);
		bullet->setPhysicsBody(body);
		this->addChild(bullet);
		bullet->runAction(Sequence::create(MoveBy::create(0.3f * (i + 1), Vec2(x, y)), CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, bullet)), NULL));
	}
	
	updateInformationMP(this, this->getKnight());

}

bool Level01::attackTowardsTarget(Hero* hero)
{
	
	int tileGid;
	float relativeX, relativeY, relativeR, searchX, searchY;
	float cosAlpha, sinAlpha;//角度
	bool hit;
	hit = false;
	bool tag = false;

	Vec2 heroPos = this->getKnight()->getPosition();
	for (const auto monster : this->creepsVec)
	{
		Vec2 enemy = monster->getPosition();
		if (((!monster->getAlreadyDead()) && (enemy.x >= heroPos.x - _knight->getAttackRadius()) && (monster->getActive())&&(enemy.x <= heroPos.x + _knight->getAttackRadius()))
			&& ((enemy.y >= heroPos.y - _knight->getAttackRadius()) && (enemy.y <= heroPos.y + _knight->getAttackRadius())))
		{
			for (int i = 0; i < this->getBullet()->getAttackFrequency(); i++)//攻击频率
			{
			auto bullet = Bullet::create(this->getBulletFilename(), this->getBullet());
			Vec2 weapon = this->getWeapon()->getPosition();
			
			bullet->setVisible(false);
			auto weaponcache = SpriteFrameCache::getInstance();
					// //
			std::string filename = this->getWeaponFilename();
			for (int j = 0; j < 4; j++)
			filename.pop_back();
			filename += "Attack.plist";
			weaponcache->addSpriteFramesWithFile(filename);
				// //
			Vector<SpriteFrame*>vec;
			char name[50] = { 0 };
			std::string file = this->getWeaponFilename();
			file.erase(0, 8);
			for (int i = 0; i < 6; i++)
			{
			sprintf(name, "%sAttack%04d", file.c_str(), i);
			vec.pushBack(weaponcache->getSpriteFrameByName(name));
			}
			Animation* weaponAnimation = Animation::createWithSpriteFrames(vec, 0.005f);
			weaponAnimation->setRestoreOriginalFrame(true);
			Animate* weaponAnimate = Animate::create(weaponAnimation);
			this->getWeapon()->runAction(weaponAnimate);
			//设置碰撞属性
			auto body = PhysicsBody::createBox(bullet->getContentSize());
			body->setCategoryBitmask(MY_BULLET_1);//0010
			body->setCollisionBitmask(0);
			body->setContactTestBitmask(MY_BULLET_2);
			bullet->setPhysicsBody(body);

			bullet->setTag(TAG_OF_BULLET_01);
			bullet->setPosition(weapon);
			this->addChild(bullet);

			bullet->runAction(Sequence::create(MoveTo::create(0.3f * (i + 1), enemy), CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, bullet)), NULL));
			}
		this->getKnight()->consumeMP();
		updateInformationMP(this, this->getKnight());
		tag = true;
		break;
		}
	}
	
	return tag;
}

void Level01::attackRemotely(Vec2 enemy, Hero* hero)
{
	int tileGid;
	float relativeX, relativeY, relativeR, searchX, searchY;
	float cosAlpha, sinAlpha;//角度
	bool hit;
	hit = false;
	bool tag = false;
	for (int i = 0; i < this->getBullet()->getAttackFrequency(); i++)//攻击频率
	{
	Vec2 heroPos = hero->getPosition();
	auto bullet = Bullet::create(this->getBulletFilename(), this->getBullet());
	Vec2 weapon = this->getWeapon()->getPosition();

	auto body = PhysicsBody::createBox(bullet->getContentSize()*2);
	body->setCategoryBitmask(MY_BULLET_1);//0010
	body->setCollisionBitmask(0);
	body->setContactTestBitmask(MY_BULLET_2);
	bullet->setPhysicsBody(body);

	bullet->setTag(TAG_OF_BULLET_01);
	bullet->setPosition(weapon);
	this->addChild(bullet);


	hit = false;
	relativeX = heroPos.x - enemy.x;
	relativeY = heroPos.y - enemy.y;
	relativeR = sqrt(relativeX * relativeX + relativeY * relativeY);
	cosAlpha = relativeX / relativeR;
	sinAlpha = relativeY / relativeR;
	searchX = heroPos.x;
	searchY = heroPos.y;
	if (relativeR != hero->getAttackRadius())
	{
		relativeR = hero->getAttackRadius();
	}
	while (relativeR > 0)
	{

		searchX -= 20 * cosAlpha;
		searchY -= 20 * sinAlpha;
		int xxx = 0.5 * searchX / map->getTileSize().width;
		int yyy = ((map->getMapSize().height * map->getTileSize().height) - 0.5 * searchY) / map->getTileSize().height;

		Point posAfter = Point(xxx, yyy);

		tileGid = collidable->getTileGIDAt(posAfter);
		if (tileGid > 0)
		{
			Value prop = map->getPropertiesForGID(tileGid);

			ValueMap propValueMap = prop.asValueMap();

			std::string collision = propValueMap["Collidable"].asString();

			if (collision == "true")
			{
				hit = true;
				break;
			}
		}
			relativeR -= 20;
	}
		if (hit == true)
		{
			bullet->runAction(Sequence::create(MoveTo::create(0.3f*(i+1), Vec2(searchX, searchY)), CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, bullet)), NULL));
		}
		else
		{
			searchX -= 80 * cosAlpha;
			searchY -= 80 * sinAlpha;
			bullet->runAction(Sequence::create(MoveTo::create(0.3f*(i+1), Vec2(searchX, searchY)), CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, bullet)), NULL));
		}
	}
	this->getKnight()->consumeMP();
	updateInformationMP(this, this->getKnight());
}

void Level01::enemyMoveUpdate(float delta)
{
	creepMove();
}

void Level01::creepMove()
{
	int xx, yy, tileGid;
	Point playerPos = this->getKnight()->getPosition();
	float relativeX, relativeY, relativeR, searchX, searchY;
	float cosAlpha, sinAlpha;//角度
	bool hit;

	for (const auto& sprite : this->creepsVec)
	{
		if (!sprite->getAlreadyDead() && sprite->getActive())//如果这一个小怪没有死，就会随着英雄移动
		{
			//debuff
			if (sprite->getReleaseDebuff() == BURN)
			{
				sprite->setColor(Color3B::RED);

				int _HP = sprite->getHP();
				_HP -= 2;
				if (_HP <= 0)
				{
					sprite->setHP(0);
					sprite->setAlreadyDead(true);
					sprite->setAttackRadius(0);
				}
				else
				{
					sprite->setHP(_HP);
					sprite->setAlreadyDead(false);
				}
				if (sprite->getAlreadyDead())
				{
					creepDie(sprite);
				}
			}
			Point pos = sprite->getPosition();
			if (!this->getKnight()->getAlreadyDead())
			{
				if ((pos.x >= playerPos.x - ENEMY_REMOTE) && (pos.x <= playerPos.x + ENEMY_REMOTE))
				{
					if ((pos.y >= playerPos.y - ENEMY_REMOTE) && (pos.y <= playerPos.y + ENEMY_REMOTE))
					{
						hit = false;
						relativeX = playerPos.x - pos.x;
						relativeY = playerPos.y - pos.y;
						relativeR = sqrt(relativeX * relativeX + relativeY * relativeY);
						cosAlpha = relativeX / relativeR;
						sinAlpha = relativeY / relativeR;
						searchX = pos.x;
						searchY = pos.y;
						while (relativeR > 0)
						{

							searchX += 20 * cosAlpha;
							searchY += 20 * sinAlpha;
							int xxx = 0.5 * searchX / map->getTileSize().width;
							int yyy = ((map->getMapSize().height * map->getTileSize().height) - 0.5 * searchY) / map->getTileSize().height;

							Point posAfter = Point(xxx, yyy);

							tileGid = collidable->getTileGIDAt(posAfter);
							if (tileGid > 0)
							{
								Value prop = map->getPropertiesForGID(tileGid);

								ValueMap propValueMap = prop.asValueMap();

								std::string collision = propValueMap["Collidable"].asString();

								if (collision == "true")
								{
									hit = true;
									break;
								}
							}
							relativeR -= 20;
						}
						if (hit == true)
						{
							continue;
						}
						auto moveToKnight = MoveTo::create(1.0f, Vec2(playerPos.x, playerPos.y));
						sprite->runAction(moveToKnight);
						continue;
					}
				}
			}

			float tempAngle = CCRANDOM_0_1() * 2 * PI;
			float x, y;
			if (sprite->getReleaseDebuff() != FROST)
			{
				x = 32 * cos(tempAngle);
				y = 32 * sin(tempAngle);
			}
			else
			{
				sprite->setColor(Color3B::BLUE);
				x = 16 * cos(tempAngle);
				y = 16 * sin(tempAngle);
			}
			auto move = MoveBy::create(1.0f, Vec2(x, y));

			xx = pos.x + x;
			yy = pos.y + y;

			int xxx = 0.5 * xx / map->getTileSize().width;
			int yyy = ((map->getMapSize().height * map->getTileSize().height) - 0.5 * yy) / map->getTileSize().height;

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
}

void Level01::setPlayerPosition(Point position)
{
	//从像素点坐标转化为瓦片坐标
	Point tileCoord = this->transPoision(position);

	//获得瓦片的GID
	const int tileGid = collidable->getTileGIDAt(tileCoord);

	if (tileGid > 0)
	{
		Value prop = map->getPropertiesForGID(tileGid);

		ValueMap propValueMap = prop.asValueMap();

		std::string collision = propValueMap["Collidable"].asString();
		std::string box0 = propValueMap["box0"].asString();
		std::string box1 = propValueMap["box1"].asString();
		std::string box2 = propValueMap["box2"].asString();
		std::string box3 = propValueMap["box3"].asString();
		std::string sculpture = propValueMap["sculpture"].asString();

		if (collision == "true") { //碰撞检测成功									

			return;

		}
		if (box0 == "true") {
			if (boxVec.at(0)->getOpen()) {
				flag[0]++;
				if (flag[0] == 1)
				{
					insidePropsVec.at(0)->setVisible(true);
					insidePropsVec.at(1)->setVisible(true);
					boxVec.at(0)->initWithFile("Props/openBox.png");
				}
			}
		}
		if (box1 == "true") {
			if (boxVec.at(1)->getOpen()) {
				flag[1]++;
				if (flag[1] == 1)
				{
					boxVec.at(1)->initWithFile("Props/openBox.png");
					insidePropsVec.at(2)->setVisible(true);
					insidePropsVec.at(3)->setVisible(true);
				}
			}
		}
		if (box2 == "true") {
			if (boxVec.at(2)->getOpen()) {
				flag[2]++;
				if (flag[2] == 1)
				{
					boxVec.at(2)->initWithFile("Props/openBox.png");
					insidePropsVec.at(4)->setVisible(true);
				}
			}
		}
		if (box3 == "true") {
			flag[3]++;
			if (flag[3] == 1) {
				boxVec.at(3)->initWithFile("Props/openBox.png");
				insidePropsVec.at(5)->setVisible(true);
			}
		}

		if (sculpture == "true")//拜雕塑
		{
			flag[4]++;
			if (flag[4] == 1)
			{
				s->setVisible(true);
			}
			if (flag[5] == 0)
			{
				if (keys[EventKeyboard::KeyCode::KEY_Q])
				{
					if (this->getKnight()->getGold() >= 9)
					{
						flag[5] ++;
						s->setVisible(false);
						int gold = this->getKnight()->getGold() - 9;
						this->getKnight()->setGold(gold);
						setV = 2;
						auto door = this->getChildByTag(TAG_OG_SAFEMAP_DOOR);
						if (door->getBoundingBox().containsPoint(this->getKnight()->getPosition()) && allClear)
							nextScene();

						this->getKnight()->setPosition(position);
						const Point pos = Point(position.x, position.y - 25);
						this->getWeapon()->setPosition(pos);

						const Point posM = Point(position.x + 390, position.y + 380);

						smallK->setPosition(posM);
						smallMap->setPosition(posM);
						updateGoldBox(this, this->getKnight());
						return;
					}
				}
			}
		}

	}
	auto door = this->getChildByTag(TAG_OG_SAFEMAP_DOOR);
	if (door->getBoundingBox().containsPoint(this->getKnight()->getPosition()) && allClear)
		nextScene();//场景的切换

	this->getKnight()->setPosition(position);
	const Point pos = Point(position.x, position.y - 25);
	this->getWeapon()->setPosition(pos);

	const Point posM = Point(position.x + 390, position.y + 380);
	smallK->setPosition(posM);
	smallMap->setPosition(posM);
}

Point Level01::transPoision(Point pos)
{
	int x = 0.5 * pos.x / map->getTileSize().width;
	int y = ((map->getMapSize().height * map->getTileSize().height) - 0.5 * pos.y) /

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

	Point point0 = smallMap->getPosition();
	Point offset0 = (Vec2(-68, -60));
	smallK->setPosition(-0.054 * offset + point0 + offset0);
}

void Level01::armorRecoverUpdate(float delta)
{
	if (this->getKnightBeenSelected() && (!this->getKnight()->getAlreadyDead()))
		updateHeroArmor(this->getKnight());
}

void Level01::collectProps()
{
	if (!this->getKnight()->getAlreadyDead())
	{
		Vec2 position = this->getKnight()->getPosition();
		for (auto props : propsVec)
		{
			if (props->isInRange(position))
			{
				/*props->runAction(MoveBy::create(0.3f, position));*/
				props->setVisible(false);
				props->makeEffect(this, this->getKnight());
				updateGoldBox(this, this->getKnight());
			}
		}
	}
}

void Level01::initProps()
{
	//第一个宝箱
	//蓝瓶
	auto drugMP01 = Props::create("Props/healMagic.png", PROPS_DRUG_MP, boxPositionVec[0].x, boxPositionVec[0].y, 50);
	drugMP01->setPosition(boxPositionVec[0].x+50,boxPositionVec[0].y);
	drugMP01->setTag(TAG_OF_PROPS_MP);
	propsVec.pushBack(drugMP01);
	insidePropsVec.pushBack(drugMP01);
	drugMP01->setVisible(false);
	addChild(drugMP01,2);

	//金币
	auto gold01 = Props::create("Props/gold.png", PROPS_GOLD, boxPositionVec[0].x, boxPositionVec[0].y, 50);
	gold01->setPosition(boxPositionVec[0]);
	propsVec.pushBack(gold01);
	insidePropsVec.pushBack(gold01);
	gold01->setVisible(false);
	addChild(gold01,2);

	//第二个宝箱
	auto drugMP02 = Props::create("Props/healMagic.png", PROPS_DRUG_MP, boxPositionVec[1].x, boxPositionVec[1].y, 50);
	drugMP02->setPosition(boxPositionVec[1].x+50,boxPositionVec[1].y);
	drugMP02->setTag(TAG_OF_PROPS_MP);
	propsVec.pushBack(drugMP02);
	insidePropsVec.pushBack(drugMP02);
	drugMP02->setVisible(false);
	addChild(drugMP02,2);

	auto gold02 = Props::create("Props/gold.png", PROPS_GOLD, boxPositionVec[1].x, boxPositionVec[1].y, 50);
	gold02->setPosition(boxPositionVec[1]);
	propsVec.pushBack(gold02);
	insidePropsVec.pushBack(gold02);
	gold02->setVisible(false);
	addChild(gold02,2);

	//第三个宝箱
	auto drugHP = Props::create("Props/healBlood.png", PROPS_DRUG_HP, boxPositionVec[2].x, boxPositionVec[2].y, 50);
	drugHP->setPosition(boxPositionVec[2]);
	drugHP->setTag(TAG_OF_PROPS_HP);
	propsVec.pushBack(drugHP);
	insidePropsVec.pushBack(drugHP);
	drugHP->setVisible(false);
	addChild(drugHP,2);

	//第四个宝箱--武器宝箱（随机武器）
		
	weaponVec.at(3)->setPosition(boxPositionVec[3]);
	insidePropsVec.pushBack(weaponVec.at(3));
	this->addChild(weaponVec.at(3), 2);
	this->addChild(bulletVec.at(3), 2);
	weaponVec.at(3)->setVisible(false);
	bulletVec.at(3)->setVisible(false);
}

void Level01::nextScene()
{
	auto scene = Level02::createScene();
	////预处理
	scene->removeChildByTag(TAG_OF_LEVEL_02);
	//
	auto stage = Level02::create();

	auto knight = Knight::create(this->getKnightFilename(), this->getKnight());
	auto weapon = Weapon::create(this->getWeaponFilename(), this->getWeapon());
	auto bullet = Bullet::create(this->getBulletFilename(), this->getBullet());

	knight->setPosition(Vec2(640, 480));
	weapon->setPosition(Vec2(640, 455));

	knight->setTag(TAG_OF_KNIGHT);
	weapon->setTag(TAG_OF_KNIGHT_INITIAL_WEAPON);;

	//设置闯的关卡数
	int num = knight->getLevelNum() + 1;
	knight->setLevelNum(num);
	successLevelNum = knight->getLevelNum();

	//设置碰撞性质
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
	////角色的添加
	stage->addChild(knight,1);
	stage->addChild(weapon,20);
	stage->setKnight(knight);
	stage->setWeapon(weapon);
	stage->setKnightFilename(knight->getActorFilename());
	stage->setWeaponFilename(weapon->getWeaponFilename());
	stage->weaponVec.pushBack(weapon);
	stage->bulletVec.pushBack(bullet);

	
	bullet->setVisible(false);
	//设置其他,不管是不是近战武器都有参数传递
	stage->addChild(bullet,20);
	stage->setBullet(bullet);
	stage->setBulletFilename(bullet->getBulletFilename());
	

	if (this->getKnightBeenSelected())
	{
		stage->setKnightBeenSelected(true);
	}

// ////////////////////////

	scene->addChild(stage, 0);

	//////////创建信息栏
	createInformationBox(stage, knight);
	createSkillBox(stage, knight);
	createGoldBox(stage, knight);

	auto reScene = TransitionProgressOutIn::create(0.5f, scene);
	Director::getInstance()->replaceScene(reScene);
}

void Level01::initWeapon()
{

	//武器1：篮球
	Weapon* weaponBasketball = Weapon::create("Weapons/weaponBasketball.png", HERO_ATTACK_LOW, CONSUMPTION_2, HERO_REMOTE, NORMAL);
	Bullet* bulletBasketball = Bullet::create("Weapons/weaponBasketball.png", HERO_ATTACK_LOW, ATTACK_FREQUENCY_3, NORMAL);
	weaponVec.pushBack(weaponBasketball);
	bulletVec.pushBack(bulletBasketball);
	

	//武器2：拔粪宝（滑稽）
	Weapon* weaponToiletPump = Weapon::create("Weapons/weaponToiletPump.png", HERO_ATTACK_HIGH, CONSUMPTION_3, HERO_REMOTE_2, BURN);
	Bullet* bulletToiletPump = Bullet::create("Bullets/bulletShit.png", HERO_ATTACK_HIGH, ATTACK_FREQUENCY_1, BURN);
	weaponVec.pushBack(weaponToiletPump);
	bulletVec.pushBack(bulletToiletPump);

	//武器3:步枪
	Weapon* weaponRifle = Weapon::create("Weapons/weaponGun2.png", HERO_ATTACK_MEDIUM, CONSUMPTION_4, HERO_REMOTE_3, NORMAL);
	Bullet* bulletRifle = Bullet::create("Bullets/bullet1.png", HERO_ATTACK_MEDIUM, ATTACK_FREQUENCY_5, NORMAL);
	weaponVec.pushBack(weaponRifle);
	bulletVec.pushBack(bulletRifle);

	//武器4：鱼
	Weapon* weaponFish = Weapon::create("Weapons/weaponFish.png", HERO_ATTACK_LOW, CONSUMPTION_1, HERO_REMOTE_1, FROST);
	Bullet* bulletFish = Bullet::create("Bullets/bullet5.png", HERO_ATTACK_LOW, ATTACK_FREQUENCY_1, FROST);
	weaponVec.pushBack(weaponFish);
	bulletVec.pushBack(bulletFish);

	//武器5：叉
	Weapon* weaponFork = Weapon::create("Weapons/weaponFork.png", HERO_ATTACK_MEDIUM, CONSUMPTION_0, HERO_MELEE_2, NORMAL);
	Bullet* bulletFork = Bullet::create("Bullets/bullet4.png", HERO_ATTACK_MEDIUM, ATTACK_FREQUENCY_1, NORMAL);
	weaponVec.pushBack(weaponFork);
	bulletVec.pushBack(bulletFork);

	//武器6：刀

	Weapon* weaponKnife = Weapon::create("Weapons/weaponKnife2.png", HERO_ATTACK_HIGH, CONSUMPTION_1, HERO_MELEE_4, NORMAL);
	Bullet* bulletKnife = Bullet::create("Bullets/bullet4.png", HERO_ATTACK_HIGH, ATTACK_FREQUENCY_3, NORMAL);
	weaponVec.pushBack(weaponKnife);
	bulletVec.pushBack(bulletKnife);
}