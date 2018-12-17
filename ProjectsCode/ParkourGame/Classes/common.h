#pragma once
/*
//�������ͺͱ���ͷ�ļ�
*/

//��Ϸ�ؿ�ö��
enum Level
{
	SPRING,
	WINTER
};


//��Ϸ��ɫö��
enum PlayerType
{
	BOY,
	GIRL
};

//��Ϸ��ɫ״̬
enum PlayerState
{
	RUN,
	SLIDE,
	JUMP
};

//��ͼԪ��ö��
enum BlockType
{
	LAND,  //ש��
	NPC,   //����
	STAR,  //����
	TOOL,  //����
	NONE   //��
};

//�������������λ��Ϊ80���ֱ���800*480����������10*6�����ӣ���������ײ���
const float BLOCK_SIZE=80.0f; 
const float PICKUP_SIZE=40.0f;
const float PLAYER_RADIUS=50.0f;
const float GRAVITY=-1500.0f;
const float PLAYER_SPEED=700.0f;

