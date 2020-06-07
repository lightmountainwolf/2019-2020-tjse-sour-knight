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
		setAttackTarget(nullptr);

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