//
//  FruiteManager.cpp
//  LoveEveryDayToElimate
//
//  Created by xingweihao456 on 15-7-20.
//
//

#include "FruiteManager.h"

FruiteManager::FruiteManager(Layer* _layer)
{
    Menu::init();
    srand(unsigned(time(NULL)));
   // Num[8][8]={0};
	for (int i=0;i<8;i++)
	{
		for (int j=0;j<8;j++)
		{
			Num[i][j]=0;
		}		
	}
	
    SrandNumber();
    init_spriteVector();
    menuInit();
    initPoints();
    initHorizontal();
    initVertical();
   layer=_layer;
    layer->addChild(this);
}
void FruiteManager::initHorizontal()
{
    Horizontal[0]._MinX=-1;
    Horizontal[0]._MaxX=-1;
    Horizontal[1]._MinX=-1;
    Horizontal[1]._MaxX=-1;
}
void FruiteManager::initVertical()
{
    Vertical[0]._MinY=-1;
    Vertical[0]._MaxY=-1;
    Vertical[1]._MinY=-1;
    Vertical[1]._MaxY=-1;
}
void FruiteManager::initPoints()
{
	point[0].i=-1;
	point[0].j=-1;
	point[0].Value=-1;
	point[1].i=-1;
	point[1].j=-1;
	point[1].Value=-1;
	//point[0]={{-1,-1,-1}};
	//point[1]={{-1,-1,-1}};
}
void FruiteManager::menuInit()
{
    for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++)
        {
            Fruit * fruit=FruiteClass(Num[i][j]);
             Fruit*fruit1=FruiteClass(Num[i][j]);
            auto _menuitemImage=MenuItemSprite::create(fruit, fruit1, CC_CALLBACK_1(FruiteManager::_MenuClick,this));
                     _menuitemImage->setPosition((j-4)*40+20,(i-5)*40+20);
            _spriteVector[i][j]=_menuitemImage;
           this->addChild(_menuitemImage);
        }
        this->setPosition(160,200);
    }
}
Fruit* FruiteManager::FruiteClass(int Nums)
{
    Fruit * fruit;
    switch (Nums) {
        case Fruit::Type::Apple:
            fruit=new Apple();
            break;
        case Fruit::Type::Banner:
            fruit=new Banner();
            break;
        case Fruit::Type::Cherry:
            fruit=new Cherry();
            break;
        case Fruit::Type::CyanGrape:
            fruit=new CyanGrape();
            break;
        case Fruit::Type::KiwiFruit:
            fruit=new KiwiFruit();
            break;
        case Fruit::Type::Origin:
            fruit=new Origin();
            break;
        case Fruit::Type::Strawberry:
            fruit=new Strawberry();
            break;
        case Fruit::Type::Watermelon:
            fruit=new Watermelon();
            break;
    }
    return fruit;
}
void FruiteManager::_MenuClick(Ref * sender)
{
    bool disapper=false;
    auto image=  (MenuItemSprite*)sender;
    Point worldPoint=this->convertToWorldSpace(image->getPosition()) ;
     int x=((int)worldPoint.x)/40;
     int y=((int)worldPoint.y)/40;
    if (point[0].i==-1) {
        point[0].i=y;
        point[0].j=x;
        Sprite * sprite=(Sprite*)_spriteVector[y][x]->getSelectedImage();
        Fruit * fruit=(Fruit*)sprite;
        point[0].Value= fruit->getFruitType();
        image->setColor(Color3B::YELLOW);
    }
    else if (point[1].i==-1)
    {
        if ((point[0].i==y)&&(point[0].j==x)) {
            _spriteVector[point[0].i][point[0].j]->setColor(Color3B::WHITE);
            initPoints();
        }
        else
        {
            if (abs(point[0].i-y)+abs(point[0].j-x)==1)
            {
                _spriteVector[y][x]->setColor(Color3B::YELLOW);
                Sprite * sprite=(Sprite*)_spriteVector[y][x]->getSelectedImage();
                Fruit * fruit=(Fruit*)sprite;
                point[1].Value=fruit->getFruitType();
                point[1].i=y;
                point[1].j=x;
                Num[y][x]=point[0].Value;
                Num[point[0].i][point[0].j]=point[1].Value;
                if (LeftandRight(point[0].i, point[0].j, Num))
                {
                    disapper=true;
                    LeftandRightCheck(point[0].i, point[0].j, Num);
                }
                else
                {
                    
                    if (UpandDown(point[0].i, point[0].j, Num)) {
                        disapper=true;
                        UpandDownCheck(point[0].i, point[0].j, Num);
                    }
                }
                if (LeftandRight(point[1].i, point[1].j, Num))
                {
                    disapper=true;
                     LeftandRightCheck(point[1].i, point[1].j, Num);
                }
                else
                {
                    if (UpandDown(point[1].i, point[1].j, Num))
                    {
                        disapper=true;
                        UpandDownCheck(point[1].i, point[1].j, Num);
                    }
                }
                if (disapper)
                {
                    auto moveTo=MoveTo::create(0.2,  _spriteVector[point[0].i][point[0].j]->getPosition());
                    _spriteVector[point[1].i][point[1].j]->runAction(moveTo);
                    auto moveTo1=MoveTo::create(0.2,  _spriteVector[point[1].i][point[1].j]->getPosition());
                    _spriteVector[point[0].i][point[0].j]->runAction(moveTo1);
                    MenuItemSprite * image=_spriteVector[point[0].i][point[0].j];
                    _spriteVector[point[0].i][point[0].j]=_spriteVector[point[1].i][point[1].j];
                    _spriteVector[point[1].i][point[1].j]=image;
                    this->scheduleOnce(schedule_selector(FruiteManager::SetWait), 0.2);
                    disapper=false;
                }
                else
                {
                    _spriteVector[point[0].i][point[0].j]->setColor(Color3B::WHITE);
                    _spriteVector[point[1].i][point[1].j]->setColor(Color3B::WHITE);
                    Num[y][x]=point[1].Value;
                    Num[point[0].i][point[0].j]=point[0].Value;
                   initPoints();
                }
                
            }
            else
            {
                _spriteVector[point[0].i][point[0].j]->setColor(Color3B::WHITE);
                initPoints();
  
            }
        }
      
    }
}


