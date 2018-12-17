#pragma once
#include "cocos2d.h"
USING_NS_CC;
#include "ui/CocosGUI.h"
using namespace ui;
class gameScene :public Layer
{

public:
	static Scene * createScene();
	virtual bool init();
	CREATE_FUNC(gameScene);
    virtual bool onTouchBegan(Touch *touch, Event *unused_event); 
    virtual void onTouchMoved(Touch *touch, Event *unused_event); 
    virtual void onTouchEnded(Touch *touch, Event *unused_event); 
	//������������
	void setPhysicsWorld(PhysicsWorld *_world);
	void createPhysicsBody(Node *sprite);
	bool onContactBegin(PhysicsContact &contact);
	void update(float f);//��ʱ�������һ��float���͵Ĳ���
	void pauseBack(Ref * sender);//���巽��ʱ��ע�ⲻҪ�������װ�õķ�������������Ͳ���ֱ�Ӷ���Ϊpause��������Ϊ�����Ѿ���װ�����������
private:
	Size size;
	__Array *body_array;
	Node *snail;
	__Array *star_array;
	int star_Num;
	Sprite *star;
	Widget *house;
};

