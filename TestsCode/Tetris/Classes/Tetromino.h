#ifndef  _TETROMINO_H_
#define  _TETROMINO_H_

#include "cocos2d.h"
#include "GlobalDefine.h"

USING_NS_CC;

struct TetrominoSize
{
	int _row;
	int _col;
};

/**
 * �߸���״�ķ�����,������ǰλ�õľ����������λ�õ���ʾ����
 * ע�⣺1.ԭ�������½�,����ĵ������������
 *       2.���캯��������������Ϊ˽��,�����þ�̬����create����,��̬����destory����
 */
class Tetromino
{
public:
	static Tetromino* create(int shape,float blockSize,const int* bgInfo,Node* parent,bool bCreateTarget = true);
	static void destory(Tetromino** pTetromino);

	bool clockwiseRotate(const int* bgInfo);  ///<˳ʱ����ת
	bool move(bool bLeft,const int* bgInfo);  ///<�����ƶ�
	bool drop(const int* bgInfo);             ///<�½�

	bool setCol(int c,const int* bgInfo);
	bool setRow(int r,const int* bgInfo);

	int getCol()       {return m_col;}
	int getRow()       {return m_row;}
	int getRotate()    {return m_rotate;}
	int getShape()     {return m_shape;}
	int getTargetRow() {return m_targetRow;}  

	void setCurBlockNodePos(const Vec2& position)
	{
		m_curBlockNode->setPosition(position);
	}

	void setCurBlockNodeScale(float scale)
	{
		m_curBlockNode->setScale(scale);
	}

	void setCurBlockNodeAction(Action* action)
	{
		m_curBlockNode->runAction(action);
	}

	void setCurBlockNodeVisible(bool bVisible)
	{
		m_curBlockNode->setVisible(bVisible);
	}

	///ֱ�ӽ��䵽���Խ��������µ�һ��
	int gotoTargetPos(const int* bgInfo);

	///�õ���С
	TetrominoSize getTetrominoSize();

	///�ж��Ƿ�����������
	bool isTouch(Point worldCoord);

	///�жϴ����Ƿ��ڷ�������·�
	bool isUnderTetromino(Point worldCoord);

	///�жϴ����Ƿ��ڷ��������
	bool isBesideTetromino(Point worldCoord);

private:
	Tetromino();
	~Tetromino(){}

	int   m_shape;      ///<�������״
	int   m_col;        ///<���鵱ǰλ�õ���
	int   m_row;        ///<���鵱ǰλ�õ���
	int   m_targetRow;  ///<�����������У����Խ��������µ�һ�У�
	int   m_rotate;     ///<����˳ʱ����ת�Ĵ���
	float m_blockSize;  ///<С������block�Ĵ�С���߳���

	Node*    m_curBlockNode;          ///<��ǰ����λ�õ���ʾ����͹���������
	Sprite*  m_curBlockSprites[4];    ///<��ǰ����λ�õ���ʾ����

	Sprite*  m_targetBlockSprites[4]; ///<�������ս���λ�õ���ʾ����
	Node*    m_targetBlockNode;       ///<�������ս���λ�õ���ʾ����͹���������

	bool init(int shape,float blockSize,const int* bgInfo,Node* parent,bool bCreateTarget);

	void removeNodes();

	Sprite* createBlockSprite(int shape);

	///����block�����λ��(�ڵ�����ϵ��)
	void setBlockSprPos(Sprite* sprites[4]);      

	///���㷽����ʾ����ڵ��λ�ã��װ�����ϵ�У�
	void computeTargetNodePos(const int* bgInfo);

	///�жϷ����Ƿ���װ������������ײ
	bool isCollision(int col,int row,int rotate,const int* bgInfo);

	///�������ս���λ�õ���ʾ����ľ���
	bool createTargetBlockNode(const int* bgInfo,Node* parent);
};

#endif