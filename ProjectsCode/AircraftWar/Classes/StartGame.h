//
//  StartGame.h
//  a4
//
//  Created by student on 15-7-10.
//
//

#ifndef __a4__StartGame__
#define __a4__StartGame__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;

class StartGame:public Layer
{
public:
    static Scene *createScene();
    virtual bool init();
    CREATE_FUNC(StartGame);
    void startGame(Ref *sender);
};
#endif /* defined(__a4__StartGame__) */
