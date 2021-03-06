//
//  GameOver.cpp
//  a4
//
//  Created by student on 15-7-13.
//
//

#include "GameOver.h"
#include "StartGame.h"
#include <SimpleAudioEngine.h>
using namespace CocosDenshion;

Scene *GameOver::createScene()
{
    auto scene = Scene::create();
	auto layer = GameOver::create();
	scene->addChild(layer);
    return scene;
}
bool GameOver::init()
{
    if (!Layer::init())
		return false;
    auto dictionary = Dictionary::createWithContentsOfFile("text.xml");
	auto size = Director::getInstance()->getWinSize();
    auto spr_bg=Sprite::create("bg.png");
    spr_bg->setPosition(Vec2(size.width/2,size.height/2));
    this->addChild(spr_bg);
    
    //添加当前得分标识和显示当前分数的标签
    auto  label_score_Str= ((__String*)(dictionary->objectForKey("score")))->getCString();
    auto label_score=Label::createWithTTF(label_score_Str, "han1.ttf", 20);
    label_score->setAnchorPoint(Vec2(0.5, 0.5));
    label_score->setPosition(Vec2(size.width/2 -label_score->getContentSize().width/2+5,size.height*0.8 - label_score->getContentSize().height/2 -10 ));
    this->addChild(label_score);
    
    auto label_score_num=Label::create();
    label_score_num->setSystemFontSize(20);
    label_score_num->setColor(Color3B(255,0,0));
	label_score_num->setAnchorPoint(Vec2(0, 0.5));
    label_score_num->setPosition(Vec2(label_score->getPositionX()+label_score->getContentSize().width/2 + 10 ,label_score->getPositionY()));
    this->addChild(label_score_num);
    
    //添加最高分标识和、显示最高分的标签
    auto  label_best_score_Str= ((__String*)(dictionary->objectForKey("best_score")))->getCString();
    auto label_best_score=Label::createWithTTF(label_best_score_Str, "han1.ttf", 20);
    label_best_score->setAnchorPoint(Vec2(0.5,0.5));
    label_best_score->setPosition(Vec2(size.width / 2 - label_best_score->getContentSize().width / 2 + 5, label_score->getPositionY() - label_best_score->getContentSize().height - 5));
    this->addChild(label_best_score);
    
    auto  label_best_score_num=Label::create();
    label_best_score_num->setSystemFontSize(20);
    label_best_score_num->setColor(Color3B(255,0,0));
    label_best_score_num->setAnchorPoint(Vec2(0,0.5));
    label_best_score_num->setPosition(Vec2(label_best_score->getPositionX()+label_best_score->getContentSize().width/2 + 10, label_best_score->getPositionY()));
    this->addChild(label_best_score_num);
    
    //获取最高得分和当前得分，并显示到分数列表中
    auto  score_win = UserDefault::getInstance()->getIntegerForKey("best_score");
    auto  score = UserDefault::getInstance()->getIntegerForKey("score");
    label_best_score_num->setString(String::createWithFormat("%d",score_win)->getCString());
    label_score_num->setString(String::createWithFormat("%d",score)->getCString());
    
    // 添加“回到游戏主页”的按钮
    auto btn_label_Str=((__String *)(dictionary->objectForKey("back_menu")))->getCString();
    auto btn_label=Label::createWithTTF(btn_label_Str, "han1.ttf", 20);
    auto start_menu=MenuItemLabel::create(btn_label,CC_CALLBACK_0(GameOver::mene_play, this));
    auto menu=Menu::create(start_menu, NULL);
    menu->setPosition(Vec2(size.width/2,size.height/2));
    this->addChild(menu);
    
    //播放背景音乐
    SimpleAudioEngine::getInstance()->playBackgroundMusic("game_over.mp3",true);
    return true;
    
}
void GameOver::mene_play()
{
    Director::getInstance()->replaceScene(TransitionFade::create(0.5, StartGame::createScene()));
}