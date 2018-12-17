#include "WinLayer.h"
#include "ui/CocosGUI.h"
using namespace ui;

#include "gameScene.h"
#include "SelectChapter.h"
#include "DataParse.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

int WinLayer::win_star = 0;//��ʼ��
bool WinLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	size = Director::getInstance()->getWinSize();
	this->initWithColor(Color4B(100,100,100,100));

	this->setTouchEnabled(true);//���ÿɴ���
	this->setContentSize(Size(size.width,size.height));

	Sprite* winSp = Sprite::create("succeed.png");
	winSp->setPosition(Vec2(size.width/2,size.height/2));
	this->addChild(winSp);

	if (!UserDefault::getInstance()->getBoolForKey("onEffect"))
	{
		SimpleAudioEngine::getInstance()->playEffect("win.wav",false);
	}

	//�Զ�������Ч��
	auto quad = ParticleSystemQuad::create("xingxing.plist");
	quad->setPosition(Vec2(size.width/2,size.height/2+50));
	quad->setDuration(2);//���Ŵ���
	this->addChild(quad);

	int levelNum = UserDefault::getInstance()->getIntegerForKey("level");
	if(levelNum == 6 && win_star == 3)
	{
		Label* label = Label::createWithSystemFont("You have Win, Play next chapter","",30);
		label->setColor(Color3B(100,100,100));
		label->setPosition(Vec2(size.width/2,size.height/2+100));
		this->addChild(label);
	}

	//�ڳɹ�����������������
	for (int i = 1;i <= win_star;i++)
	{
		Sprite* starSp = Sprite::create("star2.png");
		starSp->setScale(.5);
		starSp->setPosition(Vec2(size.width/2-100+50*i,size.height/2+200));
		this->addChild(starSp);
	}

	Node* node = Node::create();
	node->setPosition(Vec2(size.width/2,size.height/2-50));
	this->addChild(node);

	Button* again = Button::create("again.png","again.png");
	again->setPosition(Vec2(-100,0));
	again->setTag(1);
	again->addClickEventListener(CC_CALLBACK_1(WinLayer::clickButton,this));
	node->addChild(again);

	Button* next = Button::create("next.png","next.png");
	next->setPosition(Vec2(0,0));
	next->setTag(2);
	next->addClickEventListener(CC_CALLBACK_1(WinLayer::clickButton,this));
	node->addChild(next);

	Button* menu = Button::create("menu.png","menu.png");
	menu->setPosition(Vec2(-100,0));
	menu->setTag(3);
	menu->addClickEventListener(CC_CALLBACK_1(WinLayer::clickButton,this));
	node->addChild(menu);

	if (levelNum == 6)
	{
		next->removeFromParent();
	}

	return true;
}

void WinLayer::clickButton(Ref* sender)
{
	Button* button = (Button*)sender;
	Scene* scene;
	//��UserDefault.xml�л�ȡ��ǰ��Ϸ���½����͹ؿ���
	int chapternum = UserDefault::getInstance()->getIntegerForKey("chapter");
	int levelNum = UserDefault::getInstance()->getIntegerForKey("level");
	//���ݵ�ǰ��Ϸ���½����͹ؿ�������json�ļ��л�ȡ��Ӧ��������������starNum
	int starNum = DataParse::getStar(chapternum,levelNum);
	switch (button->getTag())
	{
	case 1://���again��ť��������
		scene = gameScene::createScene();
		Director::getInstance()->replaceScene(scene);
		break;

	case 2://���next��ť
		if (starNum ==3 && levelNum <6)//�Ե������ǣ���ţ�������Ƕ���ײ��,˫�Ⱥ������ж��Ƿ����3�����ؿ���С��6���������µ���һ��
		{
			//�ѹؿ�����1���ٴ���UserDefault.xml��
			UserDefault::getInstance()->setIntegerForKey("level",levelNum + 1);
			/*gameScene���ڳ�ʼ������ʱ��ͨ��ִ�����int levelNum=UserDefault::getInstance()->getIntegerForKey("level");
			����һ�������뵽UserDefault.xml�еļ�1֮��Ĺؿ���ȡ��������levelNum��Ȼ�����levelNumѡ����Ӧ�Ĺؿ����档
			*/
			scene = gameScene::createScene();
			Director::getInstance()->replaceScene(scene);
		}		
		else if(starNum < 3 && levelNum < 6)//�Ե�������С��3����ţ��ײ��������С��3�����ҹؿ���С��6������ʾ��Can't go to next level!��,���ܽ�����µ���һ��
		//else
		{
			Label* lable = Label::createWithSystemFont("Can't go to next level!","",30);
			lable->setColor(Color3B(100,100,100));
			lable->setPosition(Vec2(size.width/2,size.height/2+100));
			this->addChild(lable);
		}
		break;

	case 3://���ѡ��˵���ť������ѡ����
		scene = SelectChapter::createScene();
		Director::getInstance()->replaceScene(scene);
		break;

	default:
		break;
	}
}

void WinLayer::setstarNum(int starNum)
{
	win_star = starNum;
}