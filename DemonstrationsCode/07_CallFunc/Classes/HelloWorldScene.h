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
	void startAction(Ref *render);
    void  callback(Ref *render);

	CustomCommand command;
	void onDraw( );
    void  draw(Renderer *renderer, const Mat4 &transform, uint32_t flags);

private:
    Sprite *mSprite, *fmSprite;
};

#endif // __HELLOWORLD_SCENE_H__
