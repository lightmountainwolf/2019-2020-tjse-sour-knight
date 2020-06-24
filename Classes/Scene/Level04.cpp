#include "Scene/Level04.h"
#include "Scene/Level03.h"

Scene* Level04::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setGravity(Vec2(0.0f, 0.0f));//取消重力场

	auto layer = Level04::create();
	scene->addChild(layer, 0);
	// ////////////////////////////设置暂停按钮////////////////////////////////////////////
	auto pauseMenuItem = MenuItemImage::create(
		"Buttons/buttonPause.png", "Buttons/buttonPauseClicked.png", CC_CALLBACK_1(Level04::menuPauseCallback, layer));
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

bool Level04::init()
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

	smallMap = Sprite::create("Props/smallMap4.png");


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

	map = TMXTiledMap::create("Backgrounds/theM4.tmx");	//地图！
	map->setScale(2);
	addChild(map, 0);


	TMXObjectGroup* group = map->getObjectGroup("obj");
	ValueMap spawnPoint = group->getObject("player");
	float x = spawnPoint["x"].asFloat();
	float y = spawnPoint["y"].asFloat();

	collidable = map->getLayer("collidable");
	collidable->setVisible(false);
	this->setTag(TAG_OF_LEVEL_04);

	smallK->setPosition(x , y );
	smallMap->setPosition(x , y );
	addChild(smallMap,30);
	addChild(smallK,30);
	///////////////////////////////////////////////////以下为小怪的设置
		//生成小怪

	//插入传送门
	ValueMap doorPoint = group->getObject("transfer");

	float xDoor = 2 * doorPoint["x"].asFloat();

	float yDoor = 2 * doorPoint["y"].asFloat();

	auto door = setDoor(xDoor, yDoor, 200);
	door->setTag(TAG_OG_SAFEMAP_DOOR);
	this->addChild(door);
	door->setVisible(false);

	char monsters[5][4] = { "m1","m2" ,"m3" ,"m4" ,"m5" };

	char monstersGroup2[5][4] = { "m6","m7" ,"m8" ,"m9" ,"m10" };

	char monstersGroup1[5][4] = { "m11","m12" ,"m13" ,"m14" ,"m15" };

	char monstersGroup3[5][4] = { "m16","m17" ,"m18" ,"m19" ,"m20" };

	createMonster(monsters, "Creeps/monster4.png", 0);

	createMonster(monstersGroup2, "Creeps/monster5.png", 5);

	createMonster(monstersGroup1, "Creeps/monster4.png", 10);

	createMonster(monstersGroup3, "Creeps/monster4.png", 15);

	createMonster(monsters, "Creeps/monster5.png", 20);

	createMonster(monstersGroup2, "Creeps/monster6.png", 25);

	//boss
	Creep* Boss1 = Creep::create("Bosses/boss1.png", NORMAL, ENEMY_REMOTE2, BOSS_HP_LOW, MONSTER_ATTACK_MEDIUM, true);
	auto bodyB = PhysicsBody::createBox(Boss1->getContentSize());
	bodyB->setCategoryBitmask(ENEMY_1);
	bodyB->setCollisionBitmask(0);
	bodyB->setContactTestBitmask(ENEMY_2);
	Boss1->setPhysicsBody(bodyB);
	ValueMap bossPoint = group->getObject("boss");
	float xBoss = 2 * bossPoint["x"].asFloat();
	float yBoss = 2 * bossPoint["y"].asFloat();
	Boss1->setPosition(xBoss, yBoss);
	bossVec.pushBack(Boss1);
	this->addChild(Boss1);
	Boss1->setTag(MAX_TAG_OF_MONSTER + 1);

	//怪物信息初始化
	deadCreeps = 0;
	for (int i = 0; i < 15; i++)
	{
		creepDieArr[i] = false;
	}

	for (int j = 0; j < 4; j++)
	{
		littleMapClear[j] = 0;
		littleMapWave[j] = 0;
	}

	// ////////////////////////////////////////////////////////////////////
	this->schedule(schedule_selector(Level04::enemyAttackUpdate), 1.0f, kRepeatForever, 0);//敌人的攻击
	this->schedule(schedule_selector(Level04::enemyMoveUpdate), 2, -1, 0);//敌人的移动
	this->schedule(schedule_selector(Level04::armorRecoverUpdate), 2.0f, kRepeatForever, 0);//护甲的恢复
	this->schedule(schedule_selector(Level04::heroDieUpdate), 3.0f, kRepeatForever, 2.0f);
	this->schedule(schedule_selector(Level04::groundAttackUpdate), 0.5f, kRepeatForever, 0);
	this->schedule(schedule_selector(Level04::bossAttackUpdate), 3.0f, kRepeatForever, 0);
	this->schedule(schedule_selector(Level04::bossMoveUpdate), 1.0f, kRepeatForever, 0);

	this->scheduleUpdate();

	// /////////////////////////////
	initWeapon();
	initProps();
	initShop();
	return true;

}

