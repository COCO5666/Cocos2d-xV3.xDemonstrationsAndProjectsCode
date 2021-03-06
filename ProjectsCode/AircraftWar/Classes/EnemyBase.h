//
//  EnemyBase.h
//  a4
//
//  Created by student on 15-7-11.
//
//

#ifndef __a4__EnemyBase__
#define __a4__EnemyBase__

#include <cocos2d.h>
USING_NS_CC;
#include "cocostudio/CocoStudio.h"
using namespace cocostudio;
using namespace timeline ;

class EnemyBase:public Sprite
{
public:
    virtual bool init();
    CREATE_FUNC(EnemyBase);
    void onExit();
    virtual void onEnterTransitionDidFinish();
    virtual void update(float delta);  
public:
    
    //初始化敌机
    void initEnemy(int index = 1);
    //敌机死亡，能根据敌机类型调用相应的死亡动画
    void enemy_death(int enemy_type);
    //删除敌机
    void remove_enemy();
    //敌机血量的设置和获取函数
    void set_hp(int hp);
    int get_hp() { return enemy_hp_;}
public:

    //敌机血量
    int enemy_hp_;
    //是否爆炸
    bool is_death_;
    int _type;
};
#endif /* defined(__a4__EnemyBase__) */
