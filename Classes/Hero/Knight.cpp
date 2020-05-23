#include"Knight.h"

//第二个参数是装备的情况，以类的形式开发，将会在后几个版本实现
 bool Knight::init(const std::string& filename, const::String& equipment, EAttackMode attackmode)
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
         setAttackRadius(0);//攻击半径有待于后续更新
         setAttackTarget(nullptr);
         setAttackMode(attackmode);

     }
}


//第二个参数是装备的情况，以类的形式开发，将会在后几个版本实现
 Knight* Knight::create(const std::string& filename, const::String& equipment, EAttackMode attackmode)
{
     Knight* knight = new Knight();
     if (knight && knight->init(filename, equipment, attackmode))
     {
         knight->autorelease;
         return knight;
     }
     CC_SAFE_DELETE(knight);
     return nullptr;
}

void skillOfKnight()//具体实现会在武器的实现后完成
{

}