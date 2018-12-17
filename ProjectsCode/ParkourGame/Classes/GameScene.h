#pragma once
/*
//��Ϸ��������
*/

#include "cocos2d.h"
#include "Player.h"
#include "GameMap.h"
USING_NS_CC;

class GameScene: public Layer
{
public:
	static Scene *createScene();

	CREATE_FUNC(GameScene);
private:
	virtual bool init() override;
	virtual void onEnter() override;
	virtual void onExit() override;
	//�������
	virtual bool onTouchBegan(Touch *touch,Event *event) override;
	virtual void onTouchEnded(Touch *touch,Event *event) override;
	//��ײ���
	bool onContactBegin(const PhysicsContact &contact);
	//ˢ��
	virtual void update(float dt) override;
private:
	void backGroundUpdate(float dt); //��������
	void addScore(float number); //�÷�
	void gameOver(); //��Ϸ����
private:
	Size visibleSize;
	Point visibleOrigin;

	Player *player; //��ɫ

	//�������ư�ť
	Sprite *slideBtn;
	Vector<Texture2D *> slideBtnTextures;
	Sprite *jumpBtn;
	Vector<Texture2D *> jumpBtnTextures;

	Sprite *backGround1,*backGround2; //����
	GameMap *gameMap; //��ͼ

	int score; //����
	LabelBMFont *scoreLabel; //��������
};