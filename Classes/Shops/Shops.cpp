#include "Shops/Shops.h"

bool Shops::init(const std::string& filename, int x, int y)
{
    if (!Sprite::initWithFile(filename))
        return false;
    else
    {
        setX(x);
        setY(y);
        return true;
    }
}

Shops* Shops::create(const std::string& filename, int x, int y)
{
    Shops* shop = new Shops();
    if (shop && shop->init(filename, x, y))
    {
        shop->autorelease();
        return shop;
    }
    else
    {
        CC_SAFE_DELETE(shop);
        return nullptr;
    }
}
int Shops::getLocation1X() 
{
    return getX() - getContentSize().width / 2 + 31 + 10;
}

int Shops::getLocation2X()
{
    return getX() - getContentSize().width / 2 + 190 + 10;
}

int Shops::getLocation3X()
{
    return getX() - getContentSize().width / 2 + 355 + 10;
}

int Shops::getLocationY()
{
    return getY() - getContentSize().height / 2 +267 - 220;
}
