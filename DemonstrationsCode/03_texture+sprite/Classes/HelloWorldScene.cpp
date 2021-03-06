#include "HelloWorldScene.h"
#include <cocos2d.h>
USING_NS_CC;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}

bool HelloWorld::init()
{
       if ( !Layer::init() )
    {
        return false;
    }
#pragma mark  创建精灵的方式
#pragma mark 1.直接使用图片文件名创建
    //从磁盘读取文件到内存中，已经被封装成texture贴图的模式，同样也会生成缓存，从中取图
    auto mSprite=Sprite::create("bird.png");
    mSprite->setPosition(40, 160);
    addChild(mSprite,1);
    auto backgroundSp=Sprite::create("background4.jpg");
    backgroundSp->setPosition(240,160);
    addChild(backgroundSp,0);
    
#pragma mark 2.使用贴图缓存TexureCache 和Textture2D创建精灵
    auto cache=Director::getInstance()->getTextureCache();
    //如果缓存中没有该图片则将图片加到缓存，如果缓存中已经存在这张图，则直接从缓存中取出图片并返回
    Texture2D *texture=cache->addImage("bird.png");
    auto mSprite2=Sprite::createWithTexture(texture);
    mSprite2->setPosition(140,160);
    this->addChild(mSprite2);

#pragma mark 3.先将大图加到贴图缓存中,再指定纹理和裁剪的矩形区域来创建精灵
    Texture2D *texture2=cache->addImage("blocks.png");
    auto mSprite3=Sprite::createWithTexture(texture2, Rect(32, 0, 32, 32));
    mSprite3->setPosition(240, 160);
    this->addChild(mSprite3);
#pragma mark 4.
	/*借用精灵帧缓存SpriteFrameCache和其中添加的存储纹理图集的plist文件及对应的png，
	使用精灵帧名创建一个精灵对象。*/
    auto frameCache=SpriteFrameCache::getInstance();
    frameCache->addSpriteFramesWithFile("Zombie_default.plist", "Zombie_default.png");//这里的png也可以省略
    auto sprite4=Sprite::createWithSpriteFrameName("Zombie1.png");
    sprite4->setPosition(360,240);
    addChild(sprite4);
    
#pragma mark 5.精灵帧动画(综合mark4和mark5):
	/*
	1.创建精灵帧缓存SpriteFrameCache，并在其中添加存储纹理图集的plist文件及对应的png，
	  使用精灵帧名创建出一个精灵；即上面mark4中的步骤。
	2.接着使用纹理图集plist文件创建字典对象，然后从字典取出“frames”键值对应的字典对象；
	3.把plist文件中键值frame每一帧的帧名，循环压入容器Vector，
	 其循环变量由字典对象调用allKeys()方法，再让执行的结果继续调用count()获得，
	 即数出字典中所有小图片的帧数。
	4.把容器中取出所有的精灵帧创建成动作animation；
	5.让步骤1中创建的精灵执行动画和动作。
*/
    auto dic=__Dictionary::createWithContentsOfFile("Zombie_default.plist");
    auto frameDic=(__Dictionary *)dic->objectForKey("frames");
    int num =frameDic->allKeys()->count();
    Vector<SpriteFrame *> vector(4);//还能自动扩容
	for (int i=1; i<num+1; i++)
    {
        char fName[20];
        sprintf(fName, "Zombie%d.png",i);
        auto frame =frameCache->getSpriteFrameByName(fName);
        vector.pushBack(frame);
    }
    auto animation=Animation::createWithSpriteFrames(vector);
    animation->setDelayPerUnit(0.1);
    auto animate=Animate::create(animation);
    auto forever=RepeatForever::create(animate);
    auto moveTo =MoveTo::create(10, Vec2(100,240));
    sprite4->runAction(moveTo);
	sprite4->runAction(forever);
    return true;

}

