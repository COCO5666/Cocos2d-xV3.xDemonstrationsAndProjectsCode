#pragma once

#include <iostream>
#include <cocos2d.h>
USING_NS_CC;
class Suspand_Layer:public Layer
{
public:
    virtual  bool init();
    CREATE_FUNC(Suspand_Layer);
public:
    void back_game(Ref *sender);
};
