#include "Suspand_Layer.h"

bool Suspand_Layer::init()
{
    if (!Layer::init())
    {
        return false;
    }
    auto size=Director::getInstance()->getWinSize();
    auto  bg_name=FileUtils::getInstance()->getWritablePath()+"suspend.png";
    //字符串格式的可读些路径
    auto spr_bg=Sprite::create(bg_name);
    spr_bg->setPosition(Point(size.width/2,size.height/2));
    addChild(spr_bg);
    
    auto dictionary=Dictionary::createWithContentsOfFile("text.xml");
    auto btn_label=Label::create();
    //创建“返回游戏”的按钮
    btn_label->setString(((__String *)(dictionary->objectForKey("back_game")))->getCString());
    btn_label->setSystemFontSize(25);
    auto start_menu=MenuItemLabel::create(btn_label, CC_CALLBACK_1(Suspand_Layer::back_game, this));
    start_menu->setPosition(Vec2(size.width/2,size.height/2));
    auto menu=Menu::create(start_menu, NULL);
    menu->setPosition(Vec2(0,0));
    addChild(menu);
    return true;
}
void Suspand_Layer::back_game(Ref *sender)
{
    Director::getInstance()->popScene();
}