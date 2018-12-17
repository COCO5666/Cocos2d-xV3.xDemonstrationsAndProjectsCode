#include "gameScene.h"
//cocosStudio���沼�ֵ�msb��exportJson�ļ�
//#include "editor-support/cocostudio/ActionTimeline/CSLoader.h"
#include "editor-support\cocostudio\ActionTimeline\CSLoader.h"
#include "cocostudio/CocoStudio.h"
using namespace cocostudio;

#include "DataParse.h"

#include "ui/CocosGUI.h"
using namespace ui;

#include "selectLevel.h"

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

#include"WinLayer.h"
#include"LoseLayer.h"
#include "pauseLayer.h"


Scene * gameScene::createScene()
{
	//����һ������ 
	auto scene=Scene::createWithPhysics();
	auto layer=gameScene::create();
	// ����ʹ��auto���Զ�׷�����ͣ�Ҳ����ֱ��ʹ��ע���������ͣ�gameScene *��
	//gameScene *layer=gameScene::create();
	//�õ�һ���������粢�������������������
	layer->setPhysicsWorld(scene->getPhysicsWorld());
	scene->addChild(layer);
	return scene;
}
//������������
 void gameScene::setPhysicsWorld(PhysicsWorld *_world)
{
	PhysicsWorld *world=_world;
	world->setGravity(Vec2(0,-2000));//�������������������������x����y����
	
	//����һ�����壨����Ĵ�С��
	auto bootom=PhysicsBody::createEdgeBox(Size(size.width,30));
	bootom->getShape(0)->setFriction(0.9);//����Ħ����
	bootom->getShape(0)->setRestitution(0.5);//���ûָ���
	bootom->setMass(0);//��������

	//�ݴԾ���,Ҳ�Ǹ���
	Sprite *bootomSp=Sprite::create("caocong.png");
	auto scaleX=size.width/bootomSp->getContentSize().width;
	bootomSp->setScaleX(scaleX);
	this->addChild(bootomSp);
	bootomSp->setPosition(Vec2(size.width/2,15));
	bootomSp->setPhysicsBody(bootom);//����󶨸���
	//������ԣ�������������������ԣ�
	//world->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
}

