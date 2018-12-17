#include "ResourceLoadScene.h"
#include "StartScene.h"

Scene * ResourceLoadScene::createScene()
{
	Scene * scene = Scene::create();
	Layer * layer = ResourceLoadScene::create();
	scene->addChild(layer);
	return scene;
}
bool ResourceLoadScene::init()
{
	//��ʼ������Ĺ��캯�����ǵĻ��Ͳ�������Ļ���return false
	if (!Layer::init())
	{
		return false;
	}

	Size size = Director::getInstance()->getWinSize();//��ȡ��Ļ�Ĵ�С
	Sprite * bg = Sprite::create("bg1.png");//����

	//�ñ���ͼƬ����Ļ����
	//auto��id������auto������ָ�룬�����Զ�ʶ��������������
	auto scaleX = size.width/bg->getContentSize().width;
	auto scaleY = size.height/bg->getContentSize().height;
	bg->setScale(scaleX,scaleY);//����
	bg->setPosition(Vec2(size.width/2,size.height/2));//����λ��
	this->addChild(bg);//��Ӹ���ͼ

	Sprite * timerSp = Sprite::create("loading.png");//��������
	ProgressTimer * timer = ProgressTimer::create(timerSp);//������
	timer->setPosition(Vec2(size.width/2,size.height/2));//����λ��
	/*
	setBarChangeRate(Vec2(1,0))��setMidpoint(Vec2(0,1))��ͬ�������ý�������չ������:
	��һ������Ϊ0��ʾˮƽ����û��չ��Ч����Ϊ1��ʾˮƽ������չ��Ч����
	�ڶ�������Ϊ0��ʾ��ֱ����û��չ��Ч����Ϊ1��ʾ��ֱ������չ��Ч����
	(1,0):x�᷽���������չ����(0,1)��������չ������0,0��û��չ��Ч������1,1�������½���������չ����
	*/
	timer->setBarChangeRate(Vec2(1,0));
	timer->setMidpoint(Vec2(0,1));//���û�׼�㣨չ���Ĵ���߿�ʼ��
	timer->setType(ProgressTimer::Type::BAR);//���ý��������ͣ����Σ�
	timer->setPercentage(0);//���ý������ٷֱ� ��ǰ����ʾ��
	this->addChild(timer);

	//1�� �˶���100%
	ProgressTo * progressTo = ProgressTo::create(3,100);
	auto call = CallFunc::create(CC_CALLBACK_0(ResourceLoadScene::startScene,this));
	auto sequene = Sequence::create(progressTo,call,NULL);
	timer->runAction(sequene);

	Label * lable = Label::createWithSystemFont("Loading","",40);
	lable->setPosition(Vec2(size.width/2,size.height/2));
	this->addChild(lable);
	return true;
}
void ResourceLoadScene::startScene()
{
	//����һ������
	Scene * scene = StartScene::createScene();
	//��ҳ����
	TransitionPageTurn * turn = TransitionPageTurn::create(1,scene,false);
	//�滻����
	Director::getInstance()->replaceScene(turn);
}