
#ifndef  _Inkmoo_GameScene_h_
#define  _Inkmoo_GameScene_h_

#include "cocos2d.h"
#include "GameDefine.h"

USING_NS_CC;

class SpriteShape;

class GameScene : public Layer
{
public:
	GameScene();
	static Scene* createScene();
	CREATE_FUNC(GameScene);
	int m_time;
	
	void myClock( float dt );
	virtual bool init();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();
	virtual void onExitTransitionDidStart();
	virtual void cleanup();

	void update( float dt );
	bool onTouchBegan(Touch *touch, Event *unused);
    void onTouchMoved(Touch *touch, Event *unused);
	// ɾ��һ�л���һ��  ��3��ʱ��
	void addTime();
	// ����������
	void menuBackCallback(Ref *pSender);
	void menuSetCallback(Ref *pSender);
	void gameOver(float dt);
	CC_SYNTHESIZE(int, score, Score);

private:
	// ��ͼ�����½�����λ��
	float mapLBX,mapLBY;
	// ����һ��ͼƬ
	SpriteBatchNode *spriteSheet;
	// ��ά����
	SpriteShape* map[ROWS][COLS];
	// �ж��Ƿ���ִ�ж���
	bool isAction;
	// �����¼��Ƿ����ִ��
	bool isTouchEna;
	//�Ƿ��п�ȱ��Ҫ�
    bool isFillSprite;
	// Դ���飬Ŀ�꾫��
	SpriteShape* staSprite;
	SpriteShape* endSprite;
	// true: 4������������ը��.  false: 4������������ը��.
    bool fourBoom;


	// ��������
	void createSprite( int row , int col );
	//�õ���Ӧ���о��������ֵ
	Point positionOfItem(int row,int col);
	// ��ʼ����ά����
	void initMap();
	// ���ȱλ��
	void fillSprite();
	// ��鲢�ƶ�����
	void checkAndRemoveSprite();
	// �Ƴ�����
	void removeSprite();
	// ���Chain
	void getColChain(SpriteShape *spr, std::list<SpriteShape *> &chainList);
    void getRowChain(SpriteShape *spr, std::list<SpriteShape *> &chainList);
	// 
	void markRemove( SpriteShape* spr );
	// ��ը
	void explodeSprite( SpriteShape* spr );
	void explodeSpecialH(Point point);
    void explodeSpecialV(Point point);
	//
	void actionEndCallback(Node *node);
	// ��������
	void swapSprite();
	// ��ȡ����λ��
	SpriteShape *spriteOfPoint(Point *point);

	// ����Ƿ��п��ƶ��ľ���
	bool isHaveMove();
	int find( int r1 , int c1 , int r2 , int c2 , int r3 , int c3 );
};





#endif