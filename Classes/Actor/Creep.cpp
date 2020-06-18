#include"Creep.h"

bool Creep::init(const std::string& filename,
	const EDebuffType debufftype,
	const EAttackMode attackmode,
	const int HP,
	const int attack,
	bool active)
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
		this->active = active;
		return true;
	}
 }



Creep* Creep::create(const std::string& filename,
	const EDebuffType debufftype,
	const EAttackMode attackmode,
	const int HP,
	const int attack,
	bool active)
{
	Creep* creep = new Creep();
	if (creep && creep->init(filename, debufftype, attackmode, HP, attack,active))
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