void Level04::createMonster(char arr[5][4], const std::string& location, int num)
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
			monsterTemp = Creep::create(location, NORMAL, ENEMY_REMOTE2, CREEP_HP_5, MONSTER_ATTACK_MEDIUM, true);
		else if (num / 5 == 1)
			monsterTemp = Creep::create(location, NORMAL, ENEMY_REMOTE2, CREEP_HP_4, MONSTER_ATTACK_MEDIUM, true);
		else if (num / 5 == 2)
			monsterTemp = Creep::create(location, NORMAL, ENEMY_REMOTE, CREEP_HP_4, MONSTER_ATTACK_LOW, true);
		else if (num / 5 == 3)
			monsterTemp = Creep::create(location, NORMAL, ENEMY_REMOTE2, CREEP_HP_5, MONSTER_ATTACK_MEDIUM, true);
		else if (num / 5 == 4)
			monsterTemp = Creep::create(location, NORMAL, ENEMY_REMOTE, CREEP_HP_4, MONSTER_ATTACK_LOW, true);
		else if (num / 5 == 5)
			monsterTemp = Creep::create(location, NORMAL, ENEMY_REMOTE, CREEP_HP_5, MONSTER_ATTACK_HIGH, true);

		auto body = PhysicsBody::createBox(monsterTemp->getContentSize());
		body->setCategoryBitmask(ENEMY_1);
		body->setCollisionBitmask(0);
		body->setContactTestBitmask(ENEMY_2);
		monsterTemp->setPhysicsBody(body);


		monsterTemp->setPosition(x, y);

		CCLOG("%f %f", x, y);

		monsterTemp->setTag(tagArr[i]);
		this->addChild(monsterTemp);

		if (!monsterTemp->getActive())
		{
			monsterTemp->setVisible(false);

		}


		creepsVec.pushBack(monsterTemp);
	}
}

