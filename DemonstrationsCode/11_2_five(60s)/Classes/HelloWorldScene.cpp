#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}
bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
   
    this->schedule(schedule_selector(HelloWorld::myUpdate),1);
    /**
     delay（最后一个参数）-延时秒数1
     */
     time=60;
    //初始化好一个Lable并把里面的字体进行好转换,用来显示时间
  
   // str=__String::createWithFormat("%d",time);
    countTimeLabel=Label::createWithTTF("60","Marker.ttf",60);
    countTimeLabel->setPosition(240,100);
    this->addChild(countTimeLabel);
    
    //设置停止计时的按钮
    auto stopLabel=Label::createWithTTF("STOP Counting!", "Marker.ttf",60);
    auto stopMenuItem=MenuItemLabel::create(stopLabel, CC_CALLBACK_0(HelloWorld::stop, this));
    stopMenuItem->setPosition(240, 200);
    
    auto menu=Menu::create(stopMenuItem, NULL);
    menu->setPosition(Vec2(0,0));
    this->addChild(menu);
    return true;
}
void HelloWorld::myUpdate(float f)
{
    time-=1;
    if (time>=0)
    {
        str=__String::createWithFormat("%d",time);
        countTimeLabel->setString(str->getCString());
    }
}
void HelloWorld::stop()
{
    this->unschedule(schedule_selector(HelloWorld::myUpdate));
    
}