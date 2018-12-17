#include "Mainscene.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
#include "GameScene.h"

Scene*Mainscence::creatScence()
{
	Scene*scene=Scene::create();
	Mainscence*Layer=Mainscence::create();
	scene->addChild(Layer);
	return scene;
}


bool Mainscence::init()
{
	if(!Layer::init())
	{
	return false;
	}
	Size winSize=Director::getInstance()->getWinSize();
	Sprite*bgsprite=Sprite::create("bg3.png");
	bgsprite->setScale(1.1f);
	bgsprite->setPosition(Vec2(winSize.width/2,winSize.height/2));
	this->addChild(bgsprite);
	auto quad = ParticleSystemQuad::create("liuxing.plist");
    quad->setPosition(100,winSize.height);
      auto quad1 = ParticleSystemQuad::create("liuxing.plist");
	      quad1->setPosition(350,winSize.height);
		auto quad2 = ParticleSystemQuad::create("liuxing.plist");
	            quad2->setPosition(600,winSize.height);
	            //quad->setDuration(2);//���Ŵ���
	            this->addChild(quad);
				  this->addChild(quad1);
				  this->addChild(quad2);

	
	MenuItemImage*helpItem=MenuItemImage::create("help.png", "help.png");//��Ϸ����
	helpItem->setScale(0.85f);
	helpItem->setPosition(Vec2(winSize.width/2-200,winSize.height/2));
	MenuItemImage*startItem=MenuItemImage::create("start.png", "start.png");//��ʼ��Ϸ
	startItem->setScale(1.2f);
	startItem->setPosition(Vec2(winSize.width/2,winSize.height/2));
	MenuItemImage*endItem=MenuItemImage::create("end.png", "end.png");//�˳���Ϸ
		endItem->setPosition(Vec2(winSize.width/2+200,winSize.height/2));
	startItem->setCallback(CC_CALLBACK_0(Mainscence::gameStart,this));
	helpItem->setCallback(CC_CALLBACK_0(Mainscence::helpgame,this));
	endItem->setCallback(CC_CALLBACK_0(Mainscence::end,this));

		cocos2d::RotateBy* rotateBy = cocos2d::RotateBy::create(1, 360);//1��ת360��
		

	
		Menu*gameMenu=Menu::create(startItem,helpItem,endItem,NULL);
		gameMenu->setPosition(Vec2(winSize.width/2-500,winSize.height/2-300));
		gameMenu->runAction(rotateBy);
		this->addChild(gameMenu);
		SimpleAudioEngine::getInstance()->playBackgroundMusic("backmusic.wav");
        return true;
}

void Mainscence::helpgame()
{
	Layer* layer = Layer::create();
	layer->setName("help");
	this->addChild(layer);

	Size winSize = Director::getInstance()->getWinSize();
	Sprite* sprite2 =Sprite::create("helpmianban.png");



	sprite2->setPosition(Vec2(winSize.width/2,winSize.height/2));
	sprite2->setTag(50);
    sprite2->setScale(1.5f);
	layer->addChild(sprite2,2);
	MenuItemImage* Finish = MenuItemImage::create("finish1.png","finish.png");
	Finish->setCallback(CC_CALLBACK_0(Mainscence::finish,this));
	Menu* finishMenu = Menu::create(Finish, NULL);
	//  finishMenu->setScale(0.5f);
	finishMenu->setPosition(Vec2(480, 100));

	layer->addChild(finishMenu);
}
void Mainscence::finish()
{
	
	auto layer2 = this->getChildByName("help");
	layer2->removeFromParent();
}
void Mainscence::end()
{
	exit(0);
}
void Mainscence::gameStart()
{
	 SpriteFrameCache::getInstance()->addSpriteFramesWithFile(RESOURCESPLIST);

	 Animation* xin = getAnimationByName("xin",0.5f, 9);
	 Animation* luo = getAnimationByName("xinluo",0.2f, 10);
	 Animation* childfei = getAnimationByName("fei",0.2f, 10);
	 AnimationCache::getInstance()->addAnimation(xin, "xin");
	 AnimationCache::getInstance()->addAnimation(luo, "xinluo");
	 AnimationCache::getInstance()->addAnimation(childfei, "fei");
	 Director::getInstance()->replaceScene(GameScene::createScene());
}
Animation * Mainscence::getAnimationByName(std::string animName,float delay,int animNum){

	Animation* animation = Animation::create();
	// ѭ���Ӿ���֡�����л�ȡ��ͼƬ�������Ӧ�ľ���֡��ɶ���
	for(unsigned int i = 1;i<=animNum;i++){
		// ��ȡ����ͼƬ���ƣ�����plane0.png
		std::string frameName = animName;
		frameName.append(StringUtils::format("%d",i)).append(".png");
		// ������ͼƬ���Ϊ����֡��������֡��
		animation->addSpriteFrameWithFile(frameName.c_str());
	}
	// ���ö������ŵ�����
	animation->setDelayPerUnit(delay);
	// �þ�������ڶ���ִ�����ָ������״̬
	animation->setRestoreOriginalFrame(true);

	return animation;
}











