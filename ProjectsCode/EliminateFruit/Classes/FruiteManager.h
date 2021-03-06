//
//  FruiteManager.h
//  LoveEveryDayToElimate
//
//  Created by xingweihao456 on 15-7-20.
//
//

#ifndef __LoveEveryDayToElimate__FruiteManager__
#define __LoveEveryDayToElimate__FruiteManager__

#include <iostream>
#include "ui/CocosGUI.h"
#include "FruiteAll.h"
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
using namespace ui;

struct Points
{
    int i;
    int j;
    int Value;
};
struct MinxAndMaxX
{
    int _MinX;
    int _MaxX;
};
struct MinYAndMaxY
{
    int _MinY;
    int _MaxY;
};
struct  MinYAndMaxYAndQueue
{
    int _MinY;
    int _MaxY;
    int queue;
};
class FruiteManager:public Menu{
   
public:
    std::vector<Vec2>LeftAndRight[2];
    std::vector<Vec2>UpAndDown[2];
    MinxAndMaxX Horizontal[2];
    MinYAndMaxY Vertical[2];
    Layer * layer;
    MenuItemSprite *** _spriteVector;
    FruiteManager(Layer* _layer);
  struct  Points point[2];
    int   Num[8][8];
    int   LeftandRight(int x,int y,int Num[][8]);
    int   UpandDown(int x,int y,int Num[][8]);
    int   UpandDownCheck(int x,int y,int Num[][8]);
    int   LeftandRightCheck(int x,int y, int Num[][8]);
    bool  ExchangePoint(int x,int y,int i,int j,int Num[][8]);
    void  SrandNumber();
    void  CheckGame();
    void  menuInit();
    void  init_spriteVector();
    void  initHorizontal();
    void  initVertical();
    void  _MenuClick(Ref * sender);
    Fruit*FruiteClass(int Num);
    void  sortMinXAndMaxX(std::vector<Vec2>M,MinxAndMaxX * H);
    void  sortMinYAndMaxY(std::vector<Vec2>M,MinYAndMaxY *V);
    void  setLeftAndRightDisapper(int Minx,int Maxx,int line);
    void  setLeftAndDownDisapper(int MinY,int MaxY,int queue);
    void  SetWait(float dt);
    void  initPoints();
    void  check(float dt);
};
#endif /* defined(__LoveEveryDayToElimate__FruiteManager__) */
