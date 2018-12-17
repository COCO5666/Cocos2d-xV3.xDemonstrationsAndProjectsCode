#include "SimpleAudioEngine.h"
#include "common.h"
#include "MainMenu.h"
#include "GameScene.h"
#include "GameMap.h"

using namespace CocosDenshion;

//��ʼ��ȫ�ֱ���
extern Level level=SPRING;
extern PlayerType playerType=BOY;
extern bool isSound=true;

int jumpTimes=0; //��ǰ��Ծ����
int jumpTotal=2; //�����Ծ����

Scene *GameScene::createScene()
{
	//��ʼ������Ϸ������
	auto *scene=Scene::createWithPhysics();
	scene->getPhysicsWorld()->setGravity(Vec2(0,GRAVITY));
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL); //����ģʽ����Χ��
	//��ʼ����layer
	auto *layer=GameScene::create();
	scene->addChild(layer);
	return scene;
}

bool GameScene::init()
{
	if(!Layer::init())
		return false;

	//��ȡ��Ļ��С��ԭ��λ��
	visibleSize=Director::getInstance()->getVisibleSize();
	visibleOrigin=Director::getInstance()->getVisibleOrigin();

	//��ӱ���
	std::string backGroundFile;
	switch(level)
	{
	case SPRING:
		backGroundFile="back_spring.png";
		break;
	case WINTER:
		backGroundFile="back_winter.png";
		break;
	}
	backGround1=Sprite::create(backGroundFile);
	backGround1->setAnchorPoint(Point::ZERO);
	backGround1->setPosition(Point::ZERO);
	this->addChild(backGround1,0);
	backGround2=Sprite::create(backGroundFile);
	backGround2->setAnchorPoint(Point::ZERO);
	backGround2->setPosition(Point::ZERO);
	this->addChild(backGround2,0);

	//���õ�ͼ,Ĭ��ê�������½�
	gameMap=GameMap::create();
	gameMap->setPosition(visibleOrigin.x,visibleOrigin.y);
	this->addChild(gameMap,1);



	//���player
	player=Player::create();
	player->setPosition(Point(visibleOrigin.x+2*BLOCK_SIZE,visibleOrigin.y+4*BLOCK_SIZE));
	this->addChild(player,1);


	//��ӻ��к���Ծ��ť���¼�
	score=0; //��ʼ������

	slideBtn=Sprite::create("slideButton.png");
	auto slideBtnTexture1=Sprite::create("slideButton.png")->getTexture();
	auto slideBtnTexture2=Sprite::create("slideButtonPress.png")->getTexture();
	slideBtnTextures.pushBack(slideBtnTexture1);
	slideBtnTextures.pushBack(slideBtnTexture2);
	slideBtn->setScale(0.5);
	slideBtn->setPosition(Point(visibleOrigin.x+100,visibleOrigin.y+50));
	this->addChild(slideBtn,2);

	jumpBtn=Sprite::create("jumpButton.png");
	auto jumpBtnTexture1=Sprite::create("jumpButton.png")->getTexture();
	auto jumpBtnTexture2=Sprite::create("jumpButtonPress.png")->getTexture();
	jumpBtnTextures.pushBack(jumpBtnTexture1);
	jumpBtnTextures.pushBack(jumpBtnTexture2);
	jumpBtn->setScale(0.5);
	jumpBtn->setPosition(Point(visibleOrigin.x+visibleSize.width-100,visibleOrigin.y+50));
	this->addChild(jumpBtn,2);

	//��ӻ���UI��������
	scoreLabel=LabelBMFont::create("score: ","bitmapFontChinese.fnt");
	scoreLabel->setPosition(visibleOrigin.x+visibleSize.width-150,visibleOrigin.y+visibleSize.height-20);
	this->addChild(scoreLabel,2);
	scoreLabel->setString(String::createWithFormat("score: %d",score)->_string);


	this->scheduleUpdate();//����Ĭ�ϸ���
	this->schedule(schedule_selector(GameScene::backGroundUpdate),0.02f); //��������ѭ������

	//�����ײ���
	auto contactListener=EventListenerPhysicsContact::create();
	contactListener->onContactBegin=CC_CALLBACK_1(GameScene::onContactBegin,this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener,this);

	//��Ӵ�������
	auto touchListener=EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan=CC_CALLBACK_2(GameScene::onTouchBegan,this);
	touchListener->onTouchEnded=CC_CALLBACK_2(GameScene::onTouchEnded,this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener,this);

	return true;
}

bool GameScene::onTouchBegan(Touch *touch,Event *event)
{
	auto touchPoint=touch->getLocation();
	//����Ƿ����ڰ�ť����
	if(slideBtn->getBoundingBox().containsPoint(touchPoint))
	{
		slideBtn->setTexture(slideBtnTextures.at(1));
		player->slide();
	}

	if(jumpTimes<jumpTotal&&jumpBtn->getBoundingBox().containsPoint(touchPoint))
	{
		if(isSound)
			SimpleAudioEngine::getInstance()->playEffect("jump.wav"); //������Ծ��Ч
		jumpBtn->setTexture(jumpBtnTextures.at(1));
		player->jump();
		jumpTimes++;
	}
		
	return true;
}

