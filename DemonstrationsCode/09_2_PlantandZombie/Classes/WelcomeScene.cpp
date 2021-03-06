//
//  WelcomeScene.cpp
//  twenty
//
//  Created by student on 15-6-13.
//
//

#include "WelcomeScene.h"
#include "MenuScene.h"
USING_NS_CC;
Scene *WelcomeScene::createScene()
{
    auto welcomeScene=Scene::create();
    auto welcomeLayer=WelcomeScene::create();
    welcomeScene->addChild(welcomeLayer);
    return welcomeScene;
}


bool WelcomeScene::init()
{
    if (!Layer::init()) {
        return  false;
    }
    //添加背景精灵,设置z轴为0，
    Size visibleSize=Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto spritebg=Sprite::create("titlescreen.png");
    spritebg->setPosition(Vec2(visibleSize.width/2+origin.x,visibleSize.height/2 + origin.y));
    this->addChild(spritebg,0);
   
    /*总体设计思路：把点击文字放到menu上，把menu、小草精灵、草卷精灵都放到背景精灵上，方便它们一起从下方进入场景,pvz_logo.png添加EaseBackInOut的回震缓冲动作，
     
     */
    
    //添加logo——pvz_logo.png，设置z轴为1，让它位于背景精灵之上
    auto pvzLogo=Sprite::create("pvz_logo.png");
    pvzLogo->setPosition(220, 320);
    pvzLogo->setScale(0.85);
    auto pvzLogomoveTo=EaseBackInOut::create(MoveTo::create(1.0f, Vec2(220, 280)));
    pvzLogo->runAction(pvzLogomoveTo);
    this->addChild(pvzLogo,1);
    
    //添加anode节点，设置z轴为1，用来盛放小草、草的背景精灵、草卷和点击菜单等，为了让他们一起从下方向屏幕移动
    auto anode=Node::create();
    anode->setPosition(240,-30);
    anode->setTag(1);
    this->addChild(anode,1);
    
    //添加草的背景精灵grassDownSprite,设置z轴为0，
    auto grassDownSprite=Sprite::create("down.png");
    grassDownSprite->setPosition(0,0);//240,-180
    grassDownSprite->setScale(0.65);
    grassDownSprite->setTag(0);
    anode->addChild(grassDownSprite,0);
    
     //添加小草精灵grassSprite及其生长进度条grassSpriteTimer，并设置小草进度条效果从左上角往下往右铺展。
    auto grassSprite=Sprite::create("grass.png");
    auto grassSpriteTimer=ProgressTimer::create(grassSprite);
    grassSpriteTimer->setPosition(-5,20);
    grassSpriteTimer->setType(ProgressTimer::Type::BAR);
    grassSpriteTimer->setMidpoint(Vec2(0,0));//从左往上往右生长
    grassSpriteTimer->setScale(0.65);
    anode->addChild(grassSpriteTimer,0);//把grassSpriteTimer添加到grassSprite上
    auto Pt =ProgressTo::create(8.0f,100);//创建进度条
    

    //添加草卷精灵，位于小草的上方，设置节点数为2.
    auto scrollgrass=Sprite::create("scrollgrass.png");
    scrollgrass->setPosition(-90,35);
    scrollgrass->setScale(0.6);
    anode->addChild(scrollgrass,2);
    //设置草卷滚动、缩放和隐藏效果
    auto scrollgrassMoveTo= MoveTo::create(8.0f, Vec2(95,15));
    auto scrollgrassScaleTo=ScaleTo::create(8.0f, 0.05);
    auto scrollgrassSpawn=Spawn::create(scrollgrassScaleTo, scrollgrassMoveTo, NULL);
    auto scrollgrassSeq= Sequence::create(scrollgrassSpawn,Hide::create(),NULL);
    
    //*从下方一起进入的动作执行完后，需停顿5秒，再让草卷开始滚动并缩放；缩小后再隐藏起来，这需要一个sequence顺序序列。这一系列动作由scrollgrass执行*/
    scrollgrass->runAction( Sequence::create(DelayTime::create(3.0),scrollgrassSeq, NULL) );
    
    //添加loading 和点击进入使用的label，并把它放到menu菜单中以备可点击
    Label *clickLable=Label::createWithTTF("L  O  A  D  I  N  G", "fonts/Marker Felt.ttf", 20);
    clickLable->setTag(3);
    auto clickLabelItem=MenuItemLabel::create(clickLable, CC_CALLBACK_0(WelcomeScene::enterMenuScene, this));
    clickLabelItem->setPosition(0,0);//160,25
    clickLabelItem->setColor(Color3B(250,200,100));
    clickLabelItem->setTag(2);
    auto menu=Menu::create(clickLabelItem, NULL);
    menu->setPosition(0,0);
    menu->setTag(1);
    anode->addChild(menu,3);
    
    //调用loadChangeClick( )进入MenuScene
    auto callfun=CallFunc::create(CC_CALLBACK_0(WelcomeScene::loadChangeClick, this));
    
    /*从下方一起进入的动作执行完后，需停顿5秒才让小草开始生长；小草生长当进度完成时，label中的文本由“loading”变成“Click to enter”，这需要一个sequence顺序序列。小草生成的进度通过进度条pt完成，文字变化通过设置一个调用函数CallFunc创建一个变化动作，让grassSpriteTimer执行这两个变化动作*/
    grassSpriteTimer->runAction(Sequence::create(DelayTime::create(3.0),Pt,callfun , NULL) );

    //添加一起从下方进入动作
    auto anodeMoveTo=EaseBackOut::create(MoveTo::create(2.0, Point(240,30)));
    anode->runAction(anodeMoveTo);
    return  true;
}

//进入MenuScene创建的事件
void WelcomeScene:: loadChangeClick( )
{
    auto anode =(Node *)this->getChildByTag(1);
    auto menu=(Menu*)anode->getChildByTag(1);
    auto itemlabel=(MenuItemLabel *)menu->getChildByTag(2);
    auto label=(Label*)itemlabel->getChildByTag(3);
     label->setString("Click to enter!");
     label->setColor(Color3B(255,255,100));
}

//单击文字时进入menuScene页面
void WelcomeScene:: enterMenuScene( )
{
    Scene *scene=MenuScene::createScene();
    auto transitionScene=TransitionSlideInR::create(0.5, scene);
    Director::getInstance()->replaceScene(transitionScene);
}
