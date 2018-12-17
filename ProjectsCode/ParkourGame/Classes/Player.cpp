#include "Player.h"


extern PlayerType playerType; //�õ�ȫ�ֱ������洢��Ϸ��ɫ������ȫ���ĳ������ļ�

bool Player::init()
{
	if(!Node::init())
		return false;
	//�����к���Ů��������֡����,ע��˴�Ҫ�����л��������Բ�����AnimationCache
	Animation *girlAnimation=Animation::create();
	for(int i=1;i<=8;i++)
		girlAnimation->addSpriteFrameWithFile("girl"+std::to_string(i)+".png");
	girlAnimation->setDelayPerUnit(0.15f);

	Animation *boyAnimation=Animation::create();
	for(int i=1;i<=12;i++)
		boyAnimation->addSpriteFrameWithFile("boy"+std::to_string(i)+".png");
	boyAnimation->setDelayPerUnit(0.1f);

	//ѡȡ��ͬ��ɫ
	std::string playerTextureName;
	std::string playerJumpTexureName;
	std::string playerSlideTextureName;
	Animation *playerAnimation;

	//�����Ϸ��ɫ������Ů
	switch(playerType)
	{
	case BOY:
		playerTextureName="boy1.png";
		playerJumpTexureName="boy_jump.png";
		playerSlideTextureName="boy_slide.png";
		playerAnimation=boyAnimation;
		break;
	case GIRL:
		playerTextureName="girl1.png";
		playerJumpTexureName="girl_jump.png";
		playerSlideTextureName="girl_slide.png";
		playerAnimation=girlAnimation;
		break;
	}

	

	playerSprite=Sprite::create(playerTextureName); //�˴������ʼ��һ�Ž�ɫ������������޷��л�����
	
	jumpTexture=Sprite::create(playerJumpTexureName)->getTexture(); //������Ծ����
	slideTexture=Sprite::create(playerSlideTextureName)->getTexture(); //������������

	playerAnim=Animate::create(playerAnimation);
	this->addChild(playerSprite);

	auto playerBody=PhysicsBody::createBox(playerSprite->getContentSize()); //����Ҫ�ð�Χ�У������Բ�εĻ��ᵼ�¹���
	playerBody->setDynamic(true);
	playerBody->setContactTestBitmask(1);
	playerBody->setGravityEnable(true);
	playerBody->getShape(0)->setRestitution(0.0f); //���ø���ص���
	this->setPhysicsBody(playerBody);

	playerSprite->runAction(RepeatForever::create(playerAnim)); //��ʼʱ�̽�ɫ�ڱ���
	playerState=RUN;



	return true;
}

void Player::run()
{
	playerState=RUN;
	playerSprite->resume();
}

void Player::jump()
{
	playerState=JUMP;
	
	playerSprite->pause();
	playerSprite->setTexture(jumpTexture); //������Ծ������
	this->getPhysicsBody()->setVelocity(Vec2(0,PLAYER_SPEED));

}

void Player::slide()
{
	playerState=SLIDE;
	playerSprite->pause();
	playerSprite->setTexture(slideTexture); //���û��е�����
}