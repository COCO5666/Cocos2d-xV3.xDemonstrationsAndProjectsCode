//
//  SelectPlane_Layer.cpp
//  a4
//
//  Created by student on 15-7-26.
//
//

#include "SelectPlane_Layer.h"
#include  "SelectPlane_Layer.h"

//定义最短滑动距离像素
#define SHORTEST_SLIDE_LENGTH (20)
SelectPlane_Layer::SelectPlane_Layer():page_node_(0),cur_page_node_(0)
{
    
}
SelectPlane_Layer::~SelectPlane_Layer()
{
    
}
//Scene *SelectPlane_Layer::createScene()
//{
//    
//}
 bool SelectPlane_Layer::init()
{
    if (!Layer::init())
    {
       return false;
    }
	//
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(SelectPlane_Layer::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(SelectPlane_Layer::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(SelectPlane_Layer::onTouchEnded, this);
    
    // event dispatcher used to dispatch all kinds of events
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
	size_x = Director::getInstance()->getWinSize().width;
	size_y = Director::getInstance()->getWinSize().height;
    
    return true;
    
}
void SelectPlane_Layer::goToCurNode()
{
    //
    this->runAction(MoveTo::create(0.4f, Point(-cur_page_node_*size_x,0)));
}
void SelectPlane_Layer::addNode(Node *level)
{
    if (level)
    {
      level->setContentSize(Size(size_x, size_y));
      level->setPosition(Point(size_x * page_node_, 0));
      this->addChild(level);
     //
      page_node_++;
    }
}
bool SelectPlane_Layer::onTouchBegan(Touch *touch, Event *event)
{
    log("began");
    touch_down_point_ = touch->getLocation();
	touch_cur_point_ = touch_down_point_;
    return true;
}
void SelectPlane_Layer::onTouchMoved(Touch *touch, Event *event)
{
    log("moved");
    Point touchPoint = touch->getLocation();
	//auto curX = this->getPositionX() + touchPoint.x - touch_cur_point_.x;
   // Point pos_point = Point(curX, getPositionY());
    
	touch_cur_point_ = touchPoint;
}
void SelectPlane_Layer::onTouchEnded(Touch *touch, Event *event)
{
   	touch_up_point_ = touch->getLocation();
	
	//getDistance()函数用来计算touch_up_point和touch_down_point两点之间的距离
	auto dis = touch_up_point_.getDistance(touch_down_point_);
    
    if (dis >= SHORTEST_SLIDE_LENGTH )
    {
		if (touch_down_point_.x > touch_up_point_.x)
        {
			//
			++cur_page_node_;
			if (page_node_ - 1 < cur_page_node_)
            {
                cur_page_node_ = page_node_ - 1;
            }
        }
		else if (touch_down_point_.x < touch_up_point_.x)
        {
			//
			--cur_page_node_;
			if (cur_page_node_ < 0)
				cur_page_node_ = 0;
		}
		//
        goToCurNode();
    }
}