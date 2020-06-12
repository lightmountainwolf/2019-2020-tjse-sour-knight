#include"Hero.h"
bool  Hero::init(const std::string& filename,
	const EAttackMode attackmode,
	const float attackradius,
	const int HP,
	const int MP,
	const int armor,
	const int attack)
{
	if (!Sprite::initWithFile(filename))
		return false;
	else
	{
		setHP(HP);
		setArmor(armor);
		setMP(MP);
		setAttack(attack);
		setAttackRadius(attackradius);
		setAttackMode(attackmode);
		setMPConsuming(0);
	}
 }



Hero* Hero::create(const std::string& filename,
	const EAttackMode attackmode,
	const float attackradius,
	const int HP,
	const int MP,
	const int armor,
	const int attack)
{
	Hero* hero = new Hero();
	if (hero && hero->init(filename, attackmode, attackradius, HP, MP, armor, attack))
	{
		hero->release();
		return hero;
	}
	else
	{
		CC_SAFE_DELETE(hero);
		return nullptr;
	}
}

 void Hero::consumeMP()
{
	if (this->getMP() > 0)//还有能量值
	{
		int MP = 0;
		MP = this->getMP() - this->getMPConsuming();
		this->setMP(MP);
	}
	else
	{
		this->setMP(0);
	}
}