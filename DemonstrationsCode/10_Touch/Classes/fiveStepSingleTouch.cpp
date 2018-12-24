#include "fiveStepSingleTouch.h"


fiveStepSingleTouch::fiveStepSingleTouch(void)
{
}
fiveStepSingleTouch::~fiveStepSingleTouch(void)
{
}

Scene* fiveStepSingleTouch::createScene()
{
	auto scene = Scene::create();
	auto layer = fiveStepSingleTouch::create();
	scene->addChild(layer);
	return scene;
}

bool fiveStepSingleTouch::init()
{
	if (!Layer::init())
	{
		return false;
	}

	return true;
}
void fiveStepSingleTouch::onEnter()
{
	Layer::onEnter();//���������̨ʱ����onEnter������
		//���ò�layer��λ�ô����¼�����ʱ�����ᵼ�´�����ƫ�ƣ������¼�����ӵľ���Ҳ������ƫ��
	this->setPosition(100, 100);
	log("onEnter is executed!");
	auto sp = Sprite::create("bg.jpg");
	sp->setPosition(240, 160);
	this->addChild(sp);
	// �ٻ�ȡ�����¼��ַ������¼��������ģ�
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	//�� �������㴥�������ߣ�������һ�����㴥���¼������������������¼��߼�
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);//���ɴ�����������layer�����յ������¼���������Ľ����ɵ�����ģ�ʹ����Ĳ�������������¼���
	//�۰���Ӧ�¼������������ô����ĺ����ص�
	touchListener->onTouchBegan = CC_CALLBACK_2(fiveStepSingleTouch::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(fiveStepSingleTouch::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(fiveStepSingleTouch::onTouchEnded, this);
	touchListener->onTouchCancelled = CC_CALLBACK_2(fiveStepSingleTouch::onTouchCancelled, this);
	//�ܽ���������ӵ��¼��ַ���dispatcher��
	dispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}
void fiveStepSingleTouch::onExit()
{
	Layer::onExit();//�����˳���̨ʱ����onExit����
	log("onExit is executed! ");
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	dispatcher->removeEventListenersForTarget(this);
}
//�ݱ�д�ص���Ӧ������
bool fiveStepSingleTouch::onTouchBegan(Touch *touch, Event *unused_event)
{
	log("begin");
	return true; //��ʾ������δ����¼�
   // return false;//����Ϊfalse����ʾ��������δ����¼������޷����´��ݣ�û����ʾ������
}
void fiveStepSingleTouch::onTouchMoved(Touch *touch, Event *unused_event)
{
	//log("move");�������ĺ����Ǵ�����Ļ�ͻ���Ӿ��飬
	Vec2 position = touch->getLocation();//�õ���ǰ�Ĵ������OpenGL����
	//touch->getPreviousLocation()//�õ�ǰһ�������������
	position = this->convertToNodeSpace(position);
	//Ϊ this->setPosition(100,100); ��ת�������������¼�����Ӿ���ʱ�Ͳ���ƫ�ƣ������ʲô�ط����ڸõط���ͼ
	auto sprite = Sprite::create("bird.png");
	sprite->setScale(0.5);
	sprite->setPosition(position);
	this->addChild(sprite);
}

void fiveStepSingleTouch::onTouchEnded(Touch *touch, Event *unused_event)
{
	log("end");
}
void fiveStepSingleTouch::onTouchCancelled(Touch *touch, Event *unused_event)
{
	log("cancel");
}