//
//  PopScene.h
//  twenty
//
//  Created by student on 15-6-14.
//
//

#ifndef __twenty__PopScene__
#define __twenty__PopScene__

#include <iostream>
#include <cocos2d.h>
USING_NS_CC;
class PopScene:public Layer
{
public:
    static  Scene *createScene();
    virtual bool init();
    CREATE_FUNC(PopScene);
    void enterWelcomeScene();
   // void updateWelcomeScene(Ref *sender);
    void updateWelcomeScene(float f);
};
#endif /* defined(__twenty__PopScene__) */
