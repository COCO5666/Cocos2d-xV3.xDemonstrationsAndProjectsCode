#include "SelectPlanePage.h"
#include "MainGame.h"
SelectPlanePage *SelectPlanePage::create( int page)
{
    SelectPlanePage *pRet=new SelectPlanePage();
    if (pRet && pRet->initLevelPage(page))
    {
        pRet ->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}
//初始化选择战斗机的关卡
bool SelectPlanePage::initLevelPage(int page)
{
    if (!Node::init())
    {
        return false;
    }
    //1.添加背景
    page_=page;
    auto size=Director::getInstance()->getWinSize();
    auto sprite=Sprite::create("bg.png");
    sprite->setPosition(Point(size.width/2,size.height/2));
    addChild(sprite);
    sprite->setVisible(false);

    // 2.战斗机动画效果
    auto animation=Animation::create();
    for (int i =1; i<=2; ++i)
    {
        auto spr_name=String::createWithFormat("heros%d_%d.png",page,i);
        animation->addSpriteFrameWithFile(spr_name->getCString());
    }
    animation->setDelayPerUnit(0.2f);
    animation->setLoops(-1);
    
    //3.以其中一张战斗机图创建一个精灵，并让该精灵执行上面的动画，并添加到当前页中
    auto spr_name=String::createWithFormat("heros%d_%d.png",page,1);
    auto plane_sprite=Sprite::create(spr_name->getCString());
    plane_sprite->setPosition(size.width/2, size.height/2+30);
    plane_sprite->runAction(Animate::create(animation));
    addChild(plane_sprite);
    
    //4.从xml读取数据“选择该架”，并将它作为按钮的文字内容，单击该按钮，将进入初始化战斗机的场景
    auto dictionary=Dictionary::createWithContentsOfFile("text.xml");
    auto btn_label=Label::create();
    btn_label->setString(((__String *)(dictionary->objectForKey("select")))->getCString());
    btn_label->setSystemFontSize(25);
    btn_label->setColor(Color3B(255,0,255));
    auto start_menu=MenuItemLabel::create(btn_label, CC_CALLBACK_1(SelectPlanePage::menuStartCallback, this));
    auto menu=Menu::create(start_menu,NULL);
    menu->setPosition(Vec2(size.width/2,size.height*0.35));
    addChild(menu);
    
    return true;
}
void SelectPlanePage::menuStartCallback(Ref * pSender)
{
    auto scene=Scene::create();
    auto main_layer=MainGame::create();
    main_layer->init_hero_plane(page_);
    scene->addChild(main_layer);
    Director::getInstance()->replaceScene(TransitionFadeTR::create(1.0f, scene));
}