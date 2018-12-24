#ifndef _GAME_SCENE_H_
#define _GAME_SCENE_H_

#include "cocos2d.h"
#include "editor-support\cocostudio\CocoStudio.h"
#include "ui\CocosGUI.h"
#include "network/HttpClient.h"
#include "BackgroundBoard.h"
#include "Tetromino.h"
#include "GameLayoutManager.h"
#include "NumberCount.h"
#include "RankList.h"
#include <list>
#include "editor-support\cocostudio\DictionaryHelper.h"

USING_NS_CC;
using namespace ui;

class GamesScence : public Layer
{
public:
    virtual bool init();  

    static Scene* scene();

	/*��ť�Ļص�����*/
	///�˵���ť
	void btMenuCallback(Ref* pSender,Widget::TouchEventType type);

	///��ʼ��ť
    void btStartCallback(Ref* pSender,Widget::TouchEventType type);

	///���¿�ʼ��ť
	void btRestartCallback(Ref* pSender,Widget::TouchEventType type);

	///������Ϸ��ť
	void btContinueCallback(Ref* pSender,Widget::TouchEventType type);

	///���а�ť
	void btRankListCallback(Ref* pSender,Widget::TouchEventType type);

	///������ť
	void btHelpCallback(Ref* pSender,Widget::TouchEventType type);

	///�뿪��Ϸ��ť
	void btLeaveCallback(Ref* pSender,Widget::TouchEventType type);

	///ȷ����ť���ϴ�������
	void btConfirmationCallback(Ref* pSender,Widget::TouchEventType type);

	///ȡ����ť���ϴ�������
	void btCancelCallback(Ref* pSender,Widget::TouchEventType type);

	/*BackgroundBoard����Ϣ�ص�*/
	///�ӷ֣���һ�л���б�������
    void onAddScore(int numLineCleared);

	///��ʾ�¸��������״
	void onNextBlock(int* next3Blocks);

	///GameOver
	void onGameOver();

	/*HttpTool����Ϣ�ص�*/
	///�õ������Ļص�
	void getPositionResponse(int score);

	///�ϴ������Ļص�
	void uploadScoreResponse(bool b);

    CREATE_FUNC(GamesScence);

private:

	GameLayoutManager m_panelManager;  ///�˵������а�gameover�㡢�ϴ�������Щ��һ��ֻ�ܳ���һ��,����������
	BackgroundBoard*  m_bgBpard;       ///<��Ϸ�װ�,����Ľ��䡢�����ƶ�����ת�ȵȵ��߼���������ʵ��
	NumberCount       m_scoreCount;    ///<��ʾ����
	NumberCount       m_clearCount;    ///<��ʾ�����˶�����
	TextAtlas*        m_highestLabel;  ///<��ʾ��߷�
	Button*           m_btMenu;        ///<�˵���ť
	TextField*        m_nickNameInput; ///<�����ǳƵ������
	ImageView*        m_imgFrame;      ///<��Ϸ�װ���ݺ���
	RankList*       m_list;          ///<���а񣨹�����,��������Ľ���������ʵ�֣�

	std::list<Tetromino*> m_next3Tetrominos; ///<�������������ʾ����ʾ��״��

	float m_blockSize;      ///<����Ĵ�С����Щ�����εı߳���
	float m_dropDelayTime;  ///<����ÿ�½�һ����ӳ�ʱ��
	int   m_clearLineCount; ///<����еļ���
	bool  m_isGgameRunning; ///<��Ϸ�Ƿ����������У����ھ����ǿ�ʼ��Ϸ���Ǽ�����Ϸ��
	Point m_nextTipPos;     ///<��һ���������ʾλ��
	Size  m_nextTipSize;    ///<��һ���������ʾ��С
	

	void startGame();
};

#endif 
