//
//  Fruit.h
//  LoveEveryDayToElimate
//
//  Created by xingweihao456 on 15-7-20.
//
//

#ifndef __LoveEveryDayToElimate__Fruit__
#define __LoveEveryDayToElimate__Fruit__

#include <iostream>
//using namespace std;
#include "cocos2d.h"
USING_NS_CC;

class Fruit:public Sprite{
public:
    enum Type
    {
        Apple=1,
        Banner,
        Cherry,
        CyanGrape,
        KiwiFruit,
        Origin,
        Strawberry,
        Watermelon
    };
public:
    Fruit::Type type;
    virtual void setFruitType()=0;
    virtual Fruit::Type getFruitType()=0;
    static ParticleSun * setFlower(int n);
    
};
#endif /* defined(__LoveEveryDayToElimate__Fruit__) */
