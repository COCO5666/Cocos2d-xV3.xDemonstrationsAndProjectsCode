#include "StatusLayer.h"


StatusLayer::StatusLayer(){};

StatusLayer::~StatusLayer(){};


bool StatusLayer::init(){
	if(!Layer::init()){
		return false;
	}
	// init numbers
    this->bestScore = 0;
    this->currentScore = 0;
	this->isNewRecord = false;
	this->visibleSize = Director::getInstance()->getVisibleSize();
	this->originPoint = Director::getInstance()->getVisibleOrigin();
	this->showReadyStatus();
	this->loadWhiteSprite();
	return true;
}

void StatusLayer::showReadyStatus() {
	scoreSprite = ui::TextAtlas::create("0", "num.png",30, 44,"0");
	scoreSprite->setPosition(Point(this->originPoint.x + this->visibleSize.width / 2,this->originPoint.y + this->visibleSize.height *5/6));
	this->addChild(scoreSprite);

	getreadySprite = Sprite::createWithSpriteFrameName("text_ready.png");
	getreadySprite->setPosition(Point(this->originPoint.x + this->visibleSize.width / 2, this->originPoint.y + this->visibleSize.height *2/3));
	this->addChild(getreadySprite);

	tutorialSprite = Sprite::createWithSpriteFrameName("tutorial.png");
	tutorialSprite->setPosition(Point(this->originPoint.x + this->visibleSize.width / 2, this->originPoint.y + this->visibleSize.height * 1/2));
	this->addChild(tutorialSprite);
}

void StatusLayer::showStartStatus() {
	this->getreadySprite->runAction(FadeOut::create(0.4f));
	this->tutorialSprite->runAction(FadeOut::create(0.4f));
}

void StatusLayer::showOverStatus(int curScore, int bestScore) {
    this->currentScore = curScore;
    this->bestScore = bestScore;
    if(curScore > bestScore){
		this->bestScore = curScore;
		this->isNewRecord = true;
	}else{
		this->isNewRecord = false;
	}
	this->removeChild(scoreSprite);
	this->blinkFullScreen();
}

void StatusLayer::onGameStart(){
	this->showStartStatus();
}

void StatusLayer::onGamePlaying(int score){
	auto scorestr = __String::createWithFormat("%d", score)->getCString();
	scoreSprite->setString(scorestr);
}

void StatusLayer::onGameEnd(int curScore, int bestScore){
	this->showOverStatus(curScore,bestScore);
}

void StatusLayer::loadWhiteSprite(){
	//this white sprite is used for blinking the screen for a short while
	whiteSprite = Sprite::createWithSpriteFrameName("white.png");
	whiteSprite->setScale(100);
	whiteSprite->setOpacity(0);
	this->addChild(whiteSprite,10000);
}

void StatusLayer::blinkFullScreen(){
	//display a flash blink
	auto fadeOut = FadeOut::create(0.1f);
	auto fadeIn = FadeIn::create(0.1f);
	auto blinkAction = Sequence::create(fadeIn,fadeOut,NULL);
    CallFunc *actionDone = CallFunc::create(bind(&StatusLayer::fadeInGameOver, this));
    auto sequence = Sequence::createWithTwoActions(blinkAction, actionDone);
    whiteSprite->stopAllActions();
	whiteSprite->runAction(sequence);
}

void StatusLayer::fadeInGameOver(){    
    // create the game over panel
	Sprite* gameoverSprite = Sprite::createWithSpriteFrameName("text_game_over.png");
	gameoverSprite->setPosition(Point(this->originPoint.x + this->visibleSize.width / 2, this->originPoint.y + this->visibleSize.height *2/3));
	this->addChild(gameoverSprite);
	auto gameoverFadeIn = FadeIn::create(0.5f);
    
    // Start next action
	CallFunc *actionDone = CallFunc::create(bind(&StatusLayer::jumpToScorePanel, this));
    auto sequence = Sequence::createWithTwoActions(gameoverFadeIn, actionDone);
    gameoverSprite->stopAllActions();
	gameoverSprite->runAction(sequence);
}

void StatusLayer::jumpToScorePanel(){    
    // create the score panel
    Sprite* scorepanelSprite = Sprite::createWithSpriteFrameName("score_panel.png");
	scorepanelSprite->setPosition(Point(this->originPoint.x + this->visibleSize.width / 2, this->originPoint.y - scorepanelSprite->getContentSize().height));
	this->addChild(scorepanelSprite);
        
	//display the  best score on the score panel
	auto bestscoreStr = __String::createWithFormat("%d", this->bestScore)->getCString();
	auto bestScoreSprite = ui::TextAtlas::create(bestscoreStr, "score.png", 20, 20, "0");
	bestScoreSprite->setAnchorPoint(Point(1, 1));
	bestScoreSprite->setPosition(Vec2(scorepanelSprite->getContentSize().width - 28 ,50));
	scorepanelSprite->addChild(bestScoreSprite);
    
    
	string medalsName = this->getMedalsName(currentScore);
	if(medalsName != "") {
		Sprite* medalsSprite = Sprite::createWithSpriteFrameName(medalsName);
		medalsSprite->addChild(this->blink);
		medalsSprite->setPosition(54, 58);
		scorepanelSprite->addChild(medalsSprite);
	}
    
	//if the current score is higher than the best score.
	//the panel will appear a "new" tag.
	if(this->isNewRecord){
		Sprite* newTagSprite = Sprite::createWithSpriteFrameName("new.png");
		newTagSprite->setPosition(-16, 12);
		bestScoreSprite->addChild(newTagSprite);
	}
	
    // Start next action
	auto scorePanelMoveTo = MoveTo::create(0.8f ,Point(this->originPoint.x + this->visibleSize.width / 2,this->originPoint.y + this->visibleSize.height/2 - 10.0f));
	// add variable motion for the action
	EaseExponentialOut* sineIn = EaseExponentialOut::create(scorePanelMoveTo);
	CallFunc *actionDone = CallFunc::create(bind(&StatusLayer::fadeInRestartBtn, this));
    auto sequence = Sequence::createWithTwoActions(sineIn, actionDone);
    scorepanelSprite->stopAllActions();
	SimpleAudioEngine::getInstance()->playEffect("sfx_swooshing.mp3");
	scorepanelSprite->runAction(sequence);
}

