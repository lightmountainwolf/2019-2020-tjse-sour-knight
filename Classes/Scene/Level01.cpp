#include "Scene/Level01.h"
#include "Scene/Level02.h"

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
// //////////
	//this->setBeenAttacked(false);

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

	//插入传送门
	ValueMap doorPoint = group->getObject("transfer");

	float xDoor = 2*doorPoint["x"].asFloat();

	float yDoor = 2*doorPoint["y"].asFloat();

	auto door = setDoor(xDoor, yDoor, 200);
	door->setTag(TAG_OG_SAFEMAP_DOOR);
	this->addChild(door);
	door->setVisible(false);

	collidable = map->getLayer("collidable");

	collidable->setVisible(false);

	this->setTag(TAG_OF_LEVEL_01);
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
// ////////////////////////////////////////////////////////////////////
	this->schedule(schedule_selector(Level01::enemyAttackUpdate), 1.0f, kRepeatForever, 0);//敌人的攻击
	this->schedule(schedule_selector(Level01::enemyMoveUpdate), 1, -1, 1);//敌人的移动
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
		if(num/5==0)
		monsterTemp = Creep::create(location, NORMAL, MELEE, CREEP_HP_1, MONSTER_ATTACK_LOW,true);
		else if(num/5==1)
		monsterTemp = Creep::create(location, NORMAL, ENEMY_REMOTE, CREEP_HP_2, MONSTER_ATTACK_LOW, true);
		else if(num/5==2)
			monsterTemp = Creep::create(location, NORMAL, ENEMY_REMOTE, CREEP_HP_2, MONSTER_ATTACK_LOW, true);
		else if (num / 5 == 3)
			monsterTemp = Creep::create(location, NORMAL, ENEMY_REMOTE, CREEP_HP_2, MONSTER_ATTACK_LOW, false);
		else if (num / 5 == 4)
			monsterTemp = Creep::create(location, NORMAL, ENEMY_REMOTE, CREEP_HP_1, MONSTER_ATTACK_LOW, false);


		
			auto body = PhysicsBody::createBox(monsterTemp->getContentSize());

			body->setCategoryBitmask(ENEMY_1);
			body->setCollisionBitmask(0);
			body->setContactTestBitmask(ENEMY_2);

			monsterTemp->setPhysicsBody(body);
		
		
		
		
		

		monsterTemp->setPosition(x, y);

		CCLOG("%f %f",x,y);

		monsterTemp->setTag(tagArr[i]);
		this->addChild(monsterTemp);

		if (monsterTemp->active == false)
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
		deadCreeps++;
	}

	else if ((tag >= TAG_OF_MONSTER_1 + 5) && (tag <= TAG_OF_MONSTER_5 + 5))
	{
		creep->initWithFile("Creeps/monster2Dead.png");
		creepDieArr[tag - 55] = true;
		littleMapClear[1]++;
		deadCreeps++;
		
	}
		
	else if ((tag >= TAG_OF_MONSTER_1 + 10) && (tag <= TAG_OF_MONSTER_5 + 10))
	{
		creep->initWithFile("Creeps/monster1Dead.png");
		creepDieArr[tag - 55] = true;
		littleMapClear[2]++;
		deadCreeps++;
	}

	else if ((tag >= TAG_OF_MONSTER_1 + 15) && (tag <= TAG_OF_MONSTER_5 + 15))
	{
		creep->initWithFile("Creeps/monster2Dead.png");
		creepDieArr[tag - 55] = true;
		littleMapClear[0]++;
		deadCreeps++;
	}

	else if ((tag >= TAG_OF_MONSTER_1 + 20) && (tag <= TAG_OF_MONSTER_5 + 20))
	{
		creep->initWithFile("Creeps/monster1Dead.png");
		creepDieArr[tag - 55] = true;
		littleMapClear[1]++;
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
				monster->active = true;
				monster->setVisible(true);
				;

			}
			if (littleMapWave[i] == 0)
				{
				littleMapWave[i]++;
				}
			
		}
	}
	
	if (deadCreeps >= 25)
	{
		allClear = true;
		auto door=this->getChildByTag(TAG_OG_SAFEMAP_DOOR);
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
		if (bullet && bullet->getTag() == TAG_OF_BULLET_01 && monster &&( monster->getTag()>=TAG_OF_MONSTER_1)&&(monster->getTag()<= MAX_TAG_OF_MONSTER))
		{
			if (!monster->getAlreadyDead()&&monster->active==true)
			{
				monster->setColor(Color3B::RED);
				monster->takeDamage(bullet);
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
		if(monster&&(monster->getTag()>=TAG_OF_MONSTER_1)&&(monster->getTag()<=MAX_TAG_OF_MONSTER))
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
			if(hero&&(hero->getTag()==this->getKnight()->getTag()))
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
	for(auto listener:listenerVec)
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
	if (( this->getKnight()->getMP())&&(!this->getKnight()->getAlreadyDead()))
	{
		Vec2 p = this->getWeapon()->getPosition();
		auto bullet = Bullet::create("Bullets/bullet1.png", 3, NORMAL);
		bullet->setTag(TAG_OF_BULLET_01);
		this->setBullet(bullet);
		/// ///////////设置碰撞属性
		auto body = PhysicsBody::createBox(bullet->getContentSize());
		body->setCategoryBitmask(MY_BULLET_1);//0010
		body->setCollisionBitmask(0);
		body->setContactTestBitmask(MY_BULLET_2);
		
		bullet->setPhysicsBody(body);
		bullet->setPosition(p);
		this->addChild(bullet);

		//角色的自动功放机
		if (!attackTawordsTarget(bullet))
			attackRandomly(bullet);

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
	
	log("%d", this->getKnightBeenSelected());
	if (this->getKnightBeenSelected())
	{
		updateInformationArmor(this, this->getKnight());
		updateInformationHP(this, this->getKnight());
		if ((!this->getKnight()->getAlreadyDead()))
		{
			knightMove();
		}
	}
	auto door = this->getChildByTag(TAG_OG_SAFEMAP_DOOR);
	
	if (door->getBoundingBox().containsPoint(this->getKnight()->getPosition())&&allClear)
	{
		auto scene = Level02::createScene();
		////预处理
		scene->removeChildByTag(TAG_OF_LEVEL_01);
		//

		auto stage = Level02::create();

		auto knight = Knight::create("Heroes/knight1.1.png", this->getKnight());
		auto weapon = Weapon::create("Weapons/weaponGun.png", this->getWeapon());

		knight->setPosition(Vec2(640, 480));
		weapon->setPosition(Vec2(640, 455));

		knight->setTag(TAG_OF_KNIGHT);
		weapon->setTag(TAG_OF_KNIGHT_INITIAL_WEAPON);
		//stage->setTag(TAG_OF_LEVEL_01);

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
			if (!monster->getAlreadyDead() && monster->active == true)
			{
				if (monster->getAttackMode() == ENEMY_REMOTE)
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
						//this->setBeenAttacked(true);
						auto enemyBullet = Bullet::create("Bullets/bullet1.png", 3, NORMAL);
						enemyBullet->setTag(TAG_OF_BULLET_01);

						auto Ebody = PhysicsBody::createBox(enemyBullet->getContentSize());
						Ebody->setCategoryBitmask(ENEMY_BULLET_1);//0010
						Ebody->setCollisionBitmask(0);
						Ebody->setContactTestBitmask(ENEMY_BULLET_2);
						enemyBullet->setPhysicsBody(Ebody);


						enemyBullet->setPosition(enemy);
						enemyBullet->runAction(Sequence::create(MoveTo::create(0.4f, Vec2(searchX,searchY)), CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, enemyBullet)), NULL));

						//this->setBeenAttacked(false);
						this->addChild(enemyBullet);

					}
				}
				else if (monster->getAttackMode() == MELEE)
				{
					Vec2 enemy = monster->getPosition();
					if ((enemy.x >= hero.x - MELEE) && (enemy.x <= hero.x + MELEE) &&
						(enemy.y >= hero.y - MELEE) && (enemy.y <= hero.y + MELEE))
					{
						this->setInAttackRange(true);
						//this->setBeenAttacked(true);
						auto enemyBullet = Bullet::create("Weapons/forkAttack1.png", 3, NORMAL);
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

void Level01::knightMove()//放置在update里的函数，实现骑士角色的移动
{
	Point playerPos = this->getKnight()->getPosition();

	if (keys[EventKeyboard::KeyCode::KEY_D])
	{
		playerPos.x += map->getTileSize().width/4;

		this->getKnight()->runAction(FlipX::create(false));
		this->getWeapon()->runAction(FlipX::create(false));
		
	}
	if (keys[EventKeyboard::KeyCode::KEY_A])
	{
		playerPos.x -= map->getTileSize().width/4;

		this->getKnight()->runAction(FlipX::create(true));
		this->getWeapon()->runAction(FlipX::create(true));
		
	}
	if (keys[EventKeyboard::KeyCode::KEY_S])
	{
		playerPos.y -= map->getTileSize().height/4;
		
	}
	if (keys[EventKeyboard::KeyCode::KEY_W])
	{
		playerPos.y += map->getTileSize().height/4;
		
	}
	
	this->setPlayerPosition(playerPos);
	this->screenRoll(playerPos);

}

void Level01::attackRandomly(Bullet* bullet)//没有攻击目标时的随机攻击
{
	float tempAngle = CCRANDOM_0_1() * 2 * PI;
	float x = 250 * cos(tempAngle);
	float y = 250 * sin(tempAngle);
	bullet->runAction(Sequence::create(MoveBy::create(0.3f, Vec2(x, y)), CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, bullet)), NULL));
	updateInformationMP(this, this->getKnight());

}

bool Level01::attackTawordsTarget(Bullet* bullet)
{
	int tileGid;
	float relativeX, relativeY, relativeR, searchX, searchY;
	float cosAlpha, sinAlpha;//角度
	bool hit;
	hit = false;
	bool tag=false;
	if (this->getKnightBeenSelected())
	{
		Vec2 hero = this->getKnight()->getPosition();
		for (const auto monster : this->creepsVec)
		{
			Vec2 enemy = monster->getPosition();
			if (((!monster->getAlreadyDead()) && monster->active == true && (enemy.x >= hero.x - _knight->getAttackRadius()) && (enemy.x <= hero.x + _knight->getAttackRadius()))
				&& ((enemy.y >= hero.y - _knight->getAttackRadius()) && (enemy.y <= hero.y + _knight->getAttackRadius())))
			{
				hit = false;
				relativeX = hero.x - enemy.x;
				relativeY = hero.y - enemy.y;
				relativeR = sqrt(relativeX * relativeX + relativeY * relativeY);
				cosAlpha = relativeX / relativeR;
				sinAlpha = relativeY / relativeR;
				searchX = hero.x;
				searchY = hero.y;
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
				bullet->runAction(Sequence::create(MoveTo::create(0.3f, Vec2(searchX,searchY)), CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, bullet)), NULL));
				updateInformationMP(this, this->getKnight());
				tag = true;
				break;
			}
		}
		return tag;
	}
}

void Level01::enemyMoveUpdate(float delta)
{
	creepMove();
}

void Level01::creepMove()
{
	int xx, yy, tileGid;
	Point playerPos = this->getKnight()->getPosition();
	float relativeX, relativeY,relativeR,searchX,searchY;
	float cosAlpha,sinAlpha;//角度
	bool hit;

	for (const auto& sprite : this->creepsVec)
	{
		if (!sprite->getAlreadyDead()&&sprite->active==true)//如果这一个小怪没有死，就会随着英雄移动
		{
			
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
			float x = 32 * cos(tempAngle);
			float y = 32 * sin(tempAngle);
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

			if (collision == "true") { //碰撞检测成功									

				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("empty.wav");

				return;

			}

		}
		this->getKnight()->setPosition(position);
		 const Point pos = Point(position.x, position.y - 25);
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


void Level01::armorRecoverUpdate(float delta)
{
	if (this->getKnightBeenSelected()&&(!this->getKnight()->getAlreadyDead()))
          updateHeroArmor(this->getKnight());
}