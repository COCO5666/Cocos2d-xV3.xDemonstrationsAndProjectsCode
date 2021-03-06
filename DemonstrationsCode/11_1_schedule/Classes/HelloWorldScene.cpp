#include "HelloWorldScene.h"
USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
//调用系统的scheduleUpdate()函数
this->scheduleUpdate();
    //调用自己定义的update函数
    
this->schedule(schedule_selector(HelloWorld::myupdate),3);
    
    
   // this->scheduleOnce(schedule_selector(HelloWorld::myupdate), 5);
//    auto menuItem=MenuItemFont::create("Stop", CC_CALLBACK_0(HelloWorld::stop, this));
//    auto menu=Menu::create(menuItem, NULL);
//    this->addChild(menu);
    return true;
}
//停止时间调度
 void HelloWorld::stop()
{
    //this->unscheduleUpdate();
  //  this->unschedule(schedule_selector(HelloWorld::myupdate));
    
};

void HelloWorld::myupdate(float f)
{
    log("myupdate:%f",f);
}
void HelloWorld::update(float f)
{
    log("update:%f",f);
}

