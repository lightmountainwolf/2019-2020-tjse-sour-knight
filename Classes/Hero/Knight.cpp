#include"Knight.h"



 bool Knight::init(const std::string& filename, Weapon* weapon)
{
     if (!Sprite::initWithFile(filename))
         return false;
     else
     {
         /*骑士角色的初始状态为：
         HP：7
         Armor:6
         MP:200
         */
         setHP(HP_OF_KNIGHT);
         setArmor(ARMOR_OF_KNIGHT);
         setMP(MP_OF_KNIGHT);
         setAttackMode(weapon->getAttackMode());
         setAttackRadius(weapon->getAttackMode());
         setMPConsuming(weapon->getMPConsuming());
     }
}

 Knight* Knight::create(const std::string& filename, Weapon* weapon)
{
     Knight* knight = new Knight();
     if (knight && knight->init(filename, weapon))
     {
         knight->autorelease();
         return knight;
     }
     else
     {
         CC_SAFE_DELETE(knight);
         return nullptr;
     }
}

