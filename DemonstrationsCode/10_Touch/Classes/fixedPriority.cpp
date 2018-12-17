#include "fixedPriority.h"
#include "spriteTouch.h"
USING_NS_CC;

fixedPriority::fixedPriority(void)
{
}


fixedPriority::~fixedPriority(void)
{
}


Scene* fixedPriority::createScene()
{
    // ����һ���������󣬸ö��󽫻����Զ��ͷųع����ڴ���ͷ�
    auto scene = Scene::create();
    
    // ��������󣬸ö��󽫻����Զ��ͷųع����ڴ���ͷ�
    auto layer = fixedPriority::create();
    
    // ��HelloWorld����Ϊ�ӽڵ���ӵ�����
    scene->addChild(layer);
    
    // ���س�������
    return scene;
}

// on "init" you need to initialize your instance
bool fixedPriority::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    // ����豸֧�ֵĿɼ�OpenGL��ͼ��С�������ڴ�С����
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // �رղ˵�
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(fixedPriority::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // �����˵�
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    // �����ǩ
    auto title = Label::createWithSystemFont("touch oneByeone fixed Priority Test", "",25);
    title->setPosition(visibleSize.width/2, visibleSize.height*0.9);
    this->addChild(title);
    
    // ��ʾ��ǩ
    auto subtitle = Label::createWithSystemFont("Please click block!", "", 18);
    subtitle->setPosition(visibleSize.width/2, visibleSize.height*0.75);
    this->addChild(subtitle);
    
    // ʹ��֮ǰ��Ƶ�TouchableSpriteWithFixedPriority�ഴ���������
    auto sprite1 = spriteTouch::create();
    // ��������ͼƬ
	//sprite1->initWithFile("CyanSquare.png");
	sprite1->setTexture("CyanSquare.png");
    // �������ȼ��������
    sprite1->setPriority(2,"CyanSquare");

    sprite1->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2) + Vec2(-80, 40));
    this->addChild(sprite1,3);
    
    // ʹ��֮ǰ��Ƶ�TouchableSpriteWithFixedPriority�ഴ���������
    auto sprite2 = spriteTouch::create();
    sprite2->setTexture("MagentaSquare.png");
    sprite2->setPriority(3,"MagentaSquare");
    sprite2->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    this->addChild(sprite2, 2);
    
    // ʹ��֮ǰ��Ƶ�TouchableSpriteWithFixedPriority�ഴ���������
    auto sprite3 = spriteTouch::create();
    sprite3->setTexture("YellowSquare.png");
    sprite3->setPriority(1,"YellowSquare");
    sprite3->setPosition(Vec2::ZERO);
    sprite2->addChild(sprite3, 1);    
    return true;
}


void fixedPriority::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

