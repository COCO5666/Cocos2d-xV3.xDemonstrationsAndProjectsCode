//
//  Select_Plane_Scene.cpp
//  a4
//
//  Created by student on 15-7-26.
//
//

#include "Select_Plane_Scene.h"
#include "SelectPlane_Layer.h"
#include "SelectPlanePage.h"
#include "StartGame.h"
#include <SimpleAudioEngine.h>
using namespace CocosDenshion;

//宏定义
#define  MUSIC_KEY "music_key" //MUSIC_KEY是背景音乐播放状态键
#define  MUSIC_VOLUMN_KEY "music_volumn_key" //MUSIC_KEY是背景音乐播放状态键
//#define LAYER_NUMBER (2)

Select_Plane_Scene *Select_Plane_Scene::instance_;

Select_Plane_Scene *Select_Plane_Scene::getInstance()
{
    if (instance_!=NULL)
    {
        return instance_;
    }
    return NULL;
}

bool Select_Plane_Scene::init()
{
    if (!Scene::init())
    {
        return false;
    }
    
    instance_=this;
    //1.设置背景和背景音乐
    Size size=Director::getInstance()->getWinSize();
    Sprite *spritebg=Sprite::create("bg.png");
    spritebg->setPosition(Point(size.width/2,size.height/2));
    addChild(spritebg);
    
    //2.设置游戏设置的标题
    auto dic=Dictionary::createWithContentsOfFile("text.xml");
    auto str=(__String *)(dic->objectForKey("setting_Game"));
    auto settingLabel=Label::createWithTTF(str->getCString(), "han2.ttf", 25);
    settingLabel->setColor(Color3B(255,255,255));
    settingLabel->setPosition(240, 280);
    this->addChild(settingLabel);
    
    // 3.背景音乐开关设置按钮
    auto bgSoundStartItem=MenuItemImage::create("soundController.png", "soundController.png");
    auto bgSoundPauseItem=MenuItemImage::create("soundController2.png", "soundController2.png");
    auto itemToggle=MenuItemToggle::createWithCallback(CC_CALLBACK_1(Select_Plane_Scene::bgsoundCallback,this),bgSoundStartItem ,bgSoundPauseItem,NULL);
    itemToggle->setPosition(Vec2(size.width*0.9,size.height*0.2));
    auto menu=Menu::create(itemToggle, NULL);
    menu->setPosition(Vec2(0,0));
    this->addChild(menu,2);
    
    //4.将播放状态写入UserDefault文件，并根据该状态决定音乐按钮的选择状态（播放还是暂停）
    de=UserDefault::getInstance();
    __String wrpath=FileUtils::getInstance()->getWritablePath();//获取可读可写路径
    de->setBoolForKey(MUSIC_KEY, true);
    //如果是第一次进入设置场景，设置背景音乐滑动条默认初始值为50
    de->setFloatForKey(MUSIC_VOLUMN_KEY, 50);
    de->flush();
    
    if (de->getBoolForKey(MUSIC_KEY))
    {
        itemToggle->setSelectedIndex(0);
    }
    else
    {
        itemToggle->setSelectedIndex(1);
    }
    
   //5.设置飞机类型
    SelectPlane_Layer *scrollView=SelectPlane_Layer::create();
    for (int i =1; i<=3; i++)
    {
        auto page=SelectPlanePage::create(i);
        page->setTag(i);
        scrollView->addNode(page);
    }
    
    this->addChild(scrollView);
    
    //6.音量大小调整标签
    auto VolumeLabel=Label::createWithTTF("请拖动滑块选择开关背景音乐和音量", "han2.ttf", 20);
    VolumeLabel->setColor(Color3B(255,255,50));
    VolumeLabel->setPosition(size.width/2, size.height*0.25);
    this->addChild(VolumeLabel);
    
    //7.音量大小调整滑动条
    auto  _slider=Slider::create();
    _slider->loadBarTexture("sliderTrack.png");
    _slider->loadSlidBallTextures("sliderThumb.png", "sliderThumb.png", "sliderThumb.png");
    _slider->loadProgressBarTexture("sliderProgress.png");
    _slider->setScale(0.6);
    //获取之前设置的背景音乐音量
    float musicPercent=UserDefault::getInstance()->getFloatForKey(MUSIC_VOLUMN_KEY);
   
    if (musicPercent==0.0f)
    {
        musicPercent=100.0f;
    }
    //设置背景音乐滑动条的初始值
    _slider->setPercent(musicPercent);
    _slider->setPosition(Vec2(size.width/2,size.height*0.15));
    
    //添加事件监听器,调整背景音乐音量
    _slider->addEventListener(CC_CALLBACK_2(Select_Plane_Scene::changeVolumnProgress,this));
    /*
     事件监听函数回调也可以写在一起，具体如下：
     music_slider->addEventListener([=](Ref* pSender,Slider::EventType type)
     {// 当滑块的百分比发生变化时
        if(type == Slider::EventType::ON_PERCENTAGE_CHANGED)
        {
        // 获得滑动条百分比
        int percent = music_slider->getPercent();
        // 设置背景音乐值为滑动条百分比/100，因为Slider的百分比是1-100，而MusicVolume的取值是0.0-1.0
        SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(float(percent)/100);
        // 存储设置的背景音乐值
        UserDefault::getInstance()->setFloatForKey("musicPercent", percent);
        }
     });
     */
    addChild(_slider);
    return true;
}
 //改变音量进度条的回调函数
void Select_Plane_Scene::changeVolumnProgress(Ref *sender,Slider::EventType type)
{
    auto _slider=(Slider*)sender;
    if (type==Slider::EventType::ON_PERCENTAGE_CHANGED)
    {
        int percent=_slider->getPercent();
        log("%d",percent);
        SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(float (percent)/100);
        UserDefault::getInstance()->setFloatForKey(MUSIC_VOLUMN_KEY, percent);
    }
}

void Select_Plane_Scene::bgsoundCallback(Ref *sender)
{
    //指针 sender 原本执行父类menu，
    auto toggleItem=dynamic_cast<MenuItemToggle *>(sender);
    if (toggleItem->getSelectedIndex()==0)
    {
        SimpleAudioEngine::getInstance()->playBackgroundMusic("game_music.mp3",true);
        
        de->setBoolForKey(MUSIC_KEY,false);
    }
    else if (toggleItem->getSelectedIndex()==1)
    {
        SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
        de->setBoolForKey(MUSIC_KEY,true);
    }
}

