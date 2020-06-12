#include "Actor.h"

void Actor::takeDebuff(Debuff* debuff)
{
	_HP -=debuff->getDebuffAttack();
	if (_HP <= 0)
	{
		setHP(0);
		setAlreadyDead(true);
		setAttackRadius(0);
	}
	else
	{
		setAlreadyDead(false);
	}	
}

void Actor::takeDamage(Actor* actor)
{
	_HP -= actor->getAttack();
	if (_HP <= 0)
	{
		setHP(0);
		setAlreadyDead(true);
		setAttackRadius(0);
	}
	else
	{
		setAlreadyDead(false);
	}
}


void Actor::releaseDebuff(Actor* actor)
{
	auto debuff = Debuff::create(this->getReleaseDebuff());
	actor->takeDebuff(debuff);
}

void Actor::releaseDamage(Actor* actor)
{
	actor->takeDamage(actor);
}


bool Actor::init(const std::string& filename)
{
	if (!Sprite::initWithFile(filename))
		return false;
	else
	{
		this->initData();
		return true;
	}

}

Actor* Actor::create(const std::string& fliename)
{
	Actor* actor = new(std::nothrow)Actor();
	if (actor && actor->init(fliename))
	{
		actor->autorelease();
		return actor;
	}

	CC_SAFE_DELETE(actor);
	return nullptr;
}

void Actor::initData()//用空指针的形式初始化
{
	setHP(0);
	setAttack(0);
	setAlreadyDead(true);
	setAttackRadius(0);
	setAttackMode(MELEE);
}