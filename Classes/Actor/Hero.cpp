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
		setMaxHP(HP);
		setArmor(armor);
		setMaxArmor(armor);
		setMP(MP);
		setMaxMP(MP);
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

 void Hero::takeDamage(Actor* actor)
 {
	 _armor -= actor->getAttack();
	 if (_armor < 0)
	 {
		 int hp = abs(this->getArmor());
		 this->setArmor(0);
		 _HP -= hp;
		 if (_HP <= 0)
		 {
			 setHP(0);
			 setAlreadyDead(true);
			 setAttackRadius(0);
		 }
		 else
			 setAlreadyDead(false);
	 }
 }

 void Hero::takeDamage(Bullet* bullet)
 {
	 _armor -= bullet->getAttack();
	 if (_armor < 0)
	 {
		 int hp = abs(this->getArmor());
		 this->setArmor(0);
		 _HP -= hp;
		 if (_HP <= 0)
		 {
			 setHP(0);
			 setAlreadyDead(true);
			 setAttackRadius(0);
		 }
		 else
			 setAlreadyDead(false);
	 }
 }

 