bool gameScene::init()
{ 
	if(!Layer::init())
	{
		return false;	
	}
	 size=Director::getInstance()->getWinSize();
	int chapter=UserDefault::getInstance()->getIntegerForKey("chapter");
	char gameBg[20];
	sprintf(gameBg,"background%d.png",chapter);
	Sprite *bg=Sprite::create(gameBg);
	auto scaleX=size.width/bg->getContentSize().width;
	auto ScaleY=size.height/bg->getContentSize().height;
	bg->setScale(scaleX,ScaleY);
	bg->setPosition(Vec2(size.width/2,size.height/2));
	this->addChild(bg);
	this->setTouchEnabled(true);
	//this->setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
	auto touchListener=EventListenerTouchOneByOne::create();//�������
	touchListener->onTouchBegan=CC_CALLBACK_2(gameScene::onTouchBegan,this);
	touchListener->onTouchMoved=CC_CALLBACK_2(gameScene::onTouchMoved,this);
	touchListener->onTouchEnded=CC_CALLBACK_2(gameScene::onTouchEnded,this);
	auto dispatcher=Director::getInstance()->getEventDispatcher();//�ַ�����
	dispatcher->addEventListenerWithSceneGraphPriority(touchListener,this);//��ַ�����ע��
	//�����������������������ײ���÷�����
	auto contactListener=EventListenerPhysicsContact::create();
	contactListener->onContactBegin=CC_CALLBACK_1(gameScene::onContactBegin,this);
	dispatcher->addEventListenerWithSceneGraphPriority(contactListener,this);

	//������Ϸ���ֽ��棬��cocosStudio�����Ʒ�ڷţ���Ϸ����Ĳ��ֿ��Ե���Ϊmsb�ļ���Ҳ���Ե���ΪExportJson�ļ���ֻ���ò�ͬ�ķ������ض���
	//����Button��tagֵ
	int levelNum=UserDefault::getInstance()->getIntegerForKey("level");
	char uiLayerName[40];
	sprintf(uiLayerName,"ui/Level_%d_%d.ExportJson",chapter,levelNum);
	log("===%s",uiLayerName);//������
	
	Node *uiLayer;
	//����ѡ�񲿷ֹؿ���msb��������ExportJson�ļ�
	if(chapter==1&& levelNum==1)
	{
		uiLayer=CSLoader::createNode("Layer1_1.csb");
	}
	else
	{
		uiLayer=GUIReader::getInstance()->widgetFromJsonFile(uiLayerName);
		dynamic_cast<Widget *> (uiLayer)->setSwallowTouches(false);
	}
    //  auto uiLayer=GUIReader::getInstance()->widgetFromJsonFile(uiLayerName);	
	////���ɴ�����true���ɣ����������´��ݣ�false�����ɣ��������´���
	//uiLayer->setSwallowTouches(false);
	//uiLayer=GUIReader::getInstance()->widgetFromJsonFile(uiLayerName);
	//dynamic_cast<Widget *> (uiLayer)->setSwallowTouches(false);
	this->addChild(uiLayer);
    
	body_array =__Array::create();//ʢ�ſɵ�������ĸ���
	body_array->retain();//�������飬һ֡���ͷ�
	//��ϵ�����ӷ����Ч��
	house=(Widget *)uiLayer->getChildByName("house");	
	auto light=ParticleGalaxy::create();
	light->setPosition(house->getPosition());
	this->addChild(light);
	
	//�ؿ���Ϣ
	char labelText[20];
	sprintf(labelText,"%d--%d",chapter,levelNum);
	auto label=Label::createWithSystemFont(labelText,"",40);
	label->setColor(Color3B(100,100,100));
	label->setPosition(Vec2(size.width-100,size.height-80));
	this->addChild(label);

	//��ӷ��ذ�ť
	 Button* pause= Button::create("pause.png","pause.png");
	 pause->setPosition(Vec2(50,size.height-50));
	 this->addChild(pause);
	 //ʹ��lambda ���ʽд��ͣ�Ļص�������back->addClickEventListener(CC_CALLBACK_1(gameScene::back,this));
	 pause->addClickEventListener(CC_CALLBACK_1(gameScene::pauseBack,this)); 

	//��json�ļ��������ùض�Ӧ�ĸ�������������������num������num��ùؿ��ĸ���������uiLayer��Ӧ�Ľ����еĸ�������json�ļ��е�num��һ�£���ȣ���
	int num=DataParse::getNum(chapter,levelNum);
	for(int i= 1;i<=num;i++)
	{
		char spriteName[20];
		sprintf(spriteName,"Image_%d",i);
		//�ӳ�����ȡ������
		auto sprite=(Widget *)uiLayer->getChildByName(spriteName);
		//�������岢�Ѿ���������
		this->createPhysicsBody(sprite);
	}
	//��ʼʱ���ǵ�����Ϊ1
	star_Num=0;
	//����װ������ֵ���������
	star_array=__Array::create();
	star_array->retain();
	//ͨ��uiLayerѭ���ӽ����ϻ�ȡ��������item��������װ������star_array��Ϊ�˺���������ţ�����ǵ���ײ���
	for(int i =1;i <=3;i++)
	{
		char starNum[20];
		sprintf(starNum,"star%d",i);
		auto item=uiLayer->getChildByName(starNum);
		star_array->addObject(item);
	}
	//���Ͻǵ���������
	star=Sprite::create("0getstar.png");
	star->setPosition(Vec2(size.width - star->getContentSize().width/2,size.height- star->getContentSize().height/2));
	this->addChild(star);
	this->scheduleUpdate();

	return true;
}

