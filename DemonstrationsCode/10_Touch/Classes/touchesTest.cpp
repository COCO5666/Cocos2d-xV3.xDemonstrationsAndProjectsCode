#include "touchesTest.h"


touchesTest::touchesTest(void)
{
}
touchesTest::~touchesTest(void)
{
}

Scene * touchesTest::createScene()
{
	auto scene = Scene::create();
	auto layer = Layer::create();
	scene->addChild(layer);
	return scene;
}
bool touchesTest::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto sp = Sprite::create("bg.jpg");
	sp->setPosition(240, 160);
	this->addChild(sp);
	// 1:��ȡ�����¼��ַ������¼��������ģ�
	auto dispatcher = Director::getInstance()->getEventDispatcher();

	//2:������㴥��������,��alter�����������Ϳ���ģ�����ϳ���������
	auto  touchesListener = EventListenerTouchAllAtOnce::create();
	/*���ɴ�����������layer�����յ������¼���������Ľ����ɵ�����ģ�
	ʹ����Ĳ�������������¼�����㴥��������*/
	// touchListener->setSwallowTouches(true);
	//3:���ô�����ʼʱ�ĺ����ص�
	touchesListener->onTouchesBegan = CC_CALLBACK_2(touchesTest::onTouchesBegan, this);
	touchesListener->onTouchesMoved = CC_CALLBACK_2(touchesTest::onTouchesMoved, this);
	touchesListener->onTouchesEnded = CC_CALLBACK_2(touchesTest::onTouchesEnded, this);
	touchesListener->onTouchesCancelled = CC_CALLBACK_2(touchesTest::onTouchesCancelled, this);
	//4������¼������ߵ��¼��ַ�����
	dispatcher->addEventListenerWithSceneGraphPriority(touchesListener, this);

	true;
}
void touchesTest::onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event)
{
	/*1:��������iterator����һ�ֶ������ܹ�����������׼ģ��������еĲ��ֻ�ȫ��Ԫ�أ�
	 ÿ��������������������е�ȷ���ĵ�ַ���������޸��˳���ָ��Ľӿڣ�
	 ��ν��������һ�ָ����ϵĳ�����Щ��Ϊ����������Ķ��������Խ�����������
	 Ȼ���������кܶ಻ͬ�������������԰ѳ���������ͨ���㷨�л���ͳһ������
	 �������ṩ��һ�������еĶ���ķ��ʷ��������Ҷ����������ж���ķ�Χ��
	 ����������ͬһ��ָ�롣��ʵ�ϣ�C++��ָ��Ҳ��һ�ֵ�������
	 ���ǣ���������������ָ�룬����㲻����Ϊ����һ�����е�ֵַ��
	 2:begin��end����
	 ÿ��������������һ������Ϊbegin��end�ĺ��������ڷ��ص�������
	 �����������Ԫ�صĻ�����begin���ص�Ԫ��ָ���һ��Ԫ�ء�
	 vector<int>::iterator iter=v.begin();��v��Ϊ�գ�iterָ��v[0]��
	 ��end���صĵ�����ָ�����һ��Ԫ�ص���һ����������.
	 ��vΪ�գ�begin��end���ص���ͬ��*iter=0;iter++������������ǰ�ƶ�һ��λ��,
	 ����v[0]��ֵΪ0,��end���صĲ�������н������
	 ==��!=���������Ƚ�������������������������ָ��ͬһ��Ԫ�أ���������ȣ�������ȡ�
*/
//�м�����ָ������Ļ��������Ļ�ϴ�����λ�û��Ƽ���bird���顣
	log("%d", (int)touches.size());
	auto itor = touches.begin();//C++�����£�ģ���ĵ�����
	for (; itor != touches.end(); itor++)
	{
		auto touch = (Touch*)(*itor);
		Vec2 pos = touch->getLocation();
		log("(%f,%f)", pos.x, pos.y);
		auto birdSprite = Sprite::create("bird.png");
		birdSprite->setPosition(pos);
		this->addChild(birdSprite);
	}
}
void touchesTest::onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event)
{
	log("onTouchesMoved");
}
void touchesTest::onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event)
{
	log("onTouchesEnded");
}
void touchesTest::onTouchesCancelled(const std::vector<Touch*>&touches, Event *unused_event)
{
	log("onTouchesCancelled");
}