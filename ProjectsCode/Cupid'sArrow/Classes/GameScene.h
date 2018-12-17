#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <iostream>
using namespace cocos2d;
using namespace ui;
static int _level = 1; // ��ǰ�ؿ���
static int _i = 4;
static int _i1 = 0;
static int _i2 = 0;
class GameScene : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();
	
	Sprite* y;
	void againGame();
	void goNext();
	void continueGame();
	virtual void update(float delta);
	  void addxin(float delta);
	  void gameOver(float delta);
	// a selector callback
	 void popying(Sprite* ying);
	//void menuCloseCallback(cocos2d::Ref* pSender);
	//void addshitou();
	Vector<Sprite*> _xinVector;
	Vector<Sprite*> _jianVector;
	//static bool iscollision(Sprite *sprite2,Sprite *sprite1);
private:
	  int _screenWidth , _screenHeight; 
	  LoadingBar * _timeBar; // ��ʱ��������
	  float _timeBarInterval; // ʱ�������
	  bool _gameOver; // ��Ϸ�Ƿ����
	  Sprite* xin;
	  Sprite* jian;
	  Sprite* _levelSprite;
	  Label* _levelLabel; // �ؿ�����Label

	  Sprite* child;
	  Sprite* child1;

	  Sprite* _passSprite;
	  Label* _passLabel; // ���ط�����Label

	  Sprite* _scoreSprite;
	  Label* _scoreLabel; // ��ʾ������Label

	  Sprite* _xinSprite;
	  Label* _xinLabel; 

	 // Label* shitoushu;
	 // Sprite* jiashitou;
	  int _score;  // ����
	  int _sucessScore; // ����Ŀ�����
	  int _totalxin; 
	  void setHit(Ref* pSender);
	  void unHit(Ref* pSender);
	  float a;
	  	FlipX* act1;
		
	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);
};

