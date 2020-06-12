#include "Debuff.h"

bool Debuff::init(const std::string& filename,EDebuffType debuffType)
{
	if (!Sprite::initWithFile(filename))
		return false;
	else
	{
		setDebuffAttack((debuffType == NORMAL) ? NONE_DEBUFF : DEBUFF_ATTACK);
		return true;
	}
}

Debuff* Debuff::create(const std::string& filename,EDebuffType debuffType)
{
	Debuff* debuff = new Debuff();
	if (debuff && debuff->init(filename,debuffType))
	{
		debuff->autorelease();
		return debuff;
	}
	CC_SAFE_DELETE(debuff);
	return nullptr;
}

bool Debuff::init(EDebuffType debuffType)
{
	if (!Sprite::init())
		return false;
	else
	{
		setDebuffAttack((debuffType == NORMAL) ? NONE_DEBUFF : DEBUFF_ATTACK);
		return true;
	}
}

Debuff* Debuff::create(EDebuffType debuffType)
{
	Debuff* debuff = new Debuff();
	if (debuff && debuff->init(debuffType))
	{
		debuff->autorelease();
		return debuff;
	}
	CC_SAFE_DELETE(debuff);
	return nullptr;
}