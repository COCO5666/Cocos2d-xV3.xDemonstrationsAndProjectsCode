//
//  FruiteAll.h
//  LoveEveryDayToElimate
//
//  Created by xingweihao456 on 15-7-20.
//
//

#ifndef __LoveEveryDayToElimate__FruiteAll__
#define __LoveEveryDayToElimate__FruiteAll__

#include <iostream>
using namespace std;

#include "cocos2d.h"
#include "Fruit.h"
USING_NS_CC;

#pragma Apple
class Apple:public  Fruit
{
public:
    Apple();
    void setFruitType();
    Fruit::Type getFruitType();
};
#pragma Banner
class Banner:public  Fruit
{
    public:
    Banner();
    void setFruitType();
    Fruit::Type getFruitType();
};
#pragma Cherry
class Cherry:public  Fruit
{
    public:
    Cherry();
    void setFruitType();
    Fruit::Type getFruitType();
};
#pragma CyanGrape
class CyanGrape:public  Fruit
{
    public:
    CyanGrape();
    void setFruitType();
    Fruit::Type getFruitType();
};
#pragma KiwiFruit
class KiwiFruit:public  Fruit
{
    public:
    KiwiFruit();
    void setFruitType();
    Fruit::Type getFruitType();
};
#pragma Origin
class Origin:public  Fruit
{
    public:
    Origin();
    void setFruitType();
    Fruit::Type getFruitType();
};
#pragma Strawberry
class Strawberry:public  Fruit
{
    public:
    Strawberry();
    void setFruitType();
    Fruit::Type getFruitType();
};
#pragma Watermelon
class Watermelon:public Fruit
{
    public:
    Watermelon();
    void setFruitType();
    Fruit::Type getFruitType();
};
#endif /* defined(__LoveEveryDayToElimate__FruiteAll__) */
