#pragma once
#include "cocos2d.h"
USING_NS_CC;
class sceneGraphPriority:public Layer
{
public:
	sceneGraphPriority(void);
	~sceneGraphPriority(void);
public:
    /**
     * ��̬����������Scene����
     * ע�⣺��Cocos2d-x��û��Cocos2d-iPhone�еġ�id��,���鷵����ʵ����ָ��
     */
    static Scene* createScene();
    /**
     * init��������ɳ�ʼ��������
     * ע�⣺init������Cocos2d-x�з���boolֵ�������Ƿ���Cocos2d-iPhone�еġ�id��
     */
    virtual bool init();
    
    // ѡ�����ص�����
    void menuCloseCallback(Ref* pSender);
    
    /**
     * ʹ��CREATE_FUNC�괴����ǰ��Ķ��󣬷��صĶ��󽫻����Զ��ͷųع����ڴ���ͷ�
     */
    CREATE_FUNC(sceneGraphPriority);
};

