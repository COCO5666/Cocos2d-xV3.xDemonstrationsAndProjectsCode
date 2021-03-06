#pragma once

#include "cocos2d.h"
USING_NS_CC;

#include <ui/CocosGUI.h>
using namespace ui;

class EnemyBase;//前向声明,为了创建大boss
class  PlaneSupport; //前向声明

class MainGame:public Layer
{
public:
    static Scene * createScene();
    virtual bool init();
    CREATE_FUNC(MainGame);
    void update(float  f );//重写封装好的更新函数，实现背景图片的动画效果
    virtual void onEnterTransitionDidFinish();
    void onExit();

    //单点触摸事件
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);

    Sprite *bg1; //背景精灵1
    Sprite *bg2; //背景精灵2
    Sprite *hero_player_;//战斗机精灵

    void add_enemy(float delta); //随机增加敌机1或2
    void add_bullet(float tm); //随机增加子弹
    void init_hero_plane(int planeType);//初始化战斗机
    void hero_death(int planetype);//战斗机死亡
    void hero_player_action_end(); //战斗机死亡动作结束后，停止增加敌机，并且切换场景到游戏结束

    void is_crash(float tm); //碰撞检测
    void add_support(float tm);//增加供给物品--降落伞
    void add_support_bullet(float tm); //增加供给物品--子弹

    void suspend(Ref *sender);//暂停游戏

    PlaneSupport *plane_support_; //供给物品--降落伞
   
    //战斗机和支援物品的碰撞
    void plane_support_Collision();
    int support_index_;//供给物品下标或索引
    int score_ ;//所得分数，没赋初值，默认为0
    Label * label_score_num_; //所得总分
    Label *label_best_score_num_;//所得总分的最高分
    
    int plane_type_; //战斗机机型
    int enemy_type_;//敌机机型  

};