void Level04::creepDie(Creep* creep)
{
	int tag = creep->getTag();

	if ((tag >= TAG_OF_MONSTER_1) && (tag <= TAG_OF_MONSTER_5))
	{
		creep->initWithFile("Creeps/monster4Dead.png");
		creepDieArr[tag - 55] = true;
		littleMapClear[0]++;
		deadCreeps++;
	}

	else if ((tag >= TAG_OF_MONSTER_1 + 5) && (tag <= TAG_OF_MONSTER_5 + 5))
	{
		creep->initWithFile("Creeps/monster5Dead.png");
		creepDieArr[tag - 55] = true;
		littleMapClear[1]++;
		deadCreeps++;

	}

	else if ((tag >= TAG_OF_MONSTER_1 + 10) && (tag <= TAG_OF_MONSTER_5 + 10))
	{
		creep->initWithFile("Creeps/monster4Dead.png");
		creepDieArr[tag - 55] = true;
		littleMapClear[2]++;
		deadCreeps++;
	}

	else if ((tag >= TAG_OF_MONSTER_1 + 15) && (tag <= TAG_OF_MONSTER_5 + 15))
	{
		creep->initWithFile("Creeps/monster4Dead.png");
		creepDieArr[tag - 55] = true;
		littleMapClear[3]++;
		deadCreeps++;
	}

	else if ((tag >= TAG_OF_MONSTER_1 + 20) && (tag <= TAG_OF_MONSTER_5 + 20))
	{
		creep->initWithFile("Creeps/monster5Dead.png");
		creepDieArr[tag - 55] = true;
		littleMapClear[0]++;
		deadCreeps++;
	}
	else if ((tag >= TAG_OF_MONSTER_1 + 25) && (tag <= TAG_OF_MONSTER_5 + 25))
	{
		creep->initWithFile("Creeps/monster6Dead.png");
		creepDieArr[tag - 55] = true;
		littleMapClear[1]++;
		deadCreeps++;
	}
	else if (tag == MAX_TAG_OF_MONSTER + 1)
	{
		creep->initWithFile("Bosses/boss1Dead.png");
		creepDieArr[tag - 55] = true;
		littleMapClear[1]++;
		deadCreeps++;
	}

	for (int i = 0; i < 2; i++)
	{
		if (littleMapClear[i] >= 5)
		{
			CCLOG("%d", i);
			littleMapClear[i] = 0;

			if (littleMapWave[i] == 0)
			{

				for (int j = 20 + i * 5; j < 25 + i * 5; j++)
				{
					Creep* monster = creepsVec.at(j);
					monster->setActive(true);
					monster->setVisible(true);

				}

			}
			littleMapWave[i]++;
		}
	}
	if (deadCreeps >= 31)
	{
		allClear = true;
		auto door = this->getChildByTag(TAG_OG_SAFEMAP_DOOR);
		door->setVisible(true);
	}


}


void Level04::onEnter()//注册监听器，设置音乐
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
		if (bullet && bullet->getTag() == TAG_OF_BULLET_01 && monster && (monster->getTag() >= TAG_OF_MONSTER_1) && (monster->getTag() <= MAX_TAG_OF_MONSTER + 1) && (monster->getActive()))
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
		if (monster && (monster->getTag() >= TAG_OF_MONSTER_1) && (monster->getTag() <= MAX_TAG_OF_MONSTER + 1))
			monster->setColor(Color3B::WHITE);
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(monsterListener, 1);

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

void Level04::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();

}

void Level04::onExitTransitionDidStart()
{
	Layer::onExitTransitionDidStart();

}

void Level04::onExit()//注销监听器
{
	Layer::onExit();
	for (auto listener : listenerVec)
		Director::getInstance()->getEventDispatcher()->removeEventListener(listener);

}

void Level04::cleanup()
{
	Layer::cleanup();

}

void Level04::menuPauseCallback(cocos2d::Ref* pSender)//暂停按钮的回调
{
	auto scene = Pause::createScene();
	Director::getInstance()->pushScene(scene);
	playSound("sound/ClickSound.mp3");
}


bool Level04::onTouchBegan(Touch* touch, Event* event)//鼠标点击，骑士攻击
{
	Vec2 position = convertTouchToNodeSpace(touch);
	if ((this->getKnightBeenSelected()) && (!this->getKnight()->getAlreadyDead()))//骑士被选择并且没有死
	{
		if ((this->getKnight()->getMP()) || ((!this->getKnight()->getMP()) && (!this->getWeapon()->getMPConsuming())))//如果蓝未耗完或蓝已耗完但武器不耗蓝
		{
			if (this->getKnight()->getAttackMode() <= HERO_MELEE_4)//近程攻击
			{
				if (!attackTowardsTarget(this->getKnight()))
				{
					attackMelee(this->getKnight());
				}
			}
			else attackRemotely(position, this->getKnight());
			return false;
		}
	}
	return false;
}

void Level04::removeFromParent(Node* bullet)//删除子弹的回调函数
{
	bullet->removeFromParent();
}

void Level04::update(float delta)
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


}

void Level04::heroDieUpdate(float delta)
{
	if (this->getKnightBeenSelected() && this->getKnight()->getAlreadyDead())
	{
		auto deadScene = Dead::createScene();
		auto reScene = CCTransitionMoveInT::create(0.5f, deadScene);
		Director::getInstance()->replaceScene(reScene);
	}
}

