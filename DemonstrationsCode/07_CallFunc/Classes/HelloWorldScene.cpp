#include "HelloWorldScene.h"
Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}
bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    auto  backgroundSp=Sprite::create("bg.jpg");
    backgroundSp->setPosition(240, 160);
    addChild(backgroundSp,-1);

    mSprite=Sprite::create("grossini.png");
    mSprite->setPosition(40, 180);
    addChild(mSprite);

    fmSprite=Sprite::create("fm.png");
	fmSprite->setPosition(40, 80);
    addChild(fmSprite);

	/*7.5 速度动作——ActionSpeed，既不属于瞬时动作，也不属于延时动作，
		与ActionEase没有任何关系，也不能参与到动作组合中，
		只能独立地被节点对象执行。*/
    auto moveTo=MoveTo::create(10.0f, Vec2(280,80));
    auto speed=Speed::create(moveTo, 2.0f);
   	fmSprite->runAction(speed);

    //MenuItemImage中有回调函数startAction, 
    auto menuItem=MenuItemImage::create("btn-play-normal.png", "btn-highscores-selected.png",CC_CALLBACK_1(HelloWorld::startAction, this));
    menuItem->setPosition(400,50);
    auto menu=Menu::create(menuItem, NULL);
    menu->setPosition(Vec2::ZERO);//Vec2::ZERO相当于Vec2（0，0）
    addChild(menu);
	
	//7.2.2 测试基本动作：旋转RotateTo和RotateBy
	auto RToAction1=RotateTo::create(2.0f,90);//顺时针旋转90度
	auto RToAction2=RotateTo::create(2.0f,270);//逆时针旋转90度
	//fmSprite->runAction(RToAction1);
	//fmSprite->runAction(RToAction2);
	auto RByAction=RotateBy::create(2.0f,360);
	//fmSprite->runAction(RByAction);

	//7.2.2 测试基本动作：跳跃JumpTo和JumpBy
	auto jumpTo=JumpTo::create(2.0f,Vec2(420,300),22,10);
	auto jumpBy=JumpBy::create(2.0f,Vec2(100,100),10,10);
	fmSprite->runAction(jumpBy);
	//乒乓球跳跃
	auto BallSprite=Sprite::create("ball.png");
	BallSprite->setPosition(40, 280);
    addChild(BallSprite);
	BallSprite->runAction(jumpBy);

	//7.2.1 测试瞬时动作FlipX,纵向翻转
    ActionInstant *action=NULL;
    action=FlipX::create(true);
    //mSprite->runAction(action);
	//7.2.2（8）测试延时动作视觉特效动作—FadeIn、Blink与FadeOute
	auto fadein=FadeIn::create(3);
	auto fadeout=FadeOut::create(3);
	
	//7.2.21 瞬时动作 Show、Hid
	auto show=Show::create();
	auto hide=Hide::create();
	//7.2.2 (12)延时动作Blink
    auto blink=Blink::create(2.0f,5);

	//7.2.2 延时动作MoveBy 	
    auto ac1=MoveBy::create(2, Vec2(200,0));
	//反动作reverse
	auto ac1_reverse=ac1->reverse();
	
	//7.3测试组合动作—Sequence、RepeatForever
	auto seq=Sequence::create(fadein,blink,ac1,ac1_reverse,hide,show,fadeout,NULL);
	mSprite->runAction(RepeatForever::create(seq));
	
	//7.2.2测试色彩渐变动作—TintBy
	auto apple = Sprite::create("apple.png");
	apple->setPosition(Vec2(300,280));
	//apple->setScale(.5);
	this->addChild(apple);
	auto tintBy=TintBy::create(5,0,-100,-100);//时间和RGB三原色值
	apple->runAction(tintBy);
	//7.3测试组合动作—Spawn
	auto ac2=MoveBy::create(5, Vec2(50,50));
	auto scaleto=ScaleTo::create(5,1.5);
	auto spawn=Spawn::create(ac2,scaleto,NULL);//记得添加NULL，否则会出现，位置错误
	auto sprite3=Sprite::create("bird.png");
	sprite3->setPosition(Vec2(50,150));
	this->addChild(sprite3);
	sprite3->runAction(spawn);

	// 7.6 测试跟随动作，static Follow* create(Node *followedNode, const Rect& rect = Rect::ZERO);
      //auto ac3=Follow::create(mSprite);
      //this->runAction(ac3);

	//7.2.2 贝塞尔曲线BezierTo和BezierBy

	auto sprite4=Sprite::create("bird_22.png");
	sprite4->setPosition(Vec2(20,100));
	sprite4->setScale(.3);
	this->addChild(sprite4);
	ccBezierConfig  beziercf;
	beziercf.controlPoint_1=Vec2(100,0);
	beziercf.controlPoint_1=Vec2(200,300);
	beziercf.endPosition=Vec2(300,100);
	auto bezierTo=BezierTo::create(2.0f,beziercf);
	sprite4->runAction(bezierTo);
	
	//7.2.2ProgressTimer 进度条 BAR和ProgressTo
	
    auto grass=Sprite::create("grass.png");
    auto grossTimer1=ProgressTimer::create(grass);
    grossTimer1->setPosition(240, 300);
    grossTimer1->setType(ProgressTimer::Type::BAR);
    // grossTimer->setMidpoint(Vec2(0,0.5));//从左往右往下
    grossTimer1->setMidpoint(Vec2(0,0));//从右往左往下
    grossTimer1->setPercentage(0);
    grossTimer1->setTag(10);
    this->addChild(grossTimer1);
    //7.2.2ProgressTimer RADIAL 半径展开和ProgressTo
    auto scrollgrass=Sprite::create("scrollgrass.png");
    auto grossTimer2=ProgressTimer::create(scrollgrass);
    grossTimer2->setPosition(240, 100);
   // grossTimer2->setType(ProgressTimer::Type::RADIAL);
	grossTimer1->setType(ProgressTimerType::RADIAL);
    grossTimer2->setMidpoint(Vec2(0.5,0.5));//从中心铺成圆形
   // grossTimer2->setTag(10);
    this->addChild(grossTimer2);

    auto Pt =ProgressTo::create(8.0f,100);//创建进度条
	grossTimer2->runAction(Pt);
 
	//GridBase动作
	//sprite3->runAction(PageTurn3D::create(3.0,Size(20,20)));

    //2.7.4 缓冲动作
    //ease in 先慢后快，easeout 先快后慢，EaseInOut先慢后快，再到慢
    auto rotateBy=RotateBy::create(2.0,180);
    auto EinAction=EaseInOut::create(rotateBy, 5.0f);
    //指数缓冲动作
    auto ExInAction=EaseExponentialIn::create(rotateBy);//先慢后快
    auto easeExponentialaction=EaseExponentialInOut::create(moveTo);//先慢后快，再到慢
    mSprite->runAction(action);
    
    //跳跃缓冲动作
     auto  easeBounce=EaseBounceIn::create(moveTo);
     auto easeElastic=EaseElasticIn::create(moveTo);

	//7.7 测试 延迟动作——ActionDelay
	    // 定义一个MoveTo动作，2秒内从当前位置移出屏幕
    auto plane = Sprite::create("plane.png");
	plane->setPosition(Vec2(50,50));
	plane->setScale(.5);
	this->addChild(plane);
	auto move = MoveTo::create(2, Vec2(500, 350));
    // 定义一个DelayTime动作，执行该动作时将产生5秒延迟
    auto delay = DelayTime::create(5);
    // 定义一个Sequence动作，先执行DelayTime延迟动作，再执行MoveTo移动动作
    auto sequence = Sequence::create(delay,move, NULL);
    // 精灵（飞机）执行Sequence动作
    plane->runAction(sequence);

	return  true;
}