void gameScene::pauseBack(Ref *sender)
{ 
	Director::getInstance()->pause();	 
	Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(this); 	 
	Layer* layer=pauseLayer::create();	 
	layer->setPosition(Vec2(0,0));
	this->addChild(layer,8);
}

 //������������ĸ���
 void  gameScene::createPhysicsBody(Node *sprite)
 {
	 PhysicsBody  *body;
	 Point point1,point2,point3;
	 Point points[3];
	 //���þ����bodyshape
	 switch (sprite->getTag())
	 {
	 case 601://��ţ
		 //����һ��Բ�ζ�̬����
		 snail=sprite;
		 body=PhysicsBody::createCircle(sprite->getContentSize().width/2);
		 body->getShape(0)->setRestitution(1);
		 body->setMass(20);
		 break;
	 case 106://ʯͷ��Բ�ζ�̬����
		 body=PhysicsBody::createCircle(sprite->getContentSize().width/2-5);
		 body->getShape(0)->setRestitution(0.5);
		 break;
	 case 108://Ҭ��,��̬����
		 body=PhysicsBody::createBox(sprite->getContentSize());
		 body->getShape(0)->setRestitution(0.5);
		 body->setMass(100);
		 break;
	 case 107://����Ģ������̬����
		 body= PhysicsBody::createEdgeBox(sprite->getContentSize());
		 body->getShape(0)->setRestitution(2);
		 body->setMass(0);
		 break;
	 case 109://����ש����̬����
		 sprite->setAnchorPoint(Vec2(0,0));
		 point1=Point(-sprite->getContentSize().width/2,-sprite->getContentSize().height/2);
		 point2=Point(-sprite->getContentSize().width/2,sprite->getContentSize().height);
		 point3=Point(sprite->getContentSize().width/2,-sprite->getContentSize().height);
		 points[0]=point1;
		 points[1]=point2;
		 points[2]=point3;
		 body=PhysicsBody::createEdgePolygon(points,3);
		 body->getShape(0)->setRestitution(0.5);
		 body->setMass(0);
		 break;
	 case 401://�̣���̬����
		 body=PhysicsBody::createEdgeBox(sprite->getContentSize());
		 body->getShape(0)->setRestitution(0.5);
	 case 201://�����������
		 body=PhysicsBody::createEdgeBox(sprite->getContentSize());
		 body->getShape(0)->setRestitution(0.5);
		 break;
	 case 301://���������
		 if (Widget *item=dynamic_cast<Widget *>(sprite))
		 {
			 item->setSwallowTouches(false);
		 }
		 //sprite->setSwallowTouches(false);
		 body=PhysicsBody::createEdgeBox(sprite->getContentSize());
		 body->getShape(0)->setRestitution(0.5);
		 body_array->addObject(body);
		 break;
	 default:
		 break;
	 }
	 
	 body->getShape(0)->setFriction(0.2);//����Ħ����
	 //���������巽�ɼ����ײ��������������������
	 body->setCategoryBitmask(1);//�������
	 body->setCollisionBitmask(1);//��������
	 body->setContactTestBitmask(1);//���ô�����

	 //����������
	 sprite->setPhysicsBody(body);
 }

 bool gameScene::onTouchBegan(Touch *touch, Event *unused_event)
 {
	 log("ontouchBegin");
	 return true;//true ���ܴ����������´��ݣ�false���ܴ����ģ���������
 }
 void gameScene::onTouchMoved(Touch *touch, Event *unused_event)
 {
	  log("onTouchMoved");
 }
 bool gameScene::onContactBegin(PhysicsContact &contact)
 {
	 auto nodeA=(Widget *)contact.getShapeA()->getBody()->getNode();
	 auto nodeB=(Widget *)contact.getShapeB()->getBody()->getNode();
	 int Atag=nodeA->getTag();
	 int Btag=nodeB->getTag();
	 //����tagֵ�����ж�
	 if( (Atag==401 && Btag==601) ||(Atag==601 && Btag==401))
	 {
		
		 log("AABBB");
		 this->unscheduleUpdate();//ֹͣ��ʱ��
		 this->setTouchEnabled(false);//ֹͣ��ǰlayer�ĵ���¼�
		 Director::getInstance()->getEventDispatcher()->removeAllEventListeners();//�Ƴ����еļ����¼�
		 auto loseLayer = LoseLayer::create();
		 loseLayer->setPosition(Vec2(0,200));
		 auto moveTo = MoveTo::create(0.7,Vec2(0,0));
		 this->addChild(loseLayer);
		 loseLayer->runAction(moveTo);
	 }
	 return true;
 }

 //�����û��ĵ��������������Ϸ�Ľ�����ʾ���
 void gameScene::update(float f)
 {
	 auto rect=snail->getBoundingBox();
	 //�ж���ţ�������Ƿ���ײ
	 for(int i =0; i< star_array->count();i++)
	 {
		 auto item=(Widget*)star_array->objectAtIndex(i);
		 if(rect.intersectsRect(item->getBoundingBox()))
		 {
			 //������Ч
			 if(!UserDefault::getInstance()->getBoolForKey("Effect"))
			 {
				 SimpleAudioEngine::getInstance()->playEffect("yinxiao.wav",false);				 
			 }
			 item->removeFromParent();
			 star_array->removeObject(item);
			 star_Num=star_Num + 1;
			 char starImage[20];
			 sprintf(starImage,"%dgetstar.png",star_Num);
			 //�ı侫�������
			 star->setTexture(starImage);
		 }
	 }
	 //�ж���ţ�뷿������ײ
	 if(rect.intersectsRect(house->getBoundingBox()))
	 {
		 snail->setPosition(house->getPosition());
		 this->unscheduleUpdate();
		 int chapter=UserDefault::getInstance()->getIntegerForKey("chapter");
		 int levelNum=UserDefault::getInstance()->getIntegerForKey("level");
		 DataParse::setStar(chapter,levelNum,star_Num);
		 this->setTouchEnabled(false);
		 Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
		 WinLayer::setstarNum(star_Num);
		 auto winlayer=WinLayer::create();
		 winlayer->setPosition(Vec2(0,200));
		 auto moveto=MoveTo::create(0.7,Vec2(0,0));
		 this->addChild(winlayer);
		 winlayer->runAction(moveto);		
	 }
	 //�Ƿ���磬����ţ�͸�������û����ײ������Ϸʧ��
	 auto worldRect=Rect(0,0,size.width,size.height);
	 if(!rect.intersectsRect(worldRect))
	 {
		 this->unscheduleUpdate();
		 this->setTouchEnabled(false);
		 Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
		 auto loseLayer=LoseLayer::create();
		 loseLayer->setPosition(Vec2(0,200));
		 auto moveTo=MoveTo::create(0.7,Vec2(0,0));
		 this->addChild(loseLayer);
		 loseLayer->runAction(moveTo);
	 }
 }
 void gameScene::onTouchEnded(Touch *touch, Event *unused_event)
 {
	  log("onTouchEnded");
	  auto point =touch->getLocation();//��õ�ǰ����ĵ������
	  for(int i=0;i<body_array->count();i++)
	  {
		  
		   auto body=(PhysicsBody *)body_array->getObjectAtIndex(i);//��õ���������ĸ���
		  // ͨ����� body->getNode()��ø��������ľ��飬body������һ���ڵ㣬ֻ����ӵ�����ڵ������
		  auto rect=body->getNode()->getBoundingBox();//��ø���ľ���ķ�Χ
		  //�жϵ���ĵ��Ƿ��ڵ���ķ�Χ֮�ڣ��ж��Ƿ��ǵ���������ĸ���
		  if(rect.containsPoint(point) && body->getNode()->getTag()==301)
		  {
			  body->removeFromWorld();//�������������Ƴ�����
			  body->getNode()->removeFromParent();//�Ӹ���ͼ���Ƴ�����
			  body_array->removeObject(body);//���������Ƴ�����
		  }

	  }
 }
