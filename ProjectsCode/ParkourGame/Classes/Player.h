#pragma once
/*
//��Ϸ��ɫ��
*/
#include "cocos2d.h"
#include "common.h"
using namespace cocos2d;

class Player:public Node
{
public:
	virtual bool init() override;
	CREATE_FUNC(Player);
public:
	void run(); //���Ǳ���
	void jump(); //������Ծ
	void slide(); //���ǻ���
	PlayerState playerState; //��ɫ״̬
private:
	Sprite *playerSprite; //���ܵĽ�ɫ����
	Sprite *playerSpriteSlideJump; //���к������Ľ�ɫ����
	Animate *playerAnim;
	Texture2D *jumpTexture;
	Texture2D *slideTexture;
	
};
