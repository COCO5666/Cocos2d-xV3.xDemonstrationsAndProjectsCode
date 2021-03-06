//
//  StartGame.cpp
//  a4
//
//  Created by student on 15-7-10.
//
//

#include "StartGame.h"
#include "MainGame.h"
#include "Select_Plane_Scene.h"
using namespace std;
#include <SimpleAudioEngine.h>
using namespace CocosDenshion;

Scene *  StartGame::createScene()
{
    auto scene=Scene::create();
    auto layer=StartGame::create();
    scene->addChild(layer);
    return scene;
    
}
 bool StartGame::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    auto size=Director::getInstance()->getWinSize();
    auto bg=Sprite::create("bg.png");
    bg->setPosition(240,160);
    addChild(bg);
    auto dic=Dictionary::createWithContentsOfFile("text.xml");
    auto str=(__String *)(dic->objectForKey("title"));
    auto titleLabel=Label::createWithTTF(str->getCString(), "han2.ttf", 50);
    //createWithTTF(str->getCString(), "han2.ttf", 50);
    titleLabel->setColor(Color3B(174,111,23));
	Vec2 v =  Vec2(size.width/2,size.height- titleLabel->getContentSize().height);
    titleLabel->setPosition(v);
	log("%f,%f",v.x,v.y);
    this->addChild(titleLabel);
    
    auto animation=Animation::create();
    for (int i=0; i<=4; i++)
    {
        auto picName=String::createWithFormat("start%d.png",i);
        animation->addSpriteFrameWithFile(picName->getCString());
    }
    animation->setDelayPerUnit(0.2f);
    animation->setLoops(-1);
    auto  sprite=Sprite::create("start1.png");
    sprite->setPosition(Vec2(240,160));
    sprite->runAction(Animate::create(animation));
    this->addChild(sprite);
    
    str=(__String *)(dic->objectForKey("play"));
    auto btnLabel=Label::create();
    btnLabel->setString(str->getCString());
    btnLabel->setSystemFontSize(30);
    auto startItem=MenuItemLabel::create(btnLabel, CC_CALLBACK_1(StartGame:: startGame, this));
    startItem->setPosition(Vec2(size.width/2,size.height*0.2));
    auto menu=Menu::create(startItem, NULL);
    menu->setPosition(Vec2(0,0));
    this->addChild(menu);
    SimpleAudioEngine::getInstance()->playBackgroundMusic("game_music.mp3",true);
    return true;
}

void  StartGame::startGame(Ref *sender)
{
    //程序开始还未写选战斗机类型的类时，为了测试，而把maingame类生成场景
   // auto scene=TransitionFadeTR::create(0.3, MainGame::createScene());
    auto scene=TransitionFadeTR::create(0.3, Select_Plane_Scene::create());
    Director::getInstance()->replaceScene(scene);
}