void GameScene::onTouchEnded(Touch *touch,Event *event)
{
	auto touchPoint=touch->getLocation();
	//�ж����ͷ�ʱ�Ƿ��ڰ�ť����
	if(slideBtn->getBoundingBox().containsPoint(touchPoint))
	{
		slideBtn->setTexture(slideBtnTextures.at(0));
		player->run();
	}

	if(jumpBtn->getBoundingBox().containsPoint(touchPoint))
	{
		jumpBtn->setTexture(jumpBtnTextures.at(0));
	}

}

void GameScene::update(float dt)
{
	//�ڴ˴�����ײ��⣬���ǰһ��״̬����Ծ����غ��������
	

	//��ֹ��ɫ��Ϊ��ײ������ת
	player->setRotation(0.0f); 
		
	//����ɫ������֮�����ԭ����λ��
	float step=2.0f;
	if(player->getPositionX()<2*BLOCK_SIZE)
		player->setPositionX(player->getPositionX()+step);
	if(player->getPositionX()>2*BLOCK_SIZE)
		player->setPositionX(player->getPositionX()-step);

	//�ж���Ϸ����
	if(player->getPositionY()<=0.0f)
		gameOver();
}

bool GameScene::onContactBegin(const PhysicsContact &contact)
{
	jumpTimes=0; //��ص���ͽ�����Ծ��������

	//��ñ���ײ���壬getShapeA  getShapeBҪ����һ��
	auto target=contact.getShapeA()->getBody()->getNode();
	if(target->getTag()==STAR)
	{
		//�������Ǿ��Ƿ֣�������ʧ
		gameMap->moveNode(target);
		addScore(100); //ʰȡ���ǵ�100
	}
	else if(target->getTag()==NPC&&target->getPositionY()+target->getContentSize().height/2<player->getPositionY()) //�˴�Ҫ��else if,ֻ�е���ɫ�ڹ���ͷ�ϲ��ܲ���
	{
		gameMap->moveNode(target);
		addScore(150); //�ȹֵ�150
	}
	else if(target->getTag()==NPC&&target->getPositionY()+target->getContentSize().height/2>=player->getPositionY()) //�����ɫ������������͹���
		gameOver();
	else if(target->getTag()==TOOL)
	{
		jumpTotal=3;
		auto toolIcon=Sprite::create("accelerate_state.png");
		toolIcon->setPosition(Point(visibleOrigin.x+180,visibleOrigin.y+50));
		this->addChild(toolIcon,2);
		target->removeFromParent(); //����ֻ����һ�Σ���parent����ɾ��
		addScore(300); //����300
	}

	//��ص���ָ��ܲ�״̬
	if(player->playerState==JUMP)
		player->run();

	return true;
}

void GameScene::onEnter()
{
	Layer::onEnter();
	//���볡����������
	if(isSound)
		SimpleAudioEngine::getInstance()->playBackgroundMusic(level==SPRING?"spring_music.wav":"winter_music.mp3",true);
}

void GameScene::onExit()
{
	Layer::onExit();
	//�˳������ر�����
	if(SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}

void GameScene::backGroundUpdate(float dt)
{
	backGround1->setPositionX(backGround1->getPositionX()-1.0f);
	backGround2->setPositionX(backGround1->getPositionX()+backGround1->getContentSize().width);
	if(backGround2->getPositionX()<=0.0f)
		backGround1->setPositionX(0.0f);
}

void GameScene::addScore(float number)
{
	if(isSound)
		SimpleAudioEngine::getInstance()->playEffect("point.mp3"); //���ŵ÷���Ч
	score+=number;
	scoreLabel->setString(String::createWithFormat("score: %d",score)->_string);
}

void GameScene::gameOver()
{
	//��Ϸ����ֹͣ���еĵ�����
	gameMap->unscheduleAllSelectors();
	this->unscheduleAllSelectors();
	//������Ϸ��������
	if(isSound)
		SimpleAudioEngine::getInstance()->playEffect("gameover.wav");

	//��Ϸ�������ֲ˵�
	visibleSize=Director::getInstance()->getVisibleSize();
	visibleOrigin=Director::getInstance()->getVisibleOrigin();
	
	auto gameOverPanel=Node::create();
	auto overLabel=Sprite::create("gameover.png");
	overLabel->setPosition(visibleOrigin.x+visibleSize.width/2,visibleOrigin.y+visibleSize.height/2+100);
	gameOverPanel->addChild(overLabel);

	auto backItem=MenuItemImage::create("back_to_menu.png","back_to_menu_press.png",[](Object *sender)
	{
		//��lambda���ʽ��Ϊ�˵������ص�
		auto mainMenu=MainMenu::createScene();
		TransitionScene *transition=TransitionFade::create(1.0f,mainMenu);
		Director::getInstance()->replaceScene(transition);
	});
	auto backMenu=Menu::createWithItem(backItem);
	backMenu->setPosition(visibleOrigin.x+visibleSize.width/2,visibleOrigin.y+visibleSize.height/2-50);

	gameOverPanel->addChild(backMenu);

	gameOverPanel->setPositionY(visibleOrigin.y+visibleSize.height);
	this->addChild(gameOverPanel,3);
	//����gameover logo��ע��node��ê�������½�
	gameOverPanel->runAction(MoveTo::create(0.5f,Vec2(visibleOrigin.x,visibleOrigin.y)));

}