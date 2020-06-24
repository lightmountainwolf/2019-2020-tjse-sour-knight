#include "Scene/DeadScene.h"
#include "Scene/firstStage.h"
#include "Global/GlobalVariables.h"

using namespace CocosDenshion;
USING_NS_CC;

//还未能完成单击一下的移动动画
//未能实现多角色选择时的贴图不同
Scene* Dead::createScene()
{
    return Dead::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in DeadScene.cpp\n");
}

// on "init" you need to initialize your instance
bool Dead::init()
{

    if (!Scene::init())
    {
        return false;
    }

    log("Dead init");

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    clickNum = 0;

    ////////////////设置背景///////////////////////
    Sprite* background1;
    if (successLevelNum == 5)
    {
       background1 = Sprite::create("Backgrounds/successBackground.png");
    }
    else
    {
       background1 = Sprite::create("Backgrounds/deadBackground.png");
    }
    background1->setAnchorPoint(Point(0, 0));
    background1->setPosition(Point(0, 0));
    addChild(background1);

    ///////////////设置英雄精灵///////////////////
    auto player = Sprite::create("Heroes/knight1.1.png");
    player->setAnchorPoint(Vec2(0, 0));
    player->setPosition(Vec2(90, 660));
    player->setTag(TAG_OF_PLAYER);
    addChild(player);

    //////////////设置继续按钮////////////////////
    auto continueButton = MenuItemImage::create(
        "Buttons/continue-up.png",
        "Buttons/continue-down.png", CC_CALLBACK_1(Dead::menuContinueCallback, this));
    continueButton->setAnchorPoint(Vec2(0, 0));
    continueButton->setPosition(Vec2(visibleSize.width/2 - continueButton->getContentSize().width/2, 160 - continueButton->getContentSize().height / 2));

    auto menu = Menu::create(continueButton, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);

    return true;
}

//continue
void Dead::menuContinueCallback(Ref* pSender)//进入安全屋
{
    
    clickNum++;
    auto player = static_cast <Sprite*>(getChildByTag(TAG_OF_PLAYER));
    //第一次点击触发移动的动画
    if (clickNum == 1) 
    {
        //通过第一关
        if (successLevelNum == 1)
        {
            auto moveTo = MoveTo::create(1, Vec2(360-player->getContentSize().width/2, player->getPosition().y));
            player->runAction(moveTo);
        }
        //通过第二关
        else if (successLevelNum == 2)
        {
            auto moveTo = MoveTo::create(2, Vec2(615 - player->getContentSize().width / 2, player->getPosition().y));
            player->runAction(moveTo);
        }
        //通过第三关
        else if (successLevelNum == 3)
        {
            auto moveTo = MoveTo::create(3, Vec2(860 - player->getContentSize().width / 2, player->getPosition().y));
            player->runAction(moveTo);
        }
        //通过第四关
        else
        {
            auto moveTo = MoveTo::create(4, Vec2(1110 - player->getContentSize().width / 2, player->getPosition().y));
            player->runAction(moveTo);
        }
    }
    //第二次点击返回场景
    else if (clickNum == 2) {
    auto scene = firstStage::createScene();
    Director::getInstance()->replaceScene(scene);
    }
    playSound("sound/ClickSound.mp3");
}