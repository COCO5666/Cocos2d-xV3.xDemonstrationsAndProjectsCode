#pragma once
/*
//��ϷԤ������
*/
#include "cocos2d.h"
class LoadingScene : public cocos2d::Scene
{
public:
	virtual bool init() override;
	CREATE_FUNC(LoadingScene);
private:
	virtual void onEnter() override;
	void loadingCallBack(cocos2d::Texture2D *texture); //���ػص�����

private:
	cocos2d::ProgressTimer *loadProgress; //������
	int totalNum; //�ܹ�Ҫ���ص���Դ
	int loadedNum; //�Ѿ����ص���Դ��
};