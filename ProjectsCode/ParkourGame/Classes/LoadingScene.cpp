#include "SimpleAudioEngine.h"
#include "LoadingScene.h"
#include "MainMenu.h"
using namespace cocos2d;
using namespace CocosDenshion;


bool LoadingScene::init()
{
	if (!Scene::init())
		return false;
	Size visibleSize=Director::getInstance()->getVisibleSize();
	Vec2 visibleOrigin=Director::getInstance()->getVisibleOrigin();
	//û����Ӳ㣬ֱ���ڳ���������Ӿ���
	//�����������

	auto splashBkground=Sprite::create("splash.png");
	splashBkground->setPosition(Vec2(visibleOrigin.x+visibleSize.width/2,visibleOrigin.y+visibleSize.height/2));
	this->addChild(splashBkground);

	
	//��ʼ�����ص���Դ��
	totalNum=2;
	loadedNum=0;
	
	//��ʼ��������
	Sprite *progressBkground=Sprite::create("sliderTrack.png"); //��������ͼ
	Size progressBackSize=progressBkground->getContentSize();
	progressBkground->setPosition(Point(visibleOrigin.x+100+progressBackSize.width/2,visibleOrigin.y+60));
	this->addChild(progressBkground);


	loadProgress=ProgressTimer::create(Sprite::create("sliderProgress.png")); //����������
	loadProgress->setBarChangeRate(Vec2(1,0)); //���ú���
	loadProgress->setType(ProgressTimer::Type::BAR); //��״
	loadProgress->setMidpoint(Vec2(0,1)); //���ô����ұ仯 
	Size progressSize=loadProgress->getContentSize();
	loadProgress->setPosition(Point(visibleOrigin.x+100+progressSize.width/2,visibleOrigin.y+60));
	loadProgress->setPercentage(0.0f);
	this->addChild(loadProgress);

	return true;
}

void LoadingScene::onEnter()
{
	//��Ӽ��ػص��������첽Ԥ��������
	Director::getInstance()->getTextureCache()->addImageAsync("boy.png",CC_CALLBACK_1(LoadingScene::loadingCallBack,this));
	Director::getInstance()->getTextureCache()->addImageAsync("girl.png",CC_CALLBACK_1(LoadingScene::loadingCallBack,this));

}

void LoadingScene::loadingCallBack(Texture2D *texture)
{
	loadedNum++;
	//�˴���Ԥ����֡����ָʾ����ʵ������
	switch(loadedNum)
	{
	case 1:
		//Ԥ����֡��������
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("boy.plist",texture);
		loadProgress->setPercentage((float)loadedNum/totalNum*100);
		break;
	case 2:
		//Ԥ����֡��������
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("girl.plist",texture);
		loadProgress->setPercentage((float)loadedNum/totalNum*100);
		break;
	default:
		break;
	}

	if(loadedNum==totalNum)
	{
		//Ԥ����֡����
		auto boyAnimation=Animation::create();
		boyAnimation->setDelayPerUnit(0.1f);
		for(int i=1;i<=12;i++)
		{
			char str[100]={0};
			sprintf(str,"boy%d.png",i);
			boyAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(str));
		}
			
		AnimationCache::getInstance()->addAnimation(boyAnimation,"boyAnimation");

		//Ԥ����֡����
		auto girlAnimation=Animation::create();
		girlAnimation->setDelayPerUnit(0.2f);
		for(int i=1;i<=8;i++)
			girlAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("girl"+std::to_string(i)+".png"));
		AnimationCache::getInstance()->addAnimation(girlAnimation,"girlAnimation");

		////Ԥ�������ֺ���Ч
		SimpleAudioEngine::getInstance()->preloadBackgroundMusic("spring_music.wav");
		SimpleAudioEngine::getInstance()->preloadBackgroundMusic("winter_music.mp3");

		SimpleAudioEngine::getInstance()->preloadEffect("jump.wav");
		SimpleAudioEngine::getInstance()->preloadEffect("point.mp3");
		SimpleAudioEngine::getInstance()->preloadEffect("gameover.wav");
		
		//���������ת����Ϸ����
		auto mainMenu=MainMenu::createScene();
		TransitionScene *transition=TransitionFade::create(1.0f,mainMenu);
		Director::getInstance()->replaceScene(transition);
	}
	
}