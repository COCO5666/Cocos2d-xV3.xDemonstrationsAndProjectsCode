#include "cocos2d.h"
using namespace cocos2d;
class WinLayer : public LayerColor
{
public:
	virtual bool init();
	CREATE_FUNC(WinLayer);
	void clickButton(Ref* sender);
	static void setstarNum(int starNum);
private:
	static int win_star;//Ϊ�˱���ͨ�����ǵ�������staticֻ��ʼ��һ�Σ��������ݣ�
	Size size;
};