#pragma once
#include "cocos2d.h"
USING_NS_CC;
class spriteTouch :	public Sprite
{
public:
	spriteTouch(void);
	~spriteTouch(void);
private:
    // �¼�������
    EventListener* _listener;
    // ���ȼ�
    int _fixedPriority;
    // ���ڱ��澫���ͼƬ���ƣ����ڹ۲���
    const char* _name;
    
public:
    // ���������ȼ������Ƶĺ���
    void setPriority(int fixedPriority,const char* name);
	 void onEnter() override;
	 void onExit() override;
	 CREATE_FUNC(spriteTouch);

};
