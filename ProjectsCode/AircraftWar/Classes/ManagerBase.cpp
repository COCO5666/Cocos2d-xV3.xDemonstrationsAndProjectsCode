//
//  ManagerBase.cpp
//  a4
//
//  Created by student on 15-7-11.
//
//

#include "ManagerBase.h"
//单例模式的应用，用来管理子弹和敌机

ManagerBase *ManagerBase::manager_=NULL;

ManagerBase::ManagerBase()
{
    
}
ManagerBase::~ManagerBase()
{
    
}
ManagerBase * ManagerBase::getInstance()
{
    if (manager_==NULL)
    {
        manager_=new ManagerBase();
    }
    return manager_;
}
void ManagerBase::deleteInstance()
{
    if (manager_)
    {
        delete manager_;
        manager_=NULL;
    }
}


/** @brief pushBack，Adds a new element at the end of the vector, after its current last element.
 *  @note This effectively increases the container size by one,
 *        which causes an automatic reallocation of the allocated storage space
 *        if -and only if- the new vector size surpasses the current vector capacity.
 */

/** @brief Remove a certain object in Vector.
 *  @param object The object to be removed.
 *  @param removeAll Whether to remove all elements with the same value.
 *                   If its value is 'false', it will just erase the first occurrence.
 */

//敌机数组的set和remove处理
void ManagerBase::set_enemy_list(EnemyBase *enemy)
{
    enemy_list_.pushBack(enemy);
}
void ManagerBase::remove_enemy_list(EnemyBase *enemy)
{
    enemy_list_.eraseObject(enemy);
}
//子弹数组的set和remove处理
void ManagerBase::set_bullet_list(Bullet *bullet)
{
      bullet_list_.pushBack(bullet);
}
void ManagerBase:: remove_bullet_list(Bullet *bullet)
{
    bullet_list_.eraseObject(bullet);
}
//大boss子弹数组的set和remove处理
void ManagerBase::set_bossBullet_list(Sprite *bossBullet)
{
    bossBullet_List_.pushBack(bossBullet);
}
void ManagerBase::remove_bossBullt_list(Sprite *bossBullet)
{
    bossBullet_List_.eraseObject(bossBullet);
}

