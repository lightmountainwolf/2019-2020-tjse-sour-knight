#include"Equipment/Bullet.h"

bool Bullet::init(const std::string& filename, int attack, int frequency, EDebuffType debufftype)
{
	if (!Sprite::initWithFile(filename))
		return false;
	else
	{
		setBulletFilename(filename);
		setAttack(attack);
		setDebuffType(debufftype);
		setAttackFrequency(frequency);
		return true;
	}
}

Bullet* Bullet::create(const std::string& filename, int attack, int frequency, EDebuffType debufftype)
{
	Bullet* bullet = new Bullet();
	if (bullet && bullet->init(filename, attack, frequency, debufftype))
	{
		bullet->autorelease();
		return bullet;
	}
	else
	{
		CC_SAFE_DELETE(bullet);
		return nullptr;
	}
}


bool Bullet::init(const std::string& filename, Bullet* bullet)
{

	if (!Sprite::initWithFile(filename))
		return false;
	else
	{
		setBulletFilename(filename);
		setAttack(bullet->getAttack());
		setDebuffType(bullet->getDebuffType());
		setAttackFrequency(bullet->getAttackFrequency());
		return true;
	}
}

Bullet* Bullet::create(const std::string& filename, Bullet* bullet)
{
	Bullet* tempBullet = new Bullet();
	if (tempBullet && tempBullet->init(filename, bullet))
	{
		tempBullet->autorelease();
		return tempBullet;
	}
	else
	{
		CC_SAFE_DELETE(tempBullet);
		return nullptr;
	}
}