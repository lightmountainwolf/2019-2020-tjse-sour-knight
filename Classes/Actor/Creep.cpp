#include"Creep.h"

bool Creep::init(const std::string& filename,
	const EDebuffType debufftype,
	const EAttackMode attackmode,
	const int HP,
	const int attack)
{
	if (!Sprite::initWithFile(filename))
		return false;
	else
	{
		setHP(HP);
		setAttack(attack);
		setAttackMode(attackmode);
		setAlreadyDead(false);//没有死
		setReleaseDebuff(debufftype);//敌人会对己方造成的Debuff
		setAttackRadius(attackmode);
		return true;
	}
	//this->scheduleUpdate();
 }



Creep* Creep::create(const std::string& filename,
	const EDebuffType debufftype,
	const EAttackMode attackmode,
	const int HP,
	const int attack)
{
	Creep* creep = new Creep();
	if (creep && creep->init(filename, debufftype, attackmode, HP, attack))
	{
		creep->autorelease();
		return creep;
	}
	else
	{
		CC_SAFE_DELETE(creep);
		return nullptr;
	}
 }

//随机移动
/*void Creep::update(float delta)
{
	Vec2 p = this->getPosition();
	/// ///////////////
	float tempAngle = CCRANDOM_0_1() * 2 * PI;
	float x = 250 * cos(tempAngle);
	float y = 250 * sin(tempAngle);
	auto move = MoveBy::create(20.0f, Vec2(x, y));
	this->runAction(move);
}*/