void Level04::enemyAttackUpdate(float delta)
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
				if (monster->getAttackMode() >= ENEMY_REMOTE)
				{
					Vec2 enemy = monster->getPosition();
					if ((enemy.x >= hero.x - monster->getAttackRadius()) && (enemy.x <= hero.x + monster->getAttackRadius()) &&
						(enemy.y >= hero.y - monster->getAttackRadius()) && (enemy.y <= hero.y + monster->getAttackRadius()))
					{
						hit = false;
						relativeX = hero.x - enemy.x;
						relativeY = hero.y - enemy.y;
						relativeR = sqrt(relativeX * relativeX + relativeY * relativeY);
						cosAlpha = relativeX / relativeR;
						sinAlpha = relativeY / relativeR;
						searchX = enemy.x;
						searchY = enemy.y;
						relativeR = monster->getAttackRadius();
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
						auto enemyBullet = Bullet::create("Bullets/bullet1.png", monster->getAttack(), ATTACK_FREQUENCY_1, NORMAL);
						enemyBullet->setTag(TAG_OF_BULLET_01);

						auto Ebody = PhysicsBody::createBox(enemyBullet->getContentSize());
						Ebody->setCategoryBitmask(ENEMY_BULLET_1);//0010
						Ebody->setCollisionBitmask(0);
						Ebody->setContactTestBitmask(ENEMY_BULLET_2);
						enemyBullet->setPhysicsBody(Ebody);


						enemyBullet->setPosition(enemy);
						enemyBullet->runAction(Sequence::create(MoveTo::create(1.0f, Vec2(searchX, searchY)), CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, enemyBullet)), NULL));
						this->addChild(enemyBullet);

					}
				}
				else if (monster->getAttackMode() <= ENEMY_MELEE)
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

						//this->setBeenAttacked(false);
						this->addChild(enemyBullet);
						enemyBullet->setVisible(false);
					}
				}
			}
		}
	}
}

void Level04::knightMove()//放置在update里的函数，实现骑士角色的移动
{
	Point playerPos = this->getKnight()->getPosition();

	if (keys[EventKeyboard::KeyCode::KEY_D])
	{
		playerPos.x += map->getTileSize().width / 3;

		this->getKnight()->runAction(FlipX::create(false));
		this->getWeapon()->runAction(FlipX::create(false));

	}
	if (keys[EventKeyboard::KeyCode::KEY_A])
	{
		playerPos.x -= map->getTileSize().width / 3;

		this->getKnight()->runAction(FlipX::create(true));
		this->getWeapon()->runAction(FlipX::create(true));

	}
	if (keys[EventKeyboard::KeyCode::KEY_S])
	{
		playerPos.y -= map->getTileSize().height / 3;

	}
	if (keys[EventKeyboard::KeyCode::KEY_W])
	{
		playerPos.y += map->getTileSize().height / 3;

	}
	if (keys[EventKeyboard::KeyCode::KEY_Q])
	{
		collectProps();
		buyProps();
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

void Level04::attackMelee(Hero* hero)//没有攻击目标时的随机攻击
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

bool Level04::attackTowardsTarget(Hero* hero)
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
		if (((!monster->getAlreadyDead()) && (enemy.x >= heroPos.x - _knight->getAttackRadius()) && (monster->getActive()) && (enemy.x <= heroPos.x + _knight->getAttackRadius()))
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

void Level04::attackRemotely(Vec2 enemy, Hero* hero)
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

		auto body = PhysicsBody::createBox(bullet->getContentSize() * 2);
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
			bullet->runAction(Sequence::create(MoveTo::create(0.3f * (i + 1), Vec2(searchX, searchY)), CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, bullet)), NULL));
		}
		else
		{
			searchX -= 80 * cosAlpha;
			searchY -= 80 * sinAlpha;
			bullet->runAction(Sequence::create(MoveTo::create(0.3f * (i + 1), Vec2(searchX, searchY)), CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, bullet)), NULL));
		}
	}
	this->getKnight()->consumeMP();
	updateInformationMP(this, this->getKnight());
}

void Level04::enemyMoveUpdate(float delta)
{
	creepMove();
}

