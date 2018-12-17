#include "pauseLayer.h"
#include "ui\CocosGUI.h"
using namespace ui;
#include "gameScene.h"
#include "SelectChapter.h"
pauseLayer::pauseLayer(void)
{
}
pauseLayer::~pauseLayer(void)
{
}
bool pauseLayer::init()
{
	if(!Layer::init())
  {
	  return false; //�������Ϊfalse���������Ϊtrue���������pauseLayer�����������󣬿��԰�����Ϊtrue���÷��������ĵط���Ϊfalse���鿴����
  }
	Size  size=Director::getInstance()->getWinSize();
	this->initWithColor(Color4B(180,180,180,70));
	this->setTouchEnabled(true);
	this->setContentSize(Size(size.width,size.height));
	Sprite *bg=Sprite::create("green.jpg");
	bg->setAnchorPoint(Vec2(0,0));
	bg->setPosition(Vec2(size.width- bg->getContentSize().width,size.height-bg->getContentSize().height));
	this->addChild(bg);
	Node *node=Node::create();
	node->setPosition(bg->getContentSize().width/2,bg->getContentSize().height/2);
	//�мɣ����ܰ�һ���ڵ���ӵ�����ڵ��ϣ������ӵ������������ѭ�������治�仯
	bg->addChild(node);

	Button *again=Button::create("again.png","again.png");
	again->setPosition(Vec2(0,100));//�Ѹð�ť�����ڽڵ��λ������ƫ��100��λ���ϣ�������������setpositon���������е�ֵΪ�븸�ڵ�����ƫ�����������õ��ǽڵ�����ϵ
	again->setTag(1);
	again->addClickEventListener(CC_CALLBACK_1(pauseLayer::clickButton,this));
	node->addChild(again);

	Button *continue_Button=Button::create("continue.png","continue.png");
	continue_Button->setPosition(Vec2(0,0));//��ʾ�ð�ť�븸�ڵ�node�����λ��ƫ����Ϊ0�����Ѹð�ť�����ڽڵ��λ����
	continue_Button->setTag(2);
	continue_Button->addClickEventListener(CC_CALLBACK_1(pauseLayer::clickButton,this));
	node->addChild(continue_Button);

	Button *menu_Button=Button::create("menu.png","menu.png");
	menu_Button->setPosition(Vec2(0,-100));//�Ѹð�ť�����ڽڵ��λ������ƫ��100��λ����
	menu_Button->setTag(3);
	menu_Button->addClickEventListener(CC_CALLBACK_1(pauseLayer::clickButton,this));
	node->addChild(menu_Button);
  return true;
}
	
void pauseLayer::clickButton(Ref *sender)
{
	Button *button=(Button*)sender;
	Scene *scene=Scene::create();
	int chapter=UserDefault::getInstance()->getIntegerForKey("chapter");
	int level=UserDefault::getInstance()->getIntegerForKey("level");
	switch (button->getTag())
	{
	case 1:
		Director::getInstance()->resume();//�ָ���ͣ��������Ϸ��
		scene=gameScene::createScene();
		Director::getInstance()->replaceScene(scene);
		break;
	case 2:
		Director::getInstance()->resume();
		Director::getInstance()->getEventDispatcher()->resumeEventListenersForTarget(this->getParent());
		this->removeFromParent();
		break;
	case 3:
		Director::getInstance()->resume();
		scene=SelectChapter::createScene();
		Director::getInstance()->replaceScene(scene);
		break;
	default:
		break;
	}
}