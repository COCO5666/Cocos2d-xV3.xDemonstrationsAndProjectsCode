//
//  GameOver.h
//  a4
//
//  Created by student on 15-7-13.
//
//

#ifndef __a4__GameOver__
#define __a4__GameOver__

#include <iostream>
#include <cocos2d.h>
USING_NS_CC;

class GameOver:public Layer
{
public:
    static Scene *createScene();
    virtual bool init();
    CREATE_FUNC(GameOver);
public:
    void mene_play();
};
#endif /* defined(__a4__GameOver__) */
