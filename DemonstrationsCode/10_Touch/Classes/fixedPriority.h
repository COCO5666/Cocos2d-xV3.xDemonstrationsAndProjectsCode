#pragma once
#include <iostream>
#include "cocos2d.h"
USING_NS_CC;
class fixedPriority :public Layer
{
public:
	fixedPriority(void);
	~fixedPriority(void);
	    /**
     * ��̬����������Scene����
     * ע�⣺��Cocos2d-x��û��Cocos2d-iPhone�еġ�id��,���鷵����ʵ����ָ��
     */
    static cocos2d::Scene* createScene();
    /**
     * init��������ɳ�ʼ��������
     * ע�⣺init������Cocos2d-x�з���boolֵ�������Ƿ���Cocos2d-iPhone�еġ�id��
     */
    virtual bool init();
    
    // ѡ�����ص�����
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    /**
     * ʹ��CREATE_FUNC�괴����ǰ��Ķ��󣬷��صĶ��󽫻����Զ��ͷųع����ڴ���ͷ�
     */
    CREATE_FUNC(fixedPriority);

};

