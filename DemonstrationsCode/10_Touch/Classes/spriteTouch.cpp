#include "spriteTouch.h"
#include <iostream>

spriteTouch::spriteTouch(void)
{
}


spriteTouch::~spriteTouch(void)
{
}

  // ���������ȼ������Ƶĺ���
 void spriteTouch::setPriority(int fixedPriority,const char* name)
 {
        _fixedPriority = fixedPriority;
        _name = name;
 };
    
void spriteTouch:: onEnter() 
 {
        Sprite::onEnter();
        // ����һ�����㴥��
        auto listener = EventListenerTouchOneByOne::create();
        // �����¼��Ƿ�������´���
        listener->setSwallowTouches(false);
        
        // ͨ�� lambda ���ʽ ֱ��ʵ�ִ����¼��Ļص�����
        listener->onTouchBegan = [=](Touch* touch, Event* event){
            // ��õ�ǰ�Ĵ�����
            Vec2 locationInNode = this->convertToNodeSpace(touch->getLocation());
            // ��ô��������ContentSize
            Size s = this->getContentSize();
            // ���λ�þ���
            Rect rect = Rect(0, 0, s.width, s.height);
            // �ж�λ�þ��ΰ���������
            if (rect.containsPoint(locationInNode))
            {
                 // �����Ӧ�ľ����ͼƬ���ƺ����ȼ�
                log("onTouchBegan...��Ӧ�¼�����%s, ���ȼ�=%d, x = %f, y = %f", _name,_fixedPriority,locationInNode.x, locationInNode.y);
                this->setOpacity(180);
				return true;
            }
            return false;
        };
        
        listener->onTouchMoved = [=](Touch* touch, Event* event){
            log("onTouchMoved... ");
            // �ƶ�����
            this->setPosition(this->getPosition() + touch->getDelta());
        };
        
        listener->onTouchEnded = [=](Touch* touch, Event* event){
            log("onTouchEnded..");
			this->setOpacity(255);
        };
        
        // �ڼ���touch�¼������ȼ�ֵС�ľ��齫���Ƚ��ܴ����¼�
        _eventDispatcher->addEventListenerWithFixedPriority(listener, _fixedPriority);
        _listener = listener;
}
    
void spriteTouch::onExit() 
    {
        log("onExit...");
        // ��ɾ���¼�������
        _eventDispatcher->removeEventListener(_listener);
        Sprite::onExit();
    };