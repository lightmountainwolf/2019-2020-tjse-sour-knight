#include"Buff.h"


bool Buff::init(const std::string& filename,EBuff buffType)
{
	if (!Sprite::initWithFile(filename))
		return false;
	else
	{
		//³õÊ¼Ìõ¼þ
		const int ADDARMOR = 1;
		const int ADDHP = 4;
		const int ADDMP = 50;
		this->setAddArmor(0);
		this->setAddHP(0);
		this->setAddMP(0);
		this->setIceShield(0);
		this->setPoisonShield(0);
		this->setFireShield(0);

		if (buffType == ICE_SHIELD)
			_iceShield = true;
		else if (buffType == POISON_SHIELD)
			_poisonShield = true;
		else if (buffType == FIRE_SHIELD)
			_fireShield = true;
		else if (buffType == ADD_ARMOR)
			_addArmor = ADDARMOR;
		else if (buffType == ADD_HP)
			_addHP = ADDHP;
		else if (buffType == ADD_MP)
			_addMP = ADDMP;
	}
}

Buff* Buff::create(const std::string& filename,EBuff buffType)
{
	
	Buff* buff = new (std::nothrow)Buff();
	if (buff && buff->init(filename,buffType))
	{
		buff->autorelease;
		return buff;
	}
	else
	{
		CC_SAFE_DELETE(buff);
		return nullptr;
	}
}
