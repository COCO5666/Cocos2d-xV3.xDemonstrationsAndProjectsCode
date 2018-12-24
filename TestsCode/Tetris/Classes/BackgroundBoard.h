#ifndef _BACKGROUND_BOARD_H_
#define _BACKGROUND_BOARD_H_

#include "cocos2d.h"
#include "GlobalDefine.h"
#include "Tetromino.h"
#include <list>

USING_NS_CC;

typedef void (Ref::*SEL_ClearLine)(int numLine);
#define clearLine_selector(_SELECTOR) (SEL_ClearLine)(&_SELECTOR)

typedef void (Ref::*SEL_NextBlock)(int*);
#define nextBlock_selector(_SELECTOR) (SEL_NextBlock)(&_SELECTOR)

typedef void (Ref::*SEL_GameOver)();
#define gameOver_selector(_SELECTOR) (SEL_GameOver)(&_SELECTOR)

/**
 *  �װ�
 */
class BackgroundBoard : public Node
{
public:
	///��Ϸ��ʼ,�����¿�ʼ��ʱ����,��ͣ���������continueDrop
	void start();

	void pasueDrop();        ///<��ͣ��Ϸ
	void continueDrop();     ///<������Ϸ

	void tetrominoMove(); ///<�ǰ�ķ������½���,��һ���ص�����
	void setNextTetromino(); ///<�����µķ���,��һ���ص�����

	
	void setClearLineListener(Ref*,SEL_ClearLine);  ///<�����������Ļص�
	void setGameOverListener(Ref*,SEL_GameOver);    ///<����GameOver�Ļص�

	/**
	 *  ������һ�������Ÿı�Ļص�
	 *  ������ʾ�����һ��������ʲô��״��
	 */
	void setNextBlockListener(Ref*,SEL_NextBlock);   
	
	///��������һ��ĵȴ�ʱ��
	void setDropDelayTime(float dropDur)		 {m_dropDelayTime = dropDur;}

	bool isPause()								 {return m_isPause;}

	virtual bool init(float blockSize);
	virtual void onEnter();
    virtual void onExit();

	bool onTouchBegan(Touch *pTouch, Event *pEvent);
    void onTouchMoved(Touch *pTouch, Event *pEvent);
	void onTouchEnded(Touch *pTouch, Event *pEvent);
    void onTouchCancelled(Touch *pTouch, Event *pEvent);

	static BackgroundBoard* create(float blockSize);
private:
	float m_dropDelayTime;
	bool  m_bAccAction;
	bool  m_bGameOver;
	bool  m_isPause;
	bool  m_bAccMove;
	int   m_blockSize;
	int   m_bgInfo[BACKGROUND_ROW];

	std::list<int> m_next3Blocks;
	Point          m_touchPos;
	Node*          m_blockSprRow[BACKGROUND_ROW];
	Tetromino*     m_tetromino;
	
	Ref*           m_clearLineListener;
	SEL_ClearLine  m_clearLineCallback;
	Ref*           m_gameOverListener;
	SEL_GameOver   m_gameOverCallback;
	Ref*           m_nextBlockListener;
	SEL_NextBlock  m_nextBlockCallback;


	int  clearLine();          ///<�������������
	bool addToBg();            ///<����ǰ�ķ���ӵ��װ�����������
	void addNewTetromino();    ///<�����µķ���
	void gotoTargetPos();      ///<ֱ�ӽ��䵽������
	void onGameOver();
};

inline void BackgroundBoard::setClearLineListener(Ref* pObject,SEL_ClearLine callback)
{
	m_clearLineListener   = pObject;
	m_clearLineCallback  = callback;
}

inline void BackgroundBoard::setGameOverListener(Ref* pObject,SEL_GameOver callback)
{
	m_gameOverListener  = pObject;
	m_gameOverCallback = callback;
}

inline void BackgroundBoard::setNextBlockListener(Ref* pObject,SEL_NextBlock callback)
{
	m_nextBlockListener = pObject;
	m_nextBlockCallback = callback;
}
#endif