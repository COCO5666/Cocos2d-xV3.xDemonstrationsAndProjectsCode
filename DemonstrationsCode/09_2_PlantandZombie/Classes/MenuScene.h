//
//  MenuScene.h
//  twenty
//
//  Created by student on 15-6-13.
//
//

#ifndef __twenty__MenuScene__
#define __twenty__MenuScene__
#include <iostream>
#include "cocos2d.h"
USING_NS_CC;
class MenuScene:public Layer
{
public:
    static Scene *createScene();
    CREATE_FUNC(MenuScene);
    virtual bool init();
};
#endif /* defined(__twenty__MenuScene__) */

