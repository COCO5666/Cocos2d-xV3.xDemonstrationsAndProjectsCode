#pragma once

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;

class SelectPlanePage:public Node
{
public:
    static SelectPlanePage *create( int page);
    bool initLevelPage(int page);
    void menuStartCallback(Ref * pSender);
public:
    int page_;
};
