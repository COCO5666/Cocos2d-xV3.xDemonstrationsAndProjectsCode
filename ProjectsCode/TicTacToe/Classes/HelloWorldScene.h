#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Card.h"

class HelloWorld : public cocos2d::Layer
{
public:
    
    static cocos2d::Scene* createScene();

    virtual bool init();  
   
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    CREATE_FUNC(HelloWorld);

	//��ӿ�Ƭ
	void addCard();

	//�ж���Ϸ�Ƿ����
	void isGameOver(); 

	//���¿�ʼ��Ϸ
	void reStart();

private:
	Size visibleSize;
	Point origin;

	 //��¼����Ĵ����������ε�Ϊͼ��1��ż���ε�Ϊͼ��2
	int count;

	//��Ƭ��ά���飬�������
	Card *cardArr[3][3];

	//���ڳ�ʼ��ͼ�����
	int initPatternNum;
	
    Vector<Card*> *c;  
};

#endif // __HELLOWORLD_SCENE_H__