void StatusLayer::fadeInRestartBtn(){
	Node * tmpNode = Node::create();
    
	//create the restart menu;
	Sprite* restartBtn = Sprite::createWithSpriteFrameName("button_play.png");
	Sprite* restartBtnActive = Sprite::createWithSpriteFrameName("button_play.png");
	restartBtnActive->setPositionY(-4);
	auto  menuItem = MenuItemSprite::create(restartBtn,restartBtnActive,NULL,CC_CALLBACK_1(StatusLayer::menuRestartCallback,this));
    auto menu = Menu::create(menuItem,NULL);
	menu->setPosition(Point(this->originPoint.x + this->visibleSize.width / 2 - restartBtn->getContentSize().width / 2, this->originPoint.y + this->visibleSize.height * 2 / 7 - 10.0f));
	tmpNode->addChild(menu);
    
    
	//create the rate button. however ,this button is not available yet = =
	Sprite* rateBtn = Sprite::createWithSpriteFrameName("button_score.png");
	rateBtn->setPosition(Point(this->originPoint.x + this->visibleSize.width / 2 + rateBtn->getContentSize().width / 2, this->originPoint.y + this->visibleSize.height * 2 / 7 - 10.0f));
	tmpNode->addChild(rateBtn);
	this->addChild(tmpNode);
    
	//fade in the two buttons
	auto fadeIn = FadeIn::create(0.1f);
    //tmpNode->stopAllActions();
	//tmpNode->runAction(fadeIn);

	CallFunc *actionDone = CallFunc::create(bind(&StatusLayer::refreshScoreCallback,this));
	auto sequence = Sequence::createWithTwoActions(fadeIn,actionDone);
	tmpNode->stopAllActions();
	tmpNode->runAction(sequence);
}

void StatusLayer::refreshScoreCallback(){
	this->tmpScore = 0;
	schedule(schedule_selector(StatusLayer::refreshScoreExecutor),0.1f);
}

void StatusLayer::refreshScoreExecutor(float dt){
	if(this->getChildByTag(CURRENT_SCORE_SPRITE_TAG)){
		this->removeChildByTag(CURRENT_SCORE_SPRITE_TAG);
	}
	auto tmpscoreStr = __String::createWithFormat("%d", this->tmpScore)->getCString();
	auto scoreSprite = ui::TextAtlas::create(tmpscoreStr, "score.png", 20, 20, "0");
	scoreSprite->setAnchorPoint(Point(1,0));
	scoreSprite->setPosition(Point(this->originPoint.x + this->visibleSize.width * 3 / 4 + 20.0f, this->originPoint.y + this->visibleSize.height *  1 / 2));
	scoreSprite->setTag(CURRENT_SCORE_SPRITE_TAG);
	this->addChild(scoreSprite,1000);
	this->tmpScore++;
	if(this->tmpScore > this->currentScore){
		unschedule(schedule_selector(StatusLayer::refreshScoreExecutor));
	}
}

void StatusLayer::setBlinkSprite() {
	this->blink = Sprite::createWithSpriteFrameName("blink_00.png");
	Animation *animation = Animation::create();
    animation->setDelayPerUnit(0.1f);
	for (int i = 0; i < 3; i++){
		const char *filename = String::createWithFormat("blink_%02d.png", i)->getCString();
		SpriteFrame *frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(filename);
		animation->addSpriteFrame(frame);
	}
	for (int i = 2; i >= 0; i--){
		const char *filename = String::createWithFormat("blink_%02d.png", i)->getCString();
		SpriteFrame *frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(filename);
		animation->addSpriteFrame(frame);
	}
	auto animate = Animate::create(animation);
	auto actionDone = CallFunc::create(bind(&StatusLayer::blinkAction,this));
	auto sequence = Sequence::createWithTwoActions(animate, actionDone);
	blink->runAction(RepeatForever::create(sequence));
}

void StatusLayer::blinkAction() {
	if(this->blink && this->blink->getParent()) {
		Size activeSize = this->blink->getParent()->getContentSize();
		this->blink->setPosition(rand()%((int)(activeSize.width)), rand()%((int)(activeSize.height)));
	}
}

string StatusLayer::getMedalsName(int score){
	this->setBlinkSprite();

	//display the golden silver or bronze iron
	string medalsName = "";
	if(this->currentScore >=10 && this->currentScore < 20){//iron medals
		medalsName = "medals_0.png";
	}else if(this->currentScore >= 20 && currentScore < 30){//bronze medals
		medalsName = "medals_1.png";
	}else if(currentScore >=30 && currentScore < 50){//silver medals
		medalsName = "medals_2.png";
	}else if(currentScore >=50){//golden medals
		medalsName = "medals_3.png";
	}
	return medalsName;
}

void StatusLayer::menuRestartCallback(Object* pSender){
	SimpleAudioEngine::getInstance()->playEffect("sfx_swooshing.mp3");
    auto scene = GameScene::create();
    TransitionScene *transition = TransitionFade::create(1, scene);
    Director::getInstance()->replaceScene(transition);
}