void  FruiteManager::SetWait(float dt)
{
    
    _spriteVector[point[0].i][point[0].j]->setColor(Color3B::WHITE);
    _spriteVector[point[1].i][point[1].j]->setColor(Color3B::WHITE);
    std::vector<MinYAndMaxYAndQueue*> _Points;
    MinxAndMaxX Allline;
    if (UpAndDown[0].size()!=0) {
        sortMinYAndMaxY(UpAndDown[0], &Vertical[0]);
    }
    if (UpAndDown[1].size()!=0) {
        sortMinYAndMaxY(UpAndDown[1], &Vertical[1]);
    }
    if (LeftAndRight[0].size()!=0) {
        sortMinXAndMaxX(LeftAndRight[0], &Horizontal[0]);
    }
    if (LeftAndRight[1].size()!=0) {
        sortMinXAndMaxX(LeftAndRight[1], &Horizontal[1]);
    }
    if (UpAndDown[0].size()!=0)
    {
        sortMinYAndMaxY(UpAndDown[0], &Vertical[0]);
        
        if (UpAndDown[1].size()!=0)
        {
            sortMinYAndMaxY(UpAndDown[1], &Vertical[1]);
            
            if (point[0].j==point[1].j)
            {
                int MinY=Vertical[0]._MinY<Vertical[1]._MinY?Vertical[0]._MinY:Vertical[1]._MinY;
                int MaxY=Vertical[0]._MaxY<Vertical[1]._MaxY?Vertical[1]._MaxY:Vertical[0]._MaxY;
                MinYAndMaxYAndQueue * queue=new MinYAndMaxYAndQueue;
                queue->_MinY=MinY;
                queue->_MaxY=MaxY;
                queue->queue=point[0].j;
                _Points.push_back(queue);
                Allline._MinX=point[0].j;
                Allline._MaxX=point[0].j;
            }
            else
            {
                Allline._MinX=point[0].j<point[1].j?point[0].j:point[1].j;
                Allline._MaxX=point[0].j>point[1].j?point[0].j:point[1].j;
                MinYAndMaxYAndQueue * queue1=new MinYAndMaxYAndQueue;
                MinYAndMaxYAndQueue * queue2=new MinYAndMaxYAndQueue;
                queue1->_MinY=Vertical[0]._MinY;
                queue1->_MaxY=Vertical[0]._MaxY;
                queue1->queue=point[0].j;
                queue2->_MinY=Vertical[1]._MinY;
                queue2->_MaxY=Vertical[1]._MaxY;
                queue2->queue=point[1].j;
                if (point[0].j<point[1].j) {
                    _Points.push_back(queue1);
                    _Points.push_back(queue2);
                }
                else
                {
                    _Points.push_back(queue2);
                    _Points.push_back(queue1);
                }
                
            }
            
        }
        else if(LeftAndRight[0].size()!=0)
        {
            if (UpAndDown[0].at(0).y>=Horizontal[0]._MinX&&UpAndDown[0].at(0).y<=Horizontal[0]._MaxX)
            {
                for (int m=Horizontal[0]._MinX; m<=Horizontal[0]._MaxX; m++)
                {
                    MinYAndMaxYAndQueue * queue1=new MinYAndMaxYAndQueue;
                    if (m==UpAndDown[0].at(0).y)
                    {
                        if (Vertical[0]._MinY>LeftAndRight[0].at(0).x)
                        {
                            queue1->_MinY=LeftAndRight[0].at(0).x;
                            queue1->_MaxY=Vertical[0]._MaxY;
                            queue1->queue=m;
                        }
                        else
                        {
                            queue1->_MinY=Vertical[0]._MinY;
                            queue1->_MaxY=LeftAndRight[0].at(0).x;
                            queue1->queue=m;
                            
                        }
                    }
                    else
                    {
                        queue1->_MinY=LeftAndRight[0].at(0).x;
                        queue1->_MaxY=LeftAndRight[0].at(0).x;
                        queue1->queue=m;
                    }
                    _Points.push_back(queue1);
                    
                }
            }
            else
            {
                
                for (int m=Horizontal[0]._MinX; m<=Horizontal[0]._MaxX; m++)
                {
                    MinYAndMaxYAndQueue * queue1=new MinYAndMaxYAndQueue;
                    queue1->_MinY=LeftAndRight[0].at(0).x;
                    queue1->_MaxY=LeftAndRight[0].at(0).x;
                    queue1->queue=m;
                    _Points.push_back(queue1);
                }
                
                MinYAndMaxYAndQueue * queue2=new MinYAndMaxYAndQueue;
                queue2->_MinY=Vertical[0]._MinY;
                queue2->_MaxY=Vertical[0]._MaxY;
                queue2->queue=UpAndDown[0].at(0).y;
                auto begin=_Points.begin();
                if (UpAndDown[0].at(0).x<Horizontal[0]._MaxX) {
                    _Points.insert(begin,queue2);
                }
                else
                {
                    _Points.push_back(queue2);
                }
            }
        }
        else if(LeftAndRight[0].size()==0)
        {
            MinYAndMaxYAndQueue * queue2=new MinYAndMaxYAndQueue;
            queue2->_MaxY=Vertical[0]._MaxY;
            queue2->_MinY=Vertical[0]._MinY;
            queue2->queue=UpAndDown[0].at(0).y;
            _Points.push_back(queue2);
            
        }
        
    }
    else if (UpAndDown[0].size()==0)
    {
        if(LeftAndRight[0].size()!=0)
        {
            if (LeftAndRight[1].size()!=0)
            {
                
                int Minx=Horizontal[0]._MinX<Horizontal[1]._MinX ? Horizontal[0]._MinX:Horizontal[1]._MinX;
                int Maxx=Horizontal[0]._MaxX>Horizontal[1]._MaxX ? Horizontal[0]._MaxX :Horizontal[1]._MaxX;
                if (point[0].i==point[1].i)
                {
                    for (int m=Minx; m<=Maxx; m++)
                    {
                        MinYAndMaxYAndQueue * _queue=new MinYAndMaxYAndQueue;
                        _queue->_MaxY=LeftAndRight[0].at(0).x;
                        _queue->_MinY=LeftAndRight[0].at(0).x;
                        _queue->queue=m;
                        _Points.push_back(_queue);
                    }
                }
                else if(point[0].i!=point[1].i)
                {
                    int MinBig =Horizontal[0]._MinX>Horizontal[1]._MinX ? Horizontal[0]._MinX:Horizontal[1]._MinX;
                    int MaxMinBig=Horizontal[0]._MaxX<Horizontal[1]._MaxX ? Horizontal[0]._MaxX :Horizontal[1]._MaxX;
                    if (point[0].i>point[1].i)
                    {
                        if (Horizontal[0]._MinX==Minx)
                        {
                            for (int m =Minx; m<MinBig; m++)
                            {
                                MinYAndMaxYAndQueue * _queue=new MinYAndMaxYAndQueue;
                                _queue->_MaxY=LeftAndRight[0].at(0).x;
                                _queue->_MinY=LeftAndRight[0].at(0).x;
                                _queue->queue=m;
                                _Points.push_back(_queue);
                            }
                            for (int m=MinBig; m<=MaxMinBig; m++)
                            {
                                MinYAndMaxYAndQueue * _queue=new MinYAndMaxYAndQueue;
                                _queue->_MaxY=LeftAndRight[0].at(0).x;
                                _queue->_MinY=point[1].i;
                                _queue->queue=m;
                                _Points.push_back(_queue);
                            }
                            if (Horizontal[0]._MaxX==Maxx)
                            {
                                for (int m=MaxMinBig+1; m<=Maxx; m++)
                                {
                                    MinYAndMaxYAndQueue * _queue=new MinYAndMaxYAndQueue;
                                    _queue->_MaxY=LeftAndRight[0].at(0).x;
                                    _queue->_MinY=LeftAndRight[0].at(0).x;
                                    _queue->queue=m;
                                    _Points.push_back(_queue);
                                }
                            }
                            else
                            {
                                for (int m=MaxMinBig+1; m<=Maxx; m++)
                                {
                                    MinYAndMaxYAndQueue * _queue=new MinYAndMaxYAndQueue;
                                    _queue->_MaxY=LeftAndRight[1].at(0).x;
                                    _queue->_MinY=LeftAndRight[1].at(0).x;
                                    _queue->queue=m;
                                    _Points.push_back(_queue);
                                }
                            }
                        }
                        else
                        {
                            if ( Horizontal[1]._MinX==Minx)
                            {
                                for (int m=Minx; m<MinBig; m++)
                                {
                                    MinYAndMaxYAndQueue * _queue=new MinYAndMaxYAndQueue;
                                    _queue->_MaxY=LeftAndRight[1].at(0).x;
                                    _queue->_MinY=LeftAndRight[1].at(0).x;
                                    _queue->queue=m;
                                    _Points.push_back(_queue);
                                }
                                for (int m=MinBig; m<=MaxMinBig; m++)
                                {
                                    MinYAndMaxYAndQueue * _queue=new MinYAndMaxYAndQueue;
                                    _queue->_MaxY=point[0].i;
                                    _queue->_MinY=point[1].i;
                                    _queue->queue=m;
                                    _Points.push_back(_queue);
                                }
                                if (Horizontal[0]._MaxX==Maxx)
                                {
                                    for (int m=MaxMinBig+1; m<=Maxx; m++)
                                    {
                                        MinYAndMaxYAndQueue * _queue=new MinYAndMaxYAndQueue;
                                        _queue->_MaxY=LeftAndRight[0].at(0).x;
                                        _queue->_MinY=LeftAndRight[0].at(0).x;
                                        _queue->queue=m;
                                        _Points.push_back(_queue);
                                    }
                                }
                                else
                                {
                                    for (int m=MaxMinBig+1; m<=Maxx; m++)
                                    {
                                        MinYAndMaxYAndQueue * _queue=new MinYAndMaxYAndQueue;
                                        _queue->_MaxY=LeftAndRight[1].at(0).x;
                                        _queue->_MinY=LeftAndRight[1].at(0).x;
                                        _queue->queue=m;
                                        _Points.push_back(_queue);
                                    }
                                }
                            }
                            
                        }
                    }
                    else
                    {
                        if (point[0].i<point[1].i)
                        {
                            if (Horizontal[0]._MinX==Minx)
                            {
                                for (int m =Minx; m<MinBig; m++)
                                {
                                    MinYAndMaxYAndQueue * _queue=new MinYAndMaxYAndQueue;
                                    _queue->_MaxY=LeftAndRight[0].at(0).x;
                                    _queue->_MinY=LeftAndRight[0].at(0).x;
                                    _queue->queue=m;
                                    _Points.push_back(_queue);
                                }
                                for (int m=MinBig; m<=MaxMinBig; m++)
                                {
                                    MinYAndMaxYAndQueue * _queue=new MinYAndMaxYAndQueue;
                                    _queue->_MaxY=point[1].i;
                                    _queue->_MinY=point[0].i;
                                    _queue->queue=m;
                                    _Points.push_back(_queue);
                                }
                                if (Horizontal[0]._MaxX==Maxx)
                                {
                                    for (int m=MaxMinBig+1; m<=Maxx; m++)
                                    {
                                        MinYAndMaxYAndQueue * _queue=new MinYAndMaxYAndQueue;
                                        _queue->_MaxY=LeftAndRight[0].at(0).x;
                                        _queue->_MinY=LeftAndRight[0].at(0).x;
                                        _queue->queue=m;
                                        _Points.push_back(_queue);
                                    }
                                }
                                else
                                {
                                    for (int m=MaxMinBig+1; m<=Maxx; m++)
                                    {
                                        MinYAndMaxYAndQueue * _queue=new MinYAndMaxYAndQueue;
                                        _queue->_MaxY=LeftAndRight[1].at(0).x;
                                        _queue->_MinY=LeftAndRight[1].at(0).x;
                                        _queue->queue=m;
                                        _Points.push_back(_queue);
                                    }
                                }
                            }
                            else
                            {
                                if ( Horizontal[1]._MinX==Minx)
                                {
                                    for (int m =Minx; m<MinBig; m++)
                                    {
                                        MinYAndMaxYAndQueue * _queue=new MinYAndMaxYAndQueue;
                                        _queue->_MaxY=LeftAndRight[1].at(0).x;
                                        _queue->_MinY=LeftAndRight[1].at(0).x;
                                        _queue->queue=m;
                                        _Points.push_back(_queue);
                                    }
                                    for (int m=MinBig; m<=MaxMinBig; m++)
                                    {
                                        MinYAndMaxYAndQueue * _queue=new MinYAndMaxYAndQueue;
                                        _queue->_MaxY=point[1].i;
                                        _queue->_MinY=point[0].i;
                                        _queue->queue=m;
                                        _Points.push_back(_queue);
                                    }
                                    if (Horizontal[0]._MaxX==Maxx)
                                    {
                                        for (int m=MaxMinBig+1; m<=Maxx; m++)
                                        {
                                            MinYAndMaxYAndQueue * _queue=new MinYAndMaxYAndQueue;
                                            _queue->_MaxY=LeftAndRight[0].at(0).x;
                                            _queue->_MinY=LeftAndRight[0].at(0).x;
                                            _queue->queue=m;
                                            _Points.push_back(_queue);
                                        }
                                    }
                                    else
                                    {
                                        for (int m=MaxMinBig+1; m<=Maxx; m++)
                                        {
                                            MinYAndMaxYAndQueue * _queue=new MinYAndMaxYAndQueue;
                                            _queue->_MaxY=LeftAndRight[1].at(0).x;
                                            _queue->_MinY=LeftAndRight[1].at(0).x;
                                            _queue->queue=m;
                                            _Points.push_back(_queue);
                                        }
                                    }
                                }
                                
                            }
                        }
                        
                    }
                    
                }
                
                
            }
            else if(LeftAndRight[1].size()==0)
            {
                for (int m =Horizontal[0]._MinX; m<=Horizontal[0]._MaxX; m++)
                {
                    MinYAndMaxYAndQueue * _queue=new MinYAndMaxYAndQueue;
                    _queue->_MinY=LeftAndRight[0].at(0).x;
                    _queue->_MaxY=LeftAndRight[0].at(0).x;
                    _queue->queue=m;
                    _Points.push_back(_queue);
                }
            }
        }
    }
    
    for (int i=0; i<_Points.size();i++)
    {
        for (int j=_Points.at(i)->_MinY; j<=_Points.at(i)->_MaxY; j++)
        {
           
           ParticleSun * spflower= Fruit::setFlower( Num[j][_Points.at(i)->queue]);
            Point _p= _spriteVector[j][_Points.at(i)->queue]->getPosition()+Point(160,200);
            spflower->setPosition(_p);
            layer->addChild(spflower,1);
            _spriteVector[j][_Points.at(i)->queue]->removeFromParent();
        }
    }
    for (int i=0; i<_Points.size();i++)
    {
        int count=_Points.at(i)->_MaxY-_Points.at(i)->_MinY;
        for (int j=_Points.at(i)->_MaxY+1; j<=7; j++)
        {
            Num[j-(count+1)][_Points.at(i)->queue]=Num[j][_Points.at(i)->queue];
            _spriteVector[j-(count+1)][_Points.at(i)->queue]= _spriteVector[j][_Points.at(i)->queue];
            auto moveBy=MoveBy::create(0.2,Vec2(0,-40*(count+1)));
            _spriteVector[j-(count+1)][_Points.at(i)->queue]->runAction(moveBy);
        }
    }
    for (int i=0; i<_Points.size();i++)
    {
        int count=_Points.at(i)->_MaxY-_Points.at(i)->_MinY;
        for (int j=_Points.at(i)->_MinY; j<=_Points.at(i)->_MaxY; j++)
        {
            int K=rand()%6+1;
            Num[7-j+_Points.at(i)->_MinY][_Points.at(i)->queue]=K;
            Fruit * _fruit1=FruiteClass(K);
            Fruit * _fruit2=FruiteClass(K);
            MenuItemSprite * image=MenuItemSprite::create(_fruit1, _fruit2, CC_CALLBACK_1(FruiteManager::_MenuClick,this));
            image->setPosition((_Points.at(i)->queue-4)*40+20,(count -j+_Points.at(i)->_MinY)*40+300);
            this->addChild(image);
            _spriteVector[7-j+_Points.at(i)->_MinY][_Points.at(i)->queue]=image;
            auto moveTo=MoveTo::create(0.2, Vec2((_Points.at(i)->queue-4)*40+20, (7-j+_Points.at(i)->_MinY-5)*40+20));
            image->runAction(moveTo);
        }
    }
    
    initHorizontal();
    initVertical();
    initPoints();
    UpAndDown[0].clear();
    UpAndDown[1].clear();
    LeftAndRight[0].clear();
    LeftAndRight[1].clear();
    for (int i=0; i<_Points.size(); i++)
    {
        delete _Points.at(i);
    }
    _Points.clear();
    this->scheduleOnce(schedule_selector(FruiteManager::check), 0.2);
}
void FruiteManager::check(float dt)
{
    int K;
    bool disapper=false;
    for (int i=7; i>=0; i--) {
        for (int j=0; j<=7; j++)
        {
            K=j;
            if (ExchangePoint(0, 0, i, j, Num))
            {
                
                if (LeftandRight(point[0].i, point[0].j, Num))
                {
                    disapper=true;
                    LeftandRightCheck(point[0].i, point[0].j, Num);
                }
                else
                {
                    disapper=true;
                    if (UpandDown(point[0].i, point[0].j, Num)) {
                        UpandDownCheck(point[0].i, point[0].j, Num);
                    }
                }
                if (LeftandRight(point[1].i, point[1].j, Num)) {
                    disapper=true;
                    LeftandRightCheck(point[1].i, point[1].j, Num);
                }
                else
                {
                    disapper=true;
                    if (UpandDown(point[1].i, point[1].j, Num)) {
                        UpandDownCheck(point[1].i, point[1].j, Num);
                    }
                }
                disapper=true;
                this->scheduleOnce(schedule_selector( FruiteManager::SetWait) , 0.2);
                break;
            }
            
        }
        if (disapper)
        {
            disapper=false;
            break;
        }
        else if(K==7&&i==0)
        {
            initPoints();
        }
    }

}
void  FruiteManager::sortMinXAndMaxX(std::vector<Vec2>M,MinxAndMaxX * H)
{
    int count =M.size();
    int  t=M.at(0).y;
    int t1=M.at(0).y;;
    for (int i=0; i<count-1; i++) {
        if (t<M.at(i+1).y) {
            t=M.at(i+1).y;
        }
        if (t1>M.at(i+1).y) {
            t1=M.at(i+1).y;
        }
    }
    H->_MaxX=t;
    H->_MinX=t1;
}
void FruiteManager::sortMinYAndMaxY(std::vector<Vec2>M,MinYAndMaxY *V)
{
    int count =M.size();
    int  t=M.at(0).x;
    int t1=M.at(0).x;;
    for (int i=0; i<count-1; i++) {
        if (t<M.at(i+1).x) {
            t=M.at(i+1).x;
        }
        if (t1>M.at(i+1).x) {
            t1=M.at(i+1).x;
        }
    }
    V->_MaxY=t;
    V->_MinY=t1;
}
void  FruiteManager::init_spriteVector()
{
    _spriteVector=new MenuItemSprite**[8]();
    for (int i=0; i<8; i++) {
        MenuItemSprite**sprite=new  MenuItemSprite*[8]();
        _spriteVector[i]=sprite;
    }

}
void  FruiteManager::SrandNumber()
{
    for (int i=0; i<8; i++) {
        for (int j=0; j<8; j++) {
            Num[i][j]=rand()%6+1;
            if (i>0&&i<10) {
                while (true) {
                    if (LeftandRight(i, j, Num)) {
                        Num[i][j]=rand()%6+1;
                        continue;
                    }
                    else
                    {
                        if (UpandDown(i, j, Num)) {
                            Num[i][j]=rand()%6+1;
                            continue;
                        }
                        else
                        {
                            break;
                        }
                    }
                }
            }
        }
    }
}
 void  FruiteManager::CheckGame()
{
    bool  disapper=false;
    for (int i=0; i<8; i++)
    {
        for (int j=0; j<8; j++)
        {
            if (!disapper)
            {
                if (j<7) {
                    if ((disapper=ExchangePoint(0,1,i,j,Num)))
                    {
                        break;
                    }
                }
                if (j>0) {
                    if ((disapper=ExchangePoint(0,-1,i,j,Num)))
                    {
                        break;
                    }
                }
                if (i<7) {
                    if ((disapper=ExchangePoint(1,0,i,j,Num)))
                    {
                        break;
                    }
                }
                if (i>0) {
                    if ((disapper=ExchangePoint(-1,0,i,j,Num)))
                    {
                        break;
                    }
                }
            }
        }
        
        if (disapper) {
            break;
        }
    }
    if (disapper) {
        cout<<point[0].i<<","<<point[0].j<<"\t"<<"Value:"<<point[0].Value<<endl;
        cout<<point[1].i<<","<<point[1].j<<"\t"<<"Value:"<<point[1].Value<<endl;
    }
}
bool  FruiteManager:: ExchangePoint(int x,int y,int i,int j,int Num[][8])
{
    
    bool disapper=false;
    int   x1=Num[i][j];
    int   y1=Num[i+x][j+y];
    Num[i][j]=y1;
    Num[i+x][j+y]=x1;
    if (LeftandRight(i, j, Num)) {
        disapper=true;
    }
    else
    {
        if (UpandDown(i, j,Num))
        {
            disapper=true;
        }
    }
    Num[i][j]=x1;
    Num[i+x][j+y]=y1;
    point[0].i=i;
    point[0].j=j;
    point[0].Value=Num[i][j];
    point[1].i=i+x;
    point[1].j=j+y;
    point[1].Value=Num[i+x][j+y];
    return disapper;
}
int FruiteManager::UpandDown(int x,int y,int Num[][8])
{
    int total=1;
    int i=x;
    int j=y;
    while (i>0)
    {
        if (Num[i][j]==Num[i-1][j]&&Num[i][j]!=0)
        {
            total++;
            i=i-1;

        }
        else
        {
            break;
        }
    }
    i=x;
    while (i<7)
    {
        if (Num[i][j]==Num[i+1][j]&&Num[i][j]!=0)
        {
            total++;
            i=i+1;
    
        }
        else
        {
            break;
        }
    }
    if (total>=3)
    {
        return total;
    }
    return 0;
}
int FruiteManager::UpandDownCheck(int x,int y,int Num[][8])
{
    int total=1;
    int i=x;
    int j=y;
    vector<Vec2> * M;
    if (UpAndDown[0].size()==0) {
        UpAndDown[0].push_back(Vec2(i, j));
        M=&UpAndDown[0];
    }
    else
    {
        UpAndDown[1].push_back(Vec2(i, j));
        M=&UpAndDown[1];
    }
    while (i>0)
    {
        if (Num[i][j]==Num[i-1][j]&&Num[i][j]!=0)
        {
            total++;
            i=i-1;
            M->push_back(Vec2(i, j));

        }
        else
        {
            break;
        }
    }
    i=x;
    while (i<7)
    {
        if (Num[i][j]==Num[i+1][j]&&Num[i][j]!=0)
        {
            total++;
            i=i+1;
            M->push_back(Vec2(i, j));
        }
        else
        {
            break;
        }
    }
    if (total>=3)
    {
        return total;
    }
    return 0;
}
int  FruiteManager::LeftandRightCheck(int x,int y, int Num[][8])
{
    
    int total=1;
    int i=x;
    int j=y;
    vector<Vec2> * M;
    if (LeftAndRight[0].size()==0) {
        LeftAndRight[0].push_back(Vec2(i, j));
        M= &LeftAndRight[0];
    }
    else
    {
        LeftAndRight[1].push_back(Vec2(i, j));
        M= &LeftAndRight[1];
    }
   
    while (j>0)
    {
        if (Num[i][j]==Num[i][j-1]&&Num[i][j]!=0)
        {
            total++;
            j=j-1;
            M->push_back(Vec2(i, j));
        }
        else
        {
            break;
        }
    }
    j=y;
    while (j<7) {
        if (Num[i][j]==Num[i][j+1]&&Num[i][j]!=0)
        {
            total++;
            j=j+1;
            M->push_back(Vec2(i, j));
        }
        else
        {
            break;
        }
    }
    if (total>=3)
    {
        return total;
    }
    else
    {
        return 0;
    }
}
int  FruiteManager::LeftandRight(int x,int y, int Num[][8])
{
    int total=1;
    int i=x;
    int j=y;
    
    while (j>0)
    {
        if (Num[i][j]==Num[i][j-1]&&Num[i][j]!=0)
        {
            total++;
            j=j-1;
            
        }
        else
        {
            break;
        }
    }
    j=y;
    while (j<7) {
        if (Num[i][j]==Num[i][j+1]&&Num[i][j]!=0)
        {
            total++;
            j=j+1;
        }
        else
        {
            break;
        }
    }
    if (total>=3)
    {
        return total;
    }
    else
    {
        return 0;
    }
}