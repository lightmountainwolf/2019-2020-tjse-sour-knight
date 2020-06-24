#include"Equipment/Weapon.h"

bool Weapon::init(const std::string& filename, int attack, int mpconsuming, EAttackMode attackmode, EDebuffType debufftype)
{
	if (!Sprite::initWithFile(filename))
		return false;
	else
	{
		setWeaponFilename(filename);
		setAttack(attack);
		setMPConsuming(mpconsuming);
		setAttackMode(attackmode);
		setDebuffType(debufftype);

		return true;
	}
}

Weapon* Weapon::create(const std::string& filename, int attack, int mpconsuming, EAttackMode attactmode, EDebuffType debufftype)
{
	Weapon* weapon = new Weapon();
	if (weapon && weapon->init(filename, attack, mpconsuming, attactmode, debufftype))
	{
		weapon->autorelease();
		return weapon;
	}
	else
	{
		CC_SAFE_DELETE(weapon);
		return nullptr;
	}
}

 Weapon* Weapon::create(const std::string& filename, Weapon* wep)
 {
	 Weapon* weapon = new Weapon();
	 if (weapon&&weapon->init( filename, wep))
	 {
		 weapon->autorelease();
		 return weapon;
	 }
	 else
	 {
		 CC_SAFE_DELETE(weapon);
		 return nullptr;
	 }
 }

 bool Weapon::init(const std::string& filename,Weapon* weapon)
 {
	 if (!Sprite::initWithFile(filename))
		 return false;
	 else
	 {
		 setWeaponFilename(filename);
		 this->setAttack(weapon->getAttack());
		 this->setDebuffType(weapon->getDebuffType());
		 this->setAttackMode(weapon->getAttackMode());
		 this->setMPConsuming(weapon->getMPConsuming());
		 return true;
	 }
 }

 bool Weapon::operator!=(Weapon* wp)
 {
	 bool tag = false;
	 if((this->getWeaponFilename()!=wp->getWeaponFilename())||(this->getAttack()!=wp->getAttack()||(this->getMPConsuming()!=wp->getMPConsuming())
		 ||(this->getAttack()!=wp->getAttackMode())||(this->getDebuffType()!=wp->getDebuffType())))
		 tag=true;
	 return tag;
 }