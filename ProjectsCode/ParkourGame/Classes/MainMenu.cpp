#include "MainMenu.h"
#include "GameScene.h"
#include "OptionScene.h"
#include "AboutScene.h"

extern bool isSound;

Scene *MainMenu::createScene()
{
	auto *scene=Scene::create();
	auto *layer=MainMenu::create();
	scene->addChild(layer);
	return scene;
}

bool MainMenu::init()
{
	if(!Layer::init())
		return false;

	//��ȡ��Ļ��С��ԭ��λ��
	auto visibleSize=Director::getInstance()->getVisibleSize();
	auto visibleOrigin=Director::getInstance()->getVisibleOrigin();

	//��ӱ���ͼƬ
	auto menuBackGround=Sprite::create("main_menu.jpg");
	menuBackGround->setPosition(Point(visibleOrigin.x+visibleSize.width/2,visibleOrigin.y+visibleSize.height/2));
	this->addChild(menuBackGround,0);

	//��ӽ�ɫ����
	auto boySprite=Sprite::create();
	boySprite->setPosition(visibleOrigin.x+visibleSize.width/2-60,visibleOrigin.y+visibleSize.height/2+90);
	this->addChild(boySprite,0);
	auto boyAnim=Animate::create(AnimationCache::getInstance()->animationByName("boyAnimation"));
	boySprite->runAction(RepeatForever::create(boyAnim));  //�ӳᶯ��

	auto girlSprite=Sprite::create();
	girlSprite->setPosition(visibleOrigin.x+visibleSize.width/2+60,visibleOrigin.y+visibleSize.height/2+100);
	this->addChild(girlSprite,0);
	auto girlAnim=Animate::create(AnimationCache::getInstance()->animationByName("girlAnimation"));
	girlSprite->runAction(RepeatForever::create(girlAnim));  //�ӳᶯ��


	//��Ӳ˵�
	auto newGameItem=MenuItemImage::create("newgameA.png","newgameB.png",CC_CALLBACK_1(MainMenu::menuStartCallback,this));
	newGameItem->setPosition(Point(visibleOrigin.x+visibleSize.width/2,visibleOrigin.y+visibleSize.height/2));
	
	auto optionItem=MenuItemImage::create("option_btn.png","option_btn.png",CC_CALLBACK_1(MainMenu::menuOptionCallback,this));
	optionItem->setPosition(Point(visibleOrigin.x+visibleSize.width/2,visibleOrigin.y+visibleSize.height/2-60));
	
	auto aboutItem=MenuItemImage::create("aboutA.png","aboutB.png",CC_CALLBACK_1(MainMenu::menuAboutCallback,this));
	aboutItem->setPosition(Point(visibleOrigin.x+visibleSize.width/2,visibleOrigin.y+visibleSize.height/2-120));


	auto menu=Menu::create(newGameItem,optionItem,aboutItem,NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu,1);

}


void MainMenu::onEnter()
{
	//�˴�������ø����onEnter���򶯻�����
	Layer::onEnter();
}

void MainMenu::onExit()
{
	//�˴������븸���onEnter�ɶԳ��֣���������ʱ����
	Layer::onExit();
	//���뿪����ʱ�����ڴ˴��ͷ�һЩ�������
}

void MainMenu::menuStartCallback(Ref *sender)
{
	//��ת����Ϸ����
	auto gameScene=GameScene::createScene();
	TransitionScene *transition=TransitionPageTurn::create(0.5f,gameScene,false);
	Director::getInstance()->replaceScene(transition);
}

void MainMenu::menuOptionCallback(Ref *sender)
{
	//��ת��ѡ���
	auto optionScene=OptionScene::create();
	TransitionScene *transition=TransitionPageTurn::create(0.5f,optionScene,false);
	Director::getInstance()->replaceScene(transition);
}

void MainMenu::menuAboutCallback(Ref *sender)
{
	//��ת�����ڳ���
	auto aboutScene=AboutScene::create();
	TransitionScene *transition=TransitionPageTurn::create(0.5f,aboutScene,false);
	Director::getInstance()->replaceScene(transition);
}