void HelloWorld::startAction(Ref *render)
{
    //7.2.2 延时动作MoveTo
	auto action=MoveTo::create(2.0f, Vec2(400,300));
   
     /*瞬时动作CallFunc—   可以通过函数回调生成一个动作 
	 static CallFunc * create(const std::function<void()>& func);
     creates the action with the callback of type std::function<void()>.
     This is the preferred way to create the callback.
     回调的函数CC_CALLBACK_0 回调的函数没有要求有参数，
	 回调的函数CC_CALLBACK_1后至少要接1个固定参数，可以用Ref *render作为固定参数，
     回调的函数CC_CALLBACK_2后至少要接2个固定参数，
     如果参数是CC_CALLBACK_1必须用CallFuncN，
	 如果参数是CC_CALLBACK_2必须用CallFuncND，
	 如果参数是CC_CALLBACK_0，则可以用CallFunc，也可以用CC_CALLBACK_1，还可以用CC_CALLBACK_2.
    */
	/*7.2.1（4）回调函数动作—CallFuncN 回调函数callback0
	定义了一个CallFuncN动作，调用callback0函数，第三个参数是传递给callback0函数的参数（mSprite精灵）,
	无需传递时，第三个参数可以省略不写。
	 */
	auto callFunc=CallFuncN::create(CC_CALLBACK_0(HelloWorld::callback,this,mSprite));
	auto seq =Sequence::create(action,callFunc,NULL);
    mSprite->runAction(seq);


    //动作管理——stopAllActions、ActionManager 和pauseTarget
    //mSprite->stopAllActions();
    //this->stopAllActions();
	//auto manager=Director::getInstance()->getActionManager();
	//manager->pauseTarget(mSprite);     
}
//瞬时动作CallFunc执行完毕后的回调该函数，以及瞬时动作Place
void HelloWorld::callback(Ref *render)
{
    log("其它动作执行完毕");
	auto place=Place::create(Vec2(240,160));
	// 参数对象sender执行Place动作，sender就是传递进来的Node对象（mSprite精灵）
	mSprite->runAction(place);
	//mSprite->setPosition(Vec2(240,160));
}

//绘制贝塞尔曲线的渲染命令
void  HelloWorld::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
    command.init(_globalZOrder);
    command.func=CC_CALLBACK_0(HelloWorld::onDraw, this);
    renderer->addCommand(&command);
}

void HelloWorld::onDraw( )
{
    glLineWidth(5.0f);
    DrawPrimitives::setDrawColor4B(255, 0, 255, 255);
    DrawPrimitives::drawCubicBezier(Vec2(20,100),Vec2(100,0),Vec2(200,300),Vec2(300,100),50);

}