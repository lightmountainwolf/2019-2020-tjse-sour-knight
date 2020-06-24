#include "Props/props.h"

bool Props::init(const std::string& filename, int type, int x, int y, int radius)
{
    if (!Sprite::initWithFile(filename))
        return false;
    else
    {
        addHP = 2;
        addMP = 30;
        addGold = 8;
        this->type = type;
        xOrigion = x;
        yOrigion = y;
        this->radius = radius;
        isUsed = false;
        if (type == PROPS_DRUG_HP)
        {
            price = PRICE_OF_DRUG_HP;
        }
        else if (type == PROPS_DRUG_MP)
        {
            price = PRICE_OF_DRUG_MP;
        }
        else if (type == PROPS_DRUG_HPMP)
        {
            price = PRICE_OF_DRUG_HPMP;
        }
        else if (type == PROPS_DRUG_HP_FULL)
        {
            price = PRICE_OF_DRUG_HP;
        }
        else if (type == PROPS_DRUG_MP_FULL)
        {
            price = PRICE_OF_DRUG_MP;
        }
        else
        {
            price = 0;
        }

        return true;
    }
}

Props* Props::create(const std::string& filename, int type, int x, int y, int radius)
{
    Props* props = new Props();
    if (props && props->init(filename, type, x, y, radius))
    {
        props->autorelease();
        return props;
    }
    else
    {
        CC_SAFE_DELETE(props);
        return nullptr;
    }
}


bool Props::isInRange(Vec2 playerPos)
{
    if ((playerPos.x >= xOrigion - radius) && (playerPos.x <= xOrigion + radius)
        && (playerPos.y >= yOrigion - radius) && (playerPos.y <= yOrigion + radius))
    {
        return true;
    }
    return false;
}

void Props::makeEffect(Layer* p,Hero* hero)
{
    if (isUsed == false)
    {
        if (type == PROPS_DRUG_HP)
        {
            int OrigionHP = hero->getHP();
            int HP = OrigionHP + addHP;
            if (HP_OF_KNIGHT < HP)
            {
                HP = HP_OF_KNIGHT;
            }
            hero->setHP(HP);
            updateInformationHP(p, hero);
        }
        else if (type == PROPS_DRUG_HP_FULL)
        {
            int HP = HP_OF_KNIGHT;
            hero->setHP(HP);
            updateInformationHP(p, hero);
        }
        else if (type == PROPS_DRUG_MP)
        {
            int OrigionMP = hero->getMP();
            int MP = OrigionMP + addMP;
            if (MP_OF_KNIGHT < MP)
            {
                MP = MP_OF_KNIGHT;
            }
            hero->setMP(MP);
            updateInformationMP(p, hero);
        }
        else if (type == PROPS_DRUG_MP_FULL)
        {
            int MP = MP_OF_KNIGHT;
            hero->setMP(MP);
            updateInformationMP(p, hero);
        }
        else if (type == PROPS_DRUG_HPMP)
        {
            int OrigionHP = hero->getHP();
            int HP = OrigionHP + addHP;
            if (HP_OF_KNIGHT < HP)
            {
                HP = HP_OF_KNIGHT;
            }
            hero->setHP(HP);
            updateInformationHP(p, hero);

            int OrigionMP = hero->getMP();
            int MP = OrigionMP + addMP;
            if (MP_OF_KNIGHT < MP)
            {
                MP = MP_OF_KNIGHT;
            }
            hero->setMP(MP);
            updateInformationMP(p, hero);
        }
        else if (type == PROPS_GOLD)
        {
            int OrigionGold = hero->getGold();
            int gold = OrigionGold + addGold;
            hero->setGold(gold);
            //这个地方写更新金币数量的函数
        }
        else if (type == EMPTY)
        {

        }
        isUsed = true;
    }


}

int Props::getPrice()
{
    return price;
}