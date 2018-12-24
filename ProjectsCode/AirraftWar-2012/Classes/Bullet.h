#pragma once

#include <iostream>
#include <cocos2d.h>
USING_NS_CC;

class Bullet: public Sprite
{
public:
	virtual bool init();
	CREATE_FUNC(Bullet);
	void onEnterTransitionDidFinish();
	void onExit();
	void update(float delta);
public:
    //初始化子弹
    //void initBullet(char * bullet_name);
	void initBullet(__String bullet_name);
    
    
};
