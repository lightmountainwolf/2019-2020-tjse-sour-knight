#include "box.h"

int Box::getInside() {
	int count = 0;
	if (getMP() != 0) {
		insertMP();
		return 1;
	}
	if (getHP() != 0) {
		insertHP();
		return 1;
	}
	if (getGOLD() == 0 && getBULE() == 0)
	{
		insertWeapon(getweaponIndex());
		return 1;
	}
	if (getGOLD() != 0) {
		insertGOLD();
		count++;
	}
	if (getBULE() != 0) {
		insertBULE();
		count++;
	}
	return count;
}

bool Box::init(const std::string& filename,
	const int allMp,
	const int allHp,
	const int GOLD,
	const int BULE,
	const std::string& weaponIndex)
{
	if (!Sprite::initWithFile(filename))
		return false;
	else
	{
		setOpen(false);
		setHP(allHp);
		setMP(allMp);
		setGOLD(GOLD);
		setBULE(BULE);
		setweaponIndex(weaponIndex);
		return true;
	}
}

void Box::insertMP() {
	Sprite* in = Sprite::create("Props/healMagicPoint.png");
	insideVec.pushBack(in);
}
void Box::insertHP() {
	Sprite* in = Sprite::create("Props/healBlood.png");
	insideVec.pushBack(in);
}
void  Box::insertGOLD() {
	Sprite* in = Sprite::create("Props/gold.png");
	insideVec.pushBack(in);
}
void  Box::insertBULE() {
	Sprite* in = Sprite::create("Props/bule.png");
	insideVec.pushBack(in);
}
void Box::insertWeapon(const std::string& weaponIndex) {
	Sprite* in = Sprite::create(weaponIndex);
	insideVec.pushBack(in);
}

Box* Box::create(const std::string& filename,
	const int allHp,
	const int allMp,
	const int GOLD,
	const int BULE,
	const std::string& weaponIndex)
{
	Box* box = new(std::nothrow)Box();
	if (box && box->init(filename, allMp, allHp, GOLD, BULE, weaponIndex))
	{
		box->autorelease();
		return box;
	}

	CC_SAFE_DELETE(box);
	return nullptr;
}

void Box::initData()//用空指针的形式初始化
{
	setOpen(false);
	setHP(0);
	setMP(0);
	setGOLD(0);
	setBULE(0);
	setweaponIndex("Weapons/weaponBasketball.png");
}

