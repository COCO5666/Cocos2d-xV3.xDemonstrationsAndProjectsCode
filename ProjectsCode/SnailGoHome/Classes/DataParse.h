#pragma once
#include "cocos2d.h"
USING_NS_CC;
#include "json\rapidjson.h"
#include "json\document.h"
class DataParse//����̳��κθ���
{
public:
	//����Դ·���µ�Դ�ļ����Ƶ�������AppDate�У�������һ���ɶ�д���ļ������ڴ��ص�ʱ���޸�����
	static  void copyFile( );
	//�ѷ��������static��Ŀ�����κεط����Բ��ö��󣬶�ֱ�����ã������ö������÷Ǿ�̬�����Ļ������"�Ǿ�̬��Ա���ñ������ض������Ӧ"
	static __Dictionary * getChapter(int chaperIndex);
	static int getNum(int chapterIndex,int levelIndex);//��ȡ��������
	static void setStar(int chapterIndex,int levelIndex,int starNum);//�������ǵ�����
	static int getStar(int chapterIndex,int levelIndex);//�õ���������
	static void writefile(rapidjson::Document &document, std::string path);//����д�� 
	
};

