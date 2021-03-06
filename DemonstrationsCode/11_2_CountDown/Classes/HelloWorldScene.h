#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;
class HelloWorld : public Layer
{
public:
    static Scene* createScene();
    virtual bool init();
    void stop();
    void myUpdate(float f);
    CREATE_FUNC(HelloWorld);
private:
    Label *countTimeLabel;//声明变量用来接收计时时间
    int time;//设置倒计时的限制时间
    __String  *str;
};

#endif // __HELLOWORLD_SCENE_H__
