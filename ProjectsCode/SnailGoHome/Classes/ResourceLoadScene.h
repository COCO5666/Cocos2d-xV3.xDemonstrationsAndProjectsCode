#include "cocos2d.h"
using namespace cocos2d;
class ResourceLoadScene : public Layer
{
public:
	static Scene * createScene();//������������̬���෽����
    virtual bool init();//���캯�����̳��Ը��࣬virtual�麯����

	//����layer���궨�塣���洫�Ĳ����ǵ�ǰ��������
	CREATE_FUNC(ResourceLoadScene);

	void startScene();
};