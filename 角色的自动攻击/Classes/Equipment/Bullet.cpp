#include"Bullet.h"

bool Bullet::init(const std::string& filename, int attack, EDebuffType debufftype)
{
	if (!Sprite::initWithFile(filename))
		return false;
	else
	{
		setAttack(attack);
		setDebuffType(debufftype);
		return true;
	}
}

Bullet* Bullet::create(const std::string& filename, int attack, EDebuffType debufftype)
{
	Bullet* bullet = new Bullet();
	if (bullet && bullet->init(filename, attack, debufftype))
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