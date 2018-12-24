#ifndef _GAME_LAYOUT_MANAGER_H_
#define _GAME_LAYOUT_MANAGER_H_

#include "cocos2d.h"
#include "editor-support\cocostudio\CocoStudio.h"
#include "ui\CocosGUI.h"

USING_NS_CC;
using namespace ui;

#define TAG_BUTTON_START 0
#define TAG_BUTTON_CONTINUE 1


/**
 * ÿ��ֻ����һ��Widget�ɼ�
 * ������Widget�Ƿ�ɼ���ʱ���������ĵ�һ�㺢�ӵ��Ƿ�ɼ����Ƿ�ɴ�����ͬʱ����
 */
class GameLayoutManager
{
public:
	GameLayoutManager():m_visibleLayout(0){}

	void setUploadScorePanel(Layout* uploadScorePanel) {m_uploadScorePanel = uploadScorePanel;}
	void setMenuPanel(Layout* menuPanel)               {m_menuPanel        = menuPanel;}
	void setGameOverPanel(Layout* gamrOverPanel)       {m_gamrOverPanel    = gamrOverPanel;}
	void setRankList(ListView* rankList)               {m_rankList         = rankList;}

	void setMenuPanelVisible(bool bGameRunning, bool visible);
	void setGameOverPanelVisible(bool visible);
	void setUploadScorePanelVisible(int position,bool visible);
	void setRankListVisible(bool visible);
private:
	Layout*  m_visibleLayout;

	Layout* m_menuPanel;
	Layout* m_gamrOverPanel;
	Layout* m_uploadScorePanel;
	ListView* m_rankList;

	///�����Ƿ�ɼ�,�Ƿ�ɴ�����ͬʱ����
	bool setLayoutVisible(Layout* widget,bool visible);

	void setChildrenVisible(Layout* widget,bool visible);
};

#endif