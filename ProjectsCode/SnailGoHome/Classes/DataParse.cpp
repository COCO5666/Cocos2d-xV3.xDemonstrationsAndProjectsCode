#include "DataParse.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include  "json/stringbuffer.h"
#include "json\writer.h"

//Ϊ���ڿ�д·��������һ���ļ������ڴ��ص�ʱ���޸����ݣ�
void DataParse::copyFile()
{
	//��ȡ�ɶ�д�Ļ���·��
	std::string  writePath =FileUtils::getInstance()->getWritablePath();
	//���ݿɶ�д·����ƴ�ӳ���д���ļ�Data.json·��
	writePath = writePath +"Data.json";
	//��Դ����ļ�Data.json·����
	std::string  filefullPath=FileUtils::getInstance()->fullPathForFilename("Data.json");
	log("fullPath=%s",filefullPath.c_str());//���Ի�ȡ��ȫ·��
	//��д·���µ��ļ��Ƿ����
	if(!FileUtils::getInstance()->isFileExist(writePath))
	{
		std::string data=FileUtils::getInstance()->getStringFromFile(filefullPath);
		FILE *file=fopen(writePath.c_str(),"w");
		if(file)
		{
			fputs(data.c_str(),file);
			fclose(file);
		}

	}
}
//����������״ֵ̬lock������õ�������star�������Ǵ浽�ֵ�dic�У����շ�������ֵ�dic
__Dictionary * DataParse::getChapter(int chaperIndex)
{
	//�ȿ�������д·����
	copyFile();
	std::string  writePath=FileUtils::getInstance( )->getWritablePath( );
	writePath=writePath  +  "Data.json";
	log("WritablePath=%s",writePath.c_str());
	std::string data=FileUtils::getInstance( )->getStringFromFile(writePath);
	log("WritablePathNR=%s",data.c_str());
	//��������
	rapidjson::Document  doc;
	//��ʼ����
	doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());
	//�жϽ����Ƿ������
	if(doc.HasParseError())
	{
		return 0;
	}
	__Dictionary *dic=__Dictionary::create();
	char chapterName[20];	
	//ͨ��������½ڣ�key����ƴ�ӳ�json�ļ�����½�(����Ϸ�Ѷȵ�)��ǩ����
	sprintf(chapterName,"chapter_%d",chaperIndex);	
	for (int i = 1; i <= 6; i++)
	{
		//�ؿ�
		char level[20];		
		sprintf(level,"level_%d",i);
		
		//�Զ������ͨ��ѭ��������ƴ�ӳ�json�ļ���Ĺؿ���ǩ������
		char lock[20];		
		sprintf(lock,"level_%d_lock",i);
		
		//ͨ��ѭ��������ƴ�ӳ�json�ļ�������Ǳ�ǩ������
		char star[20];
		sprintf(star,"level_%d_star",i);
	    Integer *lockValue=Integer::create(doc[chapterName][level]["lock"].GetInt());
		Integer *starValue=Integer::create(doc[chapterName][level]["star"].GetInt());
		dic->setObject(lockValue,lock);
		dic->setObject(starValue,star);
	}
	return dic;
}
//��ȡ�ؿ��еĸ�����
 int DataParse::getNum(int chapterIndex,int levelIndex)
 {
	 std::string  writePath=FileUtils::getInstance()->getWritablePath();
	 writePath = writePath + "Data.json";
	 std::string  data=FileUtils::getInstance()->getStringFromFile(writePath);
	 rapidjson::Document  doc;
	 doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());
	 if( doc.HasParseError())
	 {
		 return 0;
	 }
	 char chapterName[20];
     sprintf(chapterName,"chapter_%d",chapterIndex);
	 char levelName[20];
	 sprintf(levelName,"level_%d",levelIndex);
	 int  num=doc[chapterName][levelName]["num"].GetInt();
	 return num;
 }
 //������������������ǰ��Ϸ����õ�������������json�ļ�
 void DataParse::setStar(int chapterIndex,int levelIndex,int starNum)
 {
	 std::string writePath=FileUtils::getInstance()->getWritablePath();
	 writePath= writePath + "Data.json";
	 std::string data=FileUtils::getInstance()->getStringFromFile(writePath);
	 rapidjson::Document doc;
	 doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());
	 if(doc.HasParseError())
	 {
		 return  ;
	 }
	 char chapterName[20];
	 sprintf(chapterName,"chapter_%d",chapterIndex);
	 char levelName[20];
	 sprintf(levelName,"level_%d",levelIndex);
	 //��json�ļ��н�����֮ǰ�洢������������starNum�����������ͱ���num��
	 int num=doc[chapterName][levelName]["star"].GetInt();

	 /*�ѵ�ǰ��Ϸ�����л�õ�������starNum���json�н���������֮ǰ��������num���бȽϣ����Ƚ�starNum��num��
	 ����ǰ���õ�������starNum�����starNum�浽json�ļ��У���Ϊ���õ�����������
		 */
	 if(num< starNum)
	 {
		 doc[chapterName][levelName]["star"].SetInt(starNum);//��starNum����rapidjson��doc��
		 if(starNum==3 && levelIndex!=6)
		 {
			 char nextLevelName[20];
			 sprintf(nextLevelName,"level_%d",levelIndex+1);
			 //ͨ������setInt������������0���浽json�ļ���lock״̬�У���˼�ǰ���һ�ؽ���
			 doc[chapterName][nextLevelName]["lock"].SetInt(0);
		 }

		 //д������
		 writefile(doc,writePath);
	 }
 }
 //����д�루���ǣ����Ȱ�����setStar������json�ĵ�doc������ͨ��rapidjsonд����д�뵽����buffer�У���ͨ������fputs�����ѻ�����buffer�е�����ת��ɡ�������ʽ����json�ļ�
void  DataParse::writefile(rapidjson::Document &document, std::string path)
{
	rapidjson::StringBuffer buffer;//��ʼ��������
	rapidjson::Writer<rapidjson::StringBuffer>write(buffer);//��ʼ��д����
    document.Accept(write);//д��buffer
	FILE *file=fopen(path.c_str(),"w");
	//��ԭ�����ļ����ݸ���
	if(file)
	{
		fputs(buffer.GetString(),file);
		fclose(file);
	}
}

//��json�ļ�������rapidjson��ʽ��doc����doc�л�ȡ�½ڹؿ��ж�Ӧ��������
 int DataParse::getStar(int chapterIndex,int levelIndex)
 {
	 std::string writePath=FileUtils::getInstance()->getWritablePath();
	 writePath= writePath + "Data.json";
	 std::string data=FileUtils::getInstance()->getStringFromFile(writePath);
	 rapidjson::Document doc;
	 doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());
	 if(doc.HasParseError())
	 {
		 return 0 ;
	 }
	 char chapterName[20];
	 sprintf(chapterName,"chapter_%d",chapterIndex);
	 char levelName[20];
	 sprintf(levelName,"level_%d",levelIndex);
	 int num=doc[chapterName][levelName]["star"].GetInt();
	 return num;
 }