void Level04::creepMove()
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
				if ((pos.x >= playerPos.x - sprite->getAttackRadius()) && (pos.x <= playerPos.x + sprite->getAttackRadius()))
				{
					if ((pos.y >= playerPos.y - sprite->getAttackRadius()) && (pos.y <= playerPos.y + sprite->getAttackRadius()))
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
						auto moveToKnight = MoveTo::create(2.0f, Vec2(playerPos.x, playerPos.y));
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
			auto move = MoveBy::create(2.0f, Vec2(x, y));

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

void Level04::setPlayerPosition(Point position)
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

		std::string groundAttack = propValueMap["groundjian"].asString();

		//if (groundAttack == "true")
		//{
			//this->schedule(schedule_selector(Level02::groundAttackUpdate), 2.0f, kRepeatForever, 0);
		//}//地刺

		if (collision == "true") { //碰撞检测成功									

			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("empty.wav");

			return;

		}

	}
	this->getKnight()->setPosition(position);
	const Point pos = Point(position.x, position.y - 25);
	this->getWeapon()->setPosition(pos);

	auto door = this->getChildByTag(TAG_OG_SAFEMAP_DOOR);
	if (door->getBoundingBox().containsPoint(this->getKnight()->getPosition()) && allClear)
		nextScene();//场景的切换

	const Point posM = Point(position.x + 390, position.y + 380);

	smallK->setPosition(posM);
	smallMap->setPosition(posM);


}

void Level04::nextScene()
{
	//设置闯的关卡数
	int num = this->getKnight()->getLevelNum() + 1;
	this->getKnight()->setLevelNum(num);
	successLevelNum = this->getKnight()->getLevelNum();

	auto scene = Dead::create();
	Director::getInstance()->replaceScene(scene);
}


Point Level04::transPoision(Point pos)
{
	int x = 0.5 * pos.x / map->getTileSize().width;
	int y = ((map->getMapSize().height * map->getTileSize().height) - 0.5 * pos.y) /

		map->getTileSize().height;

	return Point(x, y);
}


void Level04::screenRoll(Point position)
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

	Point offset0 = (Vec2(-50, -85));

	smallK->setPosition(-0.045 * offset + point0 + offset0);


}


void Level04::armorRecoverUpdate(float delta)
{
	if (this->getKnightBeenSelected() && (!this->getKnight()->getAlreadyDead()))
		updateHeroArmor(this->getKnight());
}


void Level04::collectProps()
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

void Level04::initProps()
{
	weaponVec.at(5)->setPosition(Vec2(500, 700));
	this->addChild(weaponVec.at(5), 2);
	this->addChild(bulletVec.at(5), 2);
	bulletVec.at(5)->setVisible(false);
}

void Level04::initShop()
{
	buyTimes = 0;
	//商店的初始化
	auto shop = Shops::create("Shops/shopWithTable.png", 600, 700);
	shop->setPosition(Vec2(shop->getX(), shop->getY()));
	addChild(shop, 0);

	//血瓶
	auto drugHP = Props::create("Props/healBlood.png", PROPS_DRUG_HP_FULL, shop->getLocation1X(), shop->getLocationY(), 50);
	drugHP->setPosition(shop->getLocation1X(), shop->getLocationY());
	addChild(drugHP);
	propsOnSaleVec.pushBack(drugHP);

	//蓝瓶
	auto drugMP = Props::create("Props/healMagic.png", PROPS_DRUG_MP_FULL, shop->getLocation2X(), shop->getLocationY(), 50);
	drugMP->setPosition(shop->getLocation2X(), shop->getLocationY());
	addChild(drugMP);
	propsOnSaleVec.pushBack(drugMP);

	//紫瓶-花钱没有效果
	auto drugHPMP = Props::create("Props/drugHPMP.png", EMPTY, shop->getLocation3X(), shop->getLocationY(), 50);
	drugHPMP->setPosition(shop->getLocation3X(), shop->getLocationY());
	addChild(drugHPMP);
	propsOnSaleVec.pushBack(drugHPMP);
}


