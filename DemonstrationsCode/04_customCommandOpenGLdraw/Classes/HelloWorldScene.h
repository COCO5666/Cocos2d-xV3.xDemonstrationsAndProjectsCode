#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;
class HelloWorld : public cocos2d::Layer
{
public:
     static cocos2d::Scene* createScene();
    virtual bool init();    
	CREATE_FUNC(HelloWorld);   
    CustomCommand command;
    void ondraw();
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags);

};

#endif // __HELLOWORLD_SCENE_H__
