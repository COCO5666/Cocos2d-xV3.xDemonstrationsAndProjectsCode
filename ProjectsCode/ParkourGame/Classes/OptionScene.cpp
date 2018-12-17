#include "OptionScene.h"
#include "common.h"
#include "MainMenu.h"

//����ȫ�ֱ����ɼ���
extern Level level;
extern PlayerType playerType;
extern bool isSound;

//����lambda���ʽ�����ⲿ�����鷳����д��ȫ����
LabelBMFont *textLevel;
LabelBMFont *textPlayer;
LabelBMFont *textSound;

bool OptionScene::init()
{
	if(!Scene::init())
		return false;

	auto visibleSize=Director::getInstance()->getVisibleSize();
	auto visibleOrigin=Director::getInstance()->getVisibleOrigin();
	//����
	//��Ӷ�̬����
	auto backGround=Sprite::create("option.png");
	backGround->setPosition(visibleOrigin.x+visibleSize.width/2,visibleOrigin.y+visibleSize.height/2);
	auto repeatAnim=MoveBy::create(3.0f,Vec2(0,40));
	backGround->runAction(RepeatForever::create(Sequence::create(repeatAnim,repeatAnim->reverse(),NULL)));
	this->addChild(backGround,0);

	//����
	textLevel=LabelBMFont::create("level: Spring","bitmapFontChinese.fnt");
	textLevel->setPosition(visibleOrigin.x+150,visibleOrigin.y+200);
	this->addChild(textLevel);

	textPlayer=LabelBMFont::create("player: Boy","bitmapFontChinese.fnt");
	textPlayer->setPosition(visibleOrigin.x+150,visibleOrigin.y+170);
	this->addChild(textPlayer);

	textSound=LabelBMFont::create("sound: On","bitmapFontChinese.fnt");
	textSound->setPosition(visibleOrigin.x+150,visibleOrigin.y+140);
	this->addChild(textSound);

	//�˵�
	//���ذ�ť
	auto backItem=MenuItemImage::create("back_btn.png","back_btn_press.png",[](Object *sender)
	{
		//��lambda���ʽ��Ϊ�˵������ص�
		auto mainMenu=MainMenu::createScene();
		TransitionScene *transition=TransitionFade::create(1.0f,mainMenu);
		Director::getInstance()->replaceScene(transition);
	});
	backItem->setPosition(visibleOrigin.x+backItem->getContentSize().width/2,visibleOrigin.y+visibleSize.height-backItem->getContentSize().height/2);
	

	//����
	auto springItem=MenuItemImage::create("spring_icon.png","spring_icon_press.png",[](Object *sender)
	{
		//�޸Ĺؿ�
		level=SPRING;
		textLevel->setString("level: Spring");
	});
	

	springItem->setPosition(visibleOrigin.x+visibleSize.width/4+35,visibleOrigin.y+visibleSize.height/4*3);
	//����
	auto winterItem=MenuItemImage::create("winter_icon.png","winter_icon_press.png",[](Object *sender)
	{
		//�޸Ĺؿ�
		level=WINTER;
		textLevel->setString("level: Winter");
	});
	winterItem->setPosition(visibleOrigin.x+visibleSize.width/4*3-35,visibleOrigin.y+visibleSize.height/4*3);
	//����
	auto boyItem=MenuItemImage::create("boy1.png","boy_jump.png",[](Object *sender)
	{
		//�޸Ľ�ɫ
		playerType=BOY;
		textPlayer->setString("player: Boy");
	});
	boyItem->setPosition(visibleOrigin.x+visibleSize.width/2,visibleOrigin.y+visibleSize.height/2-100);
	//Ů��
	auto girlItem=MenuItemImage::create("girl1.png","girl_jump.png",[](Object *sender)
	{
		//�޸Ľ�ɫ
		playerType=GIRL;
		textPlayer->setString("player: Girl");
	});
	girlItem->setPosition(visibleOrigin.x+visibleSize.width/2+200,visibleOrigin.y+visibleSize.height/2-100);

	//��������
	auto soundItem=MenuItemImage::create("sound_on.png","sound_off.png",[](Object *sender)
	{
		//�޸�����
		isSound=!isSound;
		textSound->setString(isSound?"sound: On":"sound: Off");
	});
	soundItem->setPosition(visibleOrigin.x+soundItem->getContentSize().width/2,visibleOrigin.y+soundItem->getContentSize().height/2);


	auto menu=Menu::create(backItem,springItem,winterItem,boyItem,girlItem,soundItem,NULL);
	menu->setPosition(Point::ZERO);

	this->addChild(menu);
	return true;
}