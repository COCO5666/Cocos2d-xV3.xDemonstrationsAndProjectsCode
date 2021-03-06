//
//  PlaneSupport.cpp
//  a4
//
//  Created by student on 15-7-13.

#include "PlaneSupport.h"
PlaneSupport::PlaneSupport()
{
    
}
PlaneSupport::~PlaneSupport()
{
    
}
bool PlaneSupport::init()
{
	if (!Sprite::init())
		return false;
	return true;
}
void PlaneSupport::init_support(int index)
{
	//初始化
	this->initWithFile(String::createWithFormat("support%d.png", index)->getCString());
	auto size = Director::getInstance()->getWinSize();
	auto content_size = this->getContentSize();
    
	//用贝塞尔曲线控制降落伞的降落轨迹
    
    //随机设置降落伞的起始位置
    auto pos_x = rand_0_1()*(size.width - content_size.width) + content_size.width / 2;
	auto pos_y = rand_0_1()*(size.height - content_size.height) + content_size.height / 2;
	auto point = Point(pos_x,size.height);
    this->setPosition(point);
    
    //设置贝塞尔曲线的第一个控制点
	ccBezierConfig bezier;
	pos_x = rand_0_1()*(size.width - content_size.width) + content_size.width / 2;
	pos_y = rand_0_1()*(size.height - content_size.height) + content_size.height / 2;
	bezier.controlPoint_1 = Vec2(pos_x,pos_y);
    
	//设置贝塞尔曲线的第二个控制点
	pos_x = rand_0_1()*(size.width - content_size.width) + content_size.width / 2;
	pos_y = rand_0_1()*(size.height - content_size.height) + content_size.height / 2;
	bezier.controlPoint_2 = Vec2(pos_x, pos_y);
    
    //设置贝塞尔曲线的终点
	pos_x = rand_0_1()*(size.width - content_size.width) + content_size.width / 2;
	bezier.endPosition = Vec2(pos_x, -content_size.height);
    
    //RemoveSelf是一个动作，继承自瞬时动作，该动作用来移除一个节点
	auto bezieraction = BezierTo::create(2.0, bezier);
	auto remover_action = RemoveSelf::create();
    
	auto ac = Sequence::create(bezieraction, remover_action, NULL);
	this->runAction(ac);
}