#include "cocos2d.h"

USING_NS_CC;

class Card : public Sprite
{
public:
	static Card* createCards(Color3B bgColor,Size cardSize);  
    virtual bool init(Color3B bgColor,Size cardSize);  
  
    void setLineIndex(int index);  
    int getLineIndex();  
  
    void removeCard();  
  
    //��ȡ������Ķ���  
    static Vector<Card*> *getCard();  
  
    //�������  
    static void renewVector();  

    //��ʾͼ��1
   void showO();

   //��ʾͼ��2
   void showX();

   //�趨����ж��Ƿ�Ӧ������
   void setFlag(int i);
   //��ȡ�������  ,����Ƿ���ͼƬ
   int getFlag();

   //�趨ͼ����ǣ����ͼƬ��ɫ

   void setPattern(int num);
   //��ȡͼ�����
   int getPattern();

private:  
  
    //���������Card  
    static Vector<Card*> *cards;  
  
    //��¼��Ƭ���ڵ���  
    int lineIndex;  

	//Card��Size
	 Size cSize;

	 //�ж��Ƿ�Ӧ��������
	 int flag;
  
	 //�жϵ�ǰ��Ƭ��ʲôͼ��,0��Ȧ��1�ǲ�
	 int pattern;
};