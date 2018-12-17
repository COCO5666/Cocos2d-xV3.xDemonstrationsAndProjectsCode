#include "selectLevel.h"
#include "selectChapter.h"

#include "DataParse.h"
#include "gameScene.h"

Scene *  selectLevel::createScene()
{
	Scene * scene =Scene::create();
	Layer *layer=selectLevel::create();
	scene->addChild(layer);
	return scene;
}
bool selectLevel::init()
{
	if(!Layer::init())
	{
		return false;
	}
   	size=Director::getInstance()->getWinSize();
	//
	Sprite *bg=Sprite::create("bg2.png");
	//auto scalex=size.width/bg->getContentSize().width/2;
	//auto scaley=size.width/bg->getContentSize().height/2;
	//bg->setScale(scalex,scaley);
	bg->setPosition(Vec2(size.width/2,size.height/2));
	this->addChild(bg);
	wo1=Sprite::create("wowo1.png");
	wo1->setPosition(100,size.height-100);
	this->addChild(wo1);
	JumpTo *jumptoRight=JumpTo::create(5,Vec2(size.height-100,size.height-100),20,10);
	JumpTo *jumptoLeft=JumpTo::create(5,Vec2(100,size.height-100),20,10);
	auto  backCall=CallFunc::create(this,callfunc_selector(selectLevel::flip));
	Sequence *seq=Sequence::create(jumptoRight,backCall,jumptoLeft,backCall,NULL);
	wo1->runAction(seq);
	Button * backButton=Button::create("backarrow.png","backarrow.png");
	backButton->setPosition(Vec2(50,size.height-50));
	backButton->addClickEventListener(CC_CALLBACK_0(selectLevel::back,this));
	this->addChild(backButton);
	
	//��ScrollView��ʵ�ֻ���ѡȡ�ؿ���Ч��
	scrollView=ScrollView::create();
	Size size2(size.width,size.height/4*3);
	scrollView->setContentSize(size2);
	//�������ݴ�СΪ2��
	scrollView->setInnerContainerSize(Size(size.width*2,size.height/4*3));
	scrollView->setPosition(Vec2(0,0));
	scrollView->setAnchorPoint(Vec2(0,0));
	scrollView->setDirection(ScrollView::Direction::HORIZONTAL);
	this->addChild(scrollView);
	//��scrollview�����С���ӣ���
	createLevelItem();
	return true;
}
void selectLevel::createLevelItem()
{
	//���button��tagֵ
	int chapter=UserDefault::getInstance()->getIntegerForKey("chapter");
	//������chapter��ͨ��DataParse::getChapter(chapter)��ȡ���е�star��lock��ֵ������ŵ��ֵ��У�����һ���ֵ�
	__Dictionary * chapterData=DataParse::getChapter(chapter); 
   //���ݹؿ���ƴ�ӳ������ͷ�����ͼƬ������
	char levelLock[20];
	sprintf(levelLock,"house_lock%d.png",chapter);
	char levelUnlock[20];
	sprintf(levelUnlock,"house%d.png",chapter);
	
	//��������״ֵ̬��ѭ�����6���ؿ���Ӧ�ķ��ӣ�������starNum��Ӧ��ֵ���ڷ��ӵ�λ����ʾ���ǵ�ͼƬ0getstar.png
	for (int i = 1; i <=6; i++)
	{
		Button *levelBg;//����
		char lockKey[20];
		sprintf(lockKey,"level_%d_lock",i);
		Integer *lock=(Integer* )chapterData->objectForKey(lockKey);
		int lockValue=lock->getValue();//����״̬
		switch (lockValue)
		{
		case 0://������ͼƬ
			levelBg=Button::create(levelUnlock,levelUnlock);
			levelBg->addClickEventListener(CC_CALLBACK_1(selectLevel::goto_level,this));
			break;
		case 1:
			levelBg=Button::create(levelLock,levelLock);
		default:
			break;
		}
		levelBg->setAnchorPoint(Vec2(0,0));
		//���ӵļ��
		float f=(size.width*2-levelBg->getContentSize().width)/5;
		levelBg->setPosition(Vec2((i-1)*f,0));
		levelBg->setTag(i);
		auto starImage=Sprite::create();
		starImage->setPosition(levelBg->getContentSize().width/2,50);
		char starKey[20];
		sprintf(starKey,"level_%d_star",i);
		Integer * star=(Integer *)chapterData->objectForKey(starKey);
		int starValue=star->getValue();
		switch (starValue)
		{
		case 0:
			starImage->setTexture("0getstar.png");
			break;
		case 1:
			starImage->setTexture("1getstar.png");
			break;
		case 2:
			starImage->setTexture("2getstar.png");
			break;
		case 3:
			starImage->setTexture("3getstar.png");
			break;
		default:
			break;
		}
		levelBg->addChild(starImage);
		scrollView->addChild(levelBg);
	}

}
 void selectLevel::goto_level(Ref *sender)
{
	Button *button=(Button *)sender;
	int levelNum=button->getTag();
	UserDefault::getInstance()->setIntegerForKey("level",levelNum);
	//����	levelNum��ֵѡ��ùؿ���Ӧ����Ϸ��������Ч��ͼ
	Scene *scene=gameScene::createScene();
	Director::getInstance()->replaceScene(scene);

}
void  selectLevel::flip()
{
	if(wo1->isFlipX())
	{
		//�ָ�ԭ����״̬
		wo1->setFlipX(false);
		//wo1->setFlipX(-1);
	}
	else
	{
		//��ת
		wo1->setFlipX(true);
	}
}
void selectLevel::back( )
{
	Scene *scene=SelectChapter::createScene();
	Director::getInstance()->replaceScene(scene);
}