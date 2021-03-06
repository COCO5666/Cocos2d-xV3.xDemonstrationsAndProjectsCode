//
//  EnemyBase.cpp
//  a4
//
//  Created by student on 15-7-11.
//
//

#include "EnemyBase.h"
#include "ManagerBase.h"
using namespace std;

bool EnemyBase::init()
{
    is_death_=false;
    if (!Sprite::init())
    {
        return false;
    }
    return true;
}
void EnemyBase::onEnterTransitionDidFinish()
{
    Sprite::onEnterTransitionDidFinish();
    scheduleUpdate();
}
void EnemyBase::onExit()
{
    unscheduleUpdate();
    Sprite::onExit();
}
void EnemyBase::initEnemy(int name_index)
{
    //初始化敌机
    enemy_hp_=name_index;
    auto  name_str=String::createWithFormat("enemy%d.png",name_index);
    this->initWithFile(name_str->getCString());
    
    Size size=Director::getInstance()->getWinSize();
    
    /*
     CCRANDOM_0_1()的含义是returns a random float between 0 and 1
     size.width - this->getContentSize().width，设计窗口的宽减去敌机的宽，再乘以0-1之间的一个随机数，得到的结果是一个区间值[0,size.width - this->getContentSize().width]，若再加上敌机宽度的一半，就是设置敌机在设计窗口的上端的任一位置。
    */
    Point pos=Vec2(rand_0_1()*(size.width - this->getContentSize().width) + this->getContentSize().width/2, size.height);
    this->setPosition(pos);

}
void EnemyBase::enemy_death( int enemy_type)
{
    is_death_=true;
    auto animation = Animation::create();
    for (int i = 1; i <= 4; ++i)
	{
        __String  *enemy_name;
        if (enemy_type==2)
        {
           enemy_name = String::createWithFormat("enemy2_down%d.png",i);
        }
        else if (enemy_type==1)
        {
             enemy_name = String::createWithFormat("enemy1_down%d.png",i);
        }
        animation->addSpriteFrameWithFile(enemy_name->getCString());
    }
	animation->setDelayPerUnit(0.1f);
	animation->setLoops(1);

    this->runAction(Sequence::create(Animate::create(animation), RemoveSelf::create(), CallFunc::create(CC_CALLBACK_0(EnemyBase::remove_enemy, this)), NULL));
    
}
void EnemyBase::remove_enemy()
{
    ManagerBase::getInstance()->remove_enemy_list(this);
}
void EnemyBase::set_hp(int hp)
{
    enemy_hp_ = hp;
}

void EnemyBase::update(float delta)
{
     //如果敌机死亡就返回，不更新
    if (is_death_)
    {
        return;
    }
   //如果敌机没死亡，让敌机每帧向下移动5像素
    auto point=this->getPositionY() -3;
    this->setPositionY(point);
    //当敌机的高度位置小于敌机本身的高度时，则把敌机从当前页面移除，并且从敌机数组中移除
    if (point< -this->getContentSize().height)
    {
        /* 
         Removes this node itself from its parent node.
        If the node orphan, then nothing happens.
        @param cleanup   true if all actions and callbacks on this node should be removed, false otherwise.
        */
        this->removeFromParentAndCleanup(true);
        remove_enemy();
    }
}