void Level04::buyProps()
{
	if (!this->getKnight()->getAlreadyDead())
	{
		Vec2 position = this->getKnight()->getPosition();
		for (int i = 0; i < propsOnSaleVec.size(); i++)
		{
			auto props = propsOnSaleVec.at(i);
			int gold = this->getKnight()->getGold();
			int price = props->getPrice();
			if ((props->isInRange(position)) && (gold >= price) && (buyTimes == 0))
			{
				props->setVisible(false);
				props->makeEffect(this, this->getKnight());
				this->getKnight()->setGold(gold - price);
				updateGoldBox(this, this->getKnight());
				buyTimes = 1;
			}
		}
	}
}


void Level04::groundAttackUpdate(float delta)
{
	Point tileCoord = this->transPoision(this->getKnight()->getPosition());

	//获得瓦片的GID
	const int tileGid = collidable->getTileGIDAt(tileCoord);

	if (tileGid > 0)
	{
		Value prop = map->getPropertiesForGID(tileGid);

		ValueMap propValueMap = prop.asValueMap();

		//std::string collision = propValueMap["Collidable"].asString();

		std::string groundAttack = propValueMap["groundjian"].asString();

		if (groundAttack == "true")
		{
			auto knight = this->getKnight();
			colorKnight = knight->getColor();
			knight->setColor(Color3B::RED);

			int armor = knight->getArmor() - GROUNDATTACK_1;
			knight->setArmor(armor);
			if (knight->getArmor() < 0)
			{
				int hp = abs(knight->getArmor());
				knight->setArmor(0);
				knight->setHP(knight->getHP() - hp);
				if (knight->getHP() <= 0)
				{
					knight->setHP(0);
					knight->setAlreadyDead(true);
					knight->setAttackRadius(0);
				}
				else
					knight->setAlreadyDead(false);
			}
			this->schedule(schedule_selector(Level04::returnColor), 0, 1, 0.1f);

		}//地刺



	}
}

void Level04::returnColor(float dt)
{
	auto knight = this->getKnight();
	knight->setColor(colorKnight);
}

void Level04::initWeapon()
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

void Level04::bossMoveUpdate(float dt)
{
	int xx, yy, tileGid;
	for (const auto& sprite : this->bossVec)
	{
		if (!sprite->getAlreadyDead() && sprite->getActive())//如果这一个小怪没有死，就会随着英雄移动
		{

			Point pos = sprite->getPosition();

			float tempAngle = CCRANDOM_0_1() * 2 * PI;
			float x = 100 * cos(tempAngle);
			float y = 100 * sin(tempAngle);
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

void Level04::bossAttackUpdate(float dt)
{
	int tileGid;
	float relativeX, relativeY, relativeR, searchX, searchY;
	float cosAlpha, sinAlpha;//角度
	bool hit;
	float range = 1500;
	float frequence = 12;
	for (const auto& sprite : this->bossVec)
	{
		if (!sprite->getAlreadyDead())
		{
			Vec2 boss = sprite->getPosition();
			for (int i = 0; i < 24; i++)
			{
				auto enemyBullet = Bullet::create("Bullets/bullet1.png", sprite->getAttack(), ATTACK_FREQUENCY_1, NORMAL);
				enemyBullet->setTag(TAG_OF_BULLET_01);
				//bossBulletVec.pushBack(enemyBullet);
				auto Ebody = PhysicsBody::createBox(enemyBullet->getContentSize());
				Ebody->setCategoryBitmask(ENEMY_BULLET_1);//0010
				Ebody->setCollisionBitmask(0);
				Ebody->setContactTestBitmask(ENEMY_BULLET_2);
				enemyBullet->setPhysicsBody(Ebody);
				enemyBullet->setPosition(sprite->getPosition());
				searchX = boss.x;
				searchY = boss.y;
				relativeR = range;
				for (int j = 0; j < 30; j++)
				{
					relativeR -= 33;
					searchX += 33 * sin(PI / 12 * i);
					searchY += 33 * cos(PI / 12 * i);
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


				enemyBullet->runAction(Sequence::create(MoveTo::create(2.0f, Vec2(searchX, searchY)), CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, enemyBullet)), NULL));
				this->addChild(enemyBullet);
			}
		}
	}
}
