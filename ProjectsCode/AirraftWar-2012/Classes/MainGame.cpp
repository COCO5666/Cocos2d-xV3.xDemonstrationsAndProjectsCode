#include "MainGame.h"
USING_NS_CC;

#include <iostream>
using namespace std;

#include <SimpleAudioEngine.h>
using namespace CocosDenshion;

#include "ManagerBase.h"
#include "Suspand_Layer.h"
#include "Bullet.h"
#include "GameOver.h"
#include "PlaneSupport.h"

#include <ui/CocosGUI.h>
using namespace ui;


Scene * MainGame::createScene()
{
    auto scene=Scene::create();
    auto layer=MainGame::create();
    scene->addChild(layer);
    return scene;
}

//一.初始化游戏界面，添加背景、当前得分、最高得分、暂停按钮和单点触摸事件
bool MainGame::init()
{
    plane_support_= NULL;
    score_=0;
    
    if (!Layer::init())
    {
        return false;
    }
    /*
     1.用同一张背景图片创建2个精灵，bg1在下面，bg2在上面，让他们在高度上重叠2像素堆叠
     添加背景图像的连续滚动效果思路：第一张最初显示在屏幕上，第二张背景图在第一张下面，每一帧让两张背景图一起滚动；当背景图的y轴等于负getContentSize（）.height的时候，即背景图移出屏幕一个位置的时候，将背景图重新设置到屏幕上，两张背景图片循环滚动，从而达到背景滚动的效果。
     */
    Size size=Director::getInstance()->getWinSize();
    bg1=Sprite::create("bg.png");
    bg1->setAnchorPoint(Vec2(0,0));
    bg1->setPosition(Vec2(0,0));
    //setAliasTexParameters(),Calling this method could allocate additional texture memory.用于解决拼接的地图在连接滚动时容易形成黑色缝隙的问题
    //bg1->getTexture()->setAliasTexParameters();

    this->addChild(bg1);
   
    bg2=Sprite::create("bg.png");
    bg2->setAnchorPoint(Vec2(0,0));
    bg2->setPosition(Vec2(0,bg1->getContentSize().height-2));
    //bg2->getTexture()->setAliasTexParameters();
    this->addChild(bg2);
   
    
    //2.在屏幕右上角加暂停按钮suspend
    auto dictionary=Dictionary::createWithContentsOfFile("text.xml");
    auto suspendStr = ((__String *)(dictionary->objectForKey("suspend")))->getCString();
    auto btn_label=Label::createWithTTF(suspendStr,"han1.ttf", 20);
    auto start_menu=MenuItemLabel::create(btn_label, CC_CALLBACK_1(MainGame::suspend, this));
    auto menu =Menu::create(start_menu, NULL);
    menu->setPosition(Vec2(size.width-btn_label->getContentSize().width/2 -10,size.height-btn_label->getContentSize().height/2 -10));
    addChild(menu);
    
   //3.加当前得分score标签
	auto scoreStr=((__String*)(dictionary->objectForKey("score")))->getCString();
	auto label_score=Label::createWithTTF(scoreStr, "han1.ttf", 20);
	label_score->setAnchorPoint(Vec2(0.5,0.5));
	label_score->setPosition(Vec2(label_score->getContentSize().width/2 + 10,size.height-label_score->getContentSize().height/2 - 10));
	addChild(label_score);
	/*auto scoreStr = ((__String*)(dictionary->objectForKey("score")))->getCString();
	auto label_score = Label::createWithTTF(scoreStr, "han1.ttf", 20);
	label_score->setAnchorPoint(Vec2(0.5, 0.5));
	label_score->setPosition(Vec2(label_score->getContentSize().width/2+10, size.height-label_score))*/
    
    //4.添加当前所得具体分数score_num
    label_score_num_=Label::create();
    label_score_num_->setSystemFontSize(20);
    label_score_num_->setAnchorPoint(Vec2(0,0.5));
    label_score_num_->setPosition(Vec2(label_score->getContentSize().width+20,label_score->getPositionY()));
    label_score_num_->setColor(cocos2d::Color3B(255,0,0));
     //设置分数值，初始值为0
    label_score_num_->setString(String::createWithFormat("%d",score_)->getCString());
    addChild(label_score_num_);
    
    //5.添加best_score最高分标签
    auto bestScoreStr = ((__String *)(dictionary->objectForKey("best_score")))->getCString();
    auto label_best_score=Label::createWithTTF(bestScoreStr, "han1.ttf", 20);
    label_best_score->setAnchorPoint(Vec2(0.5,0.5));
    label_best_score->setPosition(Vec2(label_best_score->getContentSize().width/2+10,label_score->getPositionY()-label_best_score->getContentSize().height-10));
    this->addChild(label_best_score);
    
    //6.添加最高分
    label_best_score_num_=Label::create();
    label_best_score_num_->setSystemFontSize(20);
    label_best_score_num_->setColor(cocos2d::Color3B(255,0,0));
    label_best_score_num_->setAnchorPoint(Vec2(0,0.5));
    label_best_score_num_->setPosition(Vec2(label_best_score->getContentSize().width+20,label_best_score->getPositionY()));
    addChild(label_best_score_num_);
    //设置最高分，初始值默认为0
    int score_win=UserDefault::getInstance()->getIntegerForKey("best_score");
    label_best_score_num_->setString(String::createWithFormat("%d",score_win)->getCString());
    //7.单点触摸事件及其回调函数
    auto  m_touchDispatcher= Director::getInstance()->getEventDispatcher();
    auto *m_touchListener=EventListenerTouchOneByOne::create();
    m_touchListener->onTouchBegan = CC_CALLBACK_2(MainGame::onTouchBegan, this);
    m_touchListener->onTouchMoved = CC_CALLBACK_2(MainGame::onTouchMoved, this);
    m_touchListener->setSwallowTouches(true);
    m_touchDispatcher->addEventListenerWithSceneGraphPriority(m_touchListener, this);
    //8.添加战斗机,这里先初始化一个定义好的战斗机，等选飞机的三个类（SelectPlanePage、SelectPlane——Scene、SelectPlane——Layer）创建好了之后就注掉
   // init_hero_plane(2);
       return true;
}

/*
 1.scheduleUpdate：通过this->scheduleUpdate（）把定时器加到节点后，节点会每帧都会调用虚函数：update（void）；取消方法：this->unscheduleUpdate(); 只能触发虚函数 update()
 2.schedule：定义是 void CCNode::schedule(SEL_SCHEDULE selector, float interval, unsigned int repeat, float delay)；
  通过this->schedule(SEL_SCHEDULE selector, float interval, unsigned int repeat, float delay) 把定时器加到节点，可以指定回调函数、触发间隔、重复次数、延迟启动时间，第二个参数（触发间隔）为0则表示每帧都触发，相当于scheduleUpdate，但优势在于可以自己指定回调方法；取消方法：this->unschedule(SEL_SCHEDULE selector);
 3.cheduleOnce: 定义是 void CCNode::scheduleOnce(SEL_SCHEDULE selector, float delay)
  this->scheduleOnce(selector, delay) 把定时器加到节点，指定回调函数和延迟启动时间，只会触发一次。取消方法：this->unscheduleOnce(selector)；
 */

//二、设置背景的移动效果；update函数是游戏的主循环，作用是每一帧修改背景图片精灵的坐标，从而达到视觉上背景滚动效果。其实任何一款游戏都包括一个主循环，用来更新游戏的状态、玩家和敌人的数量、碰撞的逻辑等。这里的只更新背景图片实习滚动效果。
void MainGame::update(float f )
{
    //让两张背景图片每帧下落3像素，数值越大，背景下落的越快。
    float y1=bg1->getPositionY()-3;
    float y2=bg2->getPositionY()-3;
    bg1->setPositionY(y1);
    bg2->setPositionY(y2);
    
    if (y1< -bg1->getContentSize().height)
    {
      bg1->setPositionY(bg2->getPositionY()+bg2->getContentSize().height-2);
      // bg1->setPositionY(bg1->getContentSize().height);
    }
    else if(y2< -bg2->getContentSize().height)
    {
      bg2->setPositionY(bg1->getPositionY()+bg1->getContentSize().height-2);
        /*
         bg2->setPositionY(bg1->getContentSize().height-2);
         如果不加bg1->getPositionY()，会导致两张图片在一次循环后之间出现缝隙，如果游戏运行卡，则会更明显
         */
       // bg2->setPositionY(bg2->getContentSize().height);//书上存在问题
    }
    
}
//三、增加敌机
void MainGame::add_enemy(float delta)
{
    //0-9之间的随机数再加1，意即生成1-10之间的随机数
     enemy_type_=rand_0_1()*9+1;
    // 用随机数选择敌机的类型，总共2种类型的敌机，当随机数为1-5时显示敌机类型为1，当随机数为6-10时显示敌机类型为2.
    if (enemy_type_>6)
    {
        enemy_type_=2;
    }
    else
    {
        enemy_type_=1;
    }
    auto enemy=EnemyBase::create(); //创建一个敌机对象
    enemy->initEnemy(enemy_type_);
    enemy->_type = enemy_type_;
    //该对象调用EnemyBase类的函数initEnemy()，传入的参数是敌机的类型enemy_x
    this->addChild(enemy);
    
    //音效1：添加敌机出现的音效
    SimpleAudioEngine::getInstance()->playEffect("enemy_out.mp3");
    ManagerBase::getInstance()->set_enemy_list(enemy);
}

//四、初始化战斗机
void MainGame::init_hero_plane(int planeType)
{
    plane_type_=planeType;
    auto animation=Animation::create();
    for (int i=0; i<2; i++)
    {
        auto str_name=String::createWithFormat("heros%d_%d.png",plane_type_,i+1);
        animation->addSpriteFrameWithFile(str_name->getCString());
    }
    animation->setDelayPerUnit(0.5);
    animation->setLoops(-1);
    hero_player_=Sprite::create(String::createWithFormat("heros%d_1.png",plane_type_)->getCString());
    auto size=Director::getInstance()->getWinSize();
    hero_player_->setPosition(Vec2(size.width/2,size.height*0.1));
    hero_player_->setScale(0.7);
    this->addChild(hero_player_);
    hero_player_->runAction(Animate::create(animation));
}

//五、触摸开始时，获取战斗机缩放后的大小，并判断手指点击的点是否点在了战斗机精灵上
bool MainGame::onTouchBegan(Touch *touch, Event *unused_event)
{
    auto point=touch->getLocation();
    auto rect=hero_player_->getBoundingBox();
    if (rect.containsPoint(point))
    {
        return true;
    }
    return false;
}

//六、单点触摸屏幕来移动战斗机
void MainGame::onTouchMoved(Touch *touch, Event *unused_event)
{
     Size size=Director::getInstance()->getWinSize();
    //触摸点的位置减去前一次触摸点的位置为战斗机移动的距离
    //getPreviousLocation()上一次触摸点的位置
    auto add_point = touch->getLocation()- touch->getPreviousLocation();
    hero_player_->setPosition(hero_player_->getPosition()+add_point);
    auto hero_size=hero_player_->getContentSize();
    //这里的20基本上是小飞机宽度的一半，为了让战斗机左右移动时发出的子弹能打中小飞机
    if (hero_player_->getPositionX()< hero_size.width/2-20)
    {
        hero_player_->setPositionX(hero_size.width/2-20);
    }
    else if (hero_player_->getPositionX()>size.width - hero_size.width/2 + 20 )
    {
        hero_player_->setPositionX(size.width - hero_size.width/2 + 20);
    }
    if (hero_player_->getPositionY()>size.height-hero_size.height/2)
    {
        hero_player_->setPositionY(size.height-hero_size.height/2);
    }
    else if(hero_player_->getPositionY()< hero_size.height/2)
    {
        hero_player_->setPositionY(hero_size.height/2);
    }
    
}

//七、战斗机死亡
void MainGame::hero_death(int planetype)
{
    //把当前所得分数保存到 UserDefault这个单例文件中
    //UserDefault::getInstance()->setIntegerForKey("score", score_);
	UserDefault::getInstance()->setIntegerForKey("score", score_);
    //从UserDefault单例文件中取出最高分
    //int score_win=UserDefault::getInstance()->getIntegerForKey("best_score");
	int score_win = UserDefault::getInstance()->getIntegerForKey("best_score");

    //如果所得分数大于先前存储在UserDefault中的最高分数，则将当前得分设置为最高分
    /*if (score_ > score_win)
    {
        UserDefault::getInstance()->setIntegerForKey("best_score", score_);
    }*/
	if (score_>score_win)
	{
		UserDefault::getInstance()->setIntegerForKey("best_score", score_);
	}
	
    //hero_player_->stopAllActions();
    this->unschedule(SEL_SCHEDULE(&MainGame::is_crash));
    
    //战斗机死亡的动画
    auto animation = Animation::create();
    for (int i= 1; i<=4; i++)
    {
        __String  *srt_name;
        
        if (plane_type_==1)
        {
          srt_name=String::createWithFormat("hero1_blowup_n%d.png",i);;
        }
        else if (plane_type_==2)
        {
          srt_name=String::createWithFormat("hero2_blowup_n%d.png",i);
        }
        else if (plane_type_==3)
        {
          srt_name=String::createWithFormat("hero3_blowup_n%d.png",i);
        }
        animation->addSpriteFrameWithFile(srt_name->getCString());
    }
    animation->setDelayPerUnit(0.1f);
    animation->setLoops(1);
    
    //战斗机死亡动画完成后，马上调用战斗机死亡动作完成的函数hero_player_action_end()，
    hero_player_->runAction(Sequence::create(Animate::create(animation),CallFunc::create(CC_CALLBACK_0(MainGame::hero_player_action_end, this)), NULL));
}

//八、若战斗机死亡，让游戏结束
void MainGame::hero_player_action_end()
{
    //停止增加敌机，并且切换场景到游戏结束
    this->unschedule(SEL_SCHEDULE(& MainGame::add_enemy));
    Director::getInstance()->replaceScene(TransitionFadeTR::create(1.0f, GameOver::createScene()));
}

//九、根据英雄机的类型增加不同的子弹
void MainGame::add_bullet(float tm)
{
    auto bullet=Bullet::create();
    /*
     调用Bullet类创建一个对象，让该对象调用Bullet类的初始化函数initBullet，根据战斗机的类型决定子弹的类型
     */
    if (plane_type_==2)
    {
        bullet->initBullet("bullet2.png");
    }
    else if (plane_type_==3)
    {
        bullet->initBullet("bullet3.png");
    }
    else
    {
        bullet->initBullet("bullet1.png");
    }
    Point  point=Vec2(hero_player_->getPositionX(),hero_player_->getPositionY() + hero_player_->getContentSize().height / 2 + 10);
    //让子弹在飞机顶端中部位置发出
    bullet->setPosition(point);
    this->addChild(bullet);
    
    //音效2：添加子弹出现的声音
    SimpleAudioEngine::getInstance()->playEffect("bullet.mp3");
    ManagerBase::getInstance()->set_bullet_list(bullet);
}

//十、暂停处理函数
void MainGame::suspend(Ref *sender)
{
	unscheduleUpdate();
	TextureCache::getInstance()->removeUnusedTextures();
	Size size = Director::getInstance()->getWinSize();
	//相当于截取暂停这一刹那的游戏界面图，并把它保存成suspend.png
	auto texture = RenderTexture::create(size.width, size.height);
	texture->begin();
	Director::getInstance()->getRunningScene()->visit();
	texture->end();
	texture->saveToFile("suspend.png", Image::Format::PNG);
    
    auto back=[](float dt)
    {
        auto scene=Scene::create();
        auto layer=Suspand_Layer::create();
        scene->addChild(layer);
        Director::getInstance()->pushScene(scene);
    };
    auto layer=Layer::create();
    addChild(layer);
    auto schedules=layer->getScheduler();//获取调度对象

    // schedule
  
    /**   
     void Scheduler::schedule(const ccSchedulerFunc& callback, void *target, float interval, bool paused, const std::string& key)
    {
        this->schedule(callback, target, interval, CC_REPEAT_FOREVER, 0.0f, paused, key);
    }
     The scheduled method will be called every 'interval' seconds.
     If paused is true, then it won't be called until it is resumed.
     If 'interval' is 0, it will be called every frame, but if so, it's recommended to use 'scheduleUpdate' instead.
     If the 'callback' is already scheduled, then only the interval parameter will be updated without re-scheduling it again.
     repeat let the action be repeated repeat + 1 times, use CC_REPEAT_FOREVER to let the action run continuously
     delay is the amount of time the action will wait before it'll start
     @param key The key to identify the callback
     @since v3.0
     */
  
    schedules->schedule(back,layer, 0.0f, 0, 0.0f, false, "screenshot");
    
    //完全可以不用创建suspand_Layer类，也不用生成游戏截图，只需用下面的代码，让director单例调用封装好的resume、paused等函数，就可实现同样的效果。
//    if (Director::getInstance()->isPaused())
//    {
//        Director::getInstance()->resume();
//    }
//    else
//    {
//       Director::getInstance()->pause();
//    }
}

//十一、过渡切换效果完成时执行定时器函数
void MainGame::onEnterTransitionDidFinish()
{
    Layer::onEnterTransitionDidFinish();
     scheduleUpdate();//每帧更新一次，
    log("onEnterTransitionDidFinish");
    /*更新屏幕，每0.3秒增加一个敌人，每0.09秒增加一个子弹，每一帧判断一次是否有碰撞发生，每0.09秒增加一个支援物品，即降落伞*/
    this->schedule(schedule_selector(MainGame::add_enemy), 1.0f);
    this->schedule(schedule_selector(MainGame::add_bullet), 0.05f);
    this->schedule(schedule_selector(MainGame::add_support), 9.0f);  
    this->schedule(schedule_selector(MainGame::is_crash)); //crash中改变子弹的类型
}

//十二、增加支援物品降落伞
void MainGame::add_support(float tm)
{
  	//生成飞机对象
	plane_support_ = PlaneSupport::create();
	// 生成1-3之间的随机数，用来设置供给物品---降落伞的种类
	int index = rand_0_1() * 2 + 1;
	support_index_ = index;//用来设置子弹的种类
	plane_support_->init_support(index);//用index初始化供给物品--降落伞，决定了降落伞的种类
	this->addChild(plane_support_);
	plane_support_->setTag(index);
}

//十三、根据支援物品--降落伞的类型，初始化添加的子弹类型
void MainGame::add_support_bullet(float tm)
{
	auto bullet = Bullet::create();
    if (support_index_ == 2)
    {
       bullet->initBullet("bullet_suspand2.png");
	}
     else
     {
       bullet->initBullet("bullet_suspand1.png");
     }
    //让子弹添加在战斗机的上方10像素的位置，模拟从飞机上方发射子弹
	auto point = Point(hero_player_->getPositionX(),
                       hero_player_->getPositionY() + hero_player_->getContentSize().height / 2 + 10);
	bullet->setPosition(point);
    
	this->addChild(bullet);
    
	// 把子弹添加到单例中子弹数组
	ManagerBase::getInstance()->set_bullet_list(bullet);
}

//十五、用来判断敌机和子弹是否碰撞，战斗机和敌机是否碰撞

void MainGame::is_crash(float tm)
{
    auto & enemy_list = ManagerBase::getInstance()->getEnemyList();
	auto & bullet_list = ManagerBase::getInstance()->getBulletList();
    
	/*
     循环遍历每一个敌机节点，判断是否和所有的子弹节点相碰撞，
     每碰撞一次敌机血量减1，子弹从数组移除；
     如果敌机血量小于0，则敌机死亡，且所得总数增加10，
     */
	for (int  i = enemy_list.size() - 1; i >= 0 ; --i)
	{
		/*获取数组中index下标或索引为i的元素，然后先判断该敌机的血量是否小于0 */
		auto enemy = enemy_list.at(i);

        
        /*获得敌机缩放后的内容大小，作为碰撞检测时敌机的大小,返回值是一个rect。 boundingbox 方法是获取节点以父节点左下角为原点的一个矩形，该矩形的大小就是节点各种变形后的大小，矩形的左下角坐标就是节点变形后的左下角坐标.
         bullet是加到 ccspriteBatchNode 上的，ccspriteBatchNode是加到 BulletLayer上面的，ccspriteBatchNode和bulletLayer都是铺满屏幕的。所以子弹调用 boundingbox 获得的矩形是以屏幕左下角为原点的。敌机的原理也是如此。hero是直接加到 herolayer 上的，父节点同样是铺满屏幕的，所以他们的父节点的左下角的坐标都一样的，这就是通过 boundingbox 检测他们是否碰撞的前提。
         */
		auto enemy_size = enemy->boundingBox();
		//循环遍历每一个子弹节点，看它是否和该敌机相撞，
		for (int i = bullet_list.size() - 1; i >= 0; --i)
		{
			auto bullet = bullet_list.at(i);
			//子弹的位置是否在敌机的碰撞矩形区域中，是的话就发生碰撞
			if (enemy_size.containsPoint(bullet->getPosition()))
			{
                //音效3：添加敌机和子弹相撞的音效
                SimpleAudioEngine::getInstance()->playEffect("enemy_down.mp3");
                //设置敌机的血量减1
				enemy->set_hp(enemy->get_hp() - 1);
                
				// 移除并清理子弹节点
				bullet->removeFromParentAndCleanup(true);
				ManagerBase::getInstance()->remove_bullet_list(bullet);
               
				//如果敌机血量小于0，则敌机调用死亡时爆炸并移除的动画，同时游戏得分增加10，并更新游戏所得总分
				if (enemy->get_hp() <= 0)
				{
                      enemy->enemy_death(enemy_type_);
                        
                        if (enemy_type_==1)
                        {
                            score_ += rand_0_1()*10000+1;
                        }
                        else
                        {
                            score_ += rand_0_1()*20000+2;
                        }
                        label_score_num_->setString(String::createWithFormat("%d", score_)->getCString());
                        /*用一个变量生成一个字符串，它类似于c中的sprintf'函数，输出到缓冲区，缓冲区的默认大小为(1024*100) bytes。*/
                }
            }
		}
	}
	/*  循环遍历敌机，判断是否和战斗机碰撞   */
	for (auto i = enemy_list.size() - 1; i >= 0; --i)
	{
		auto enemy = enemy_list.at(i);
        //获取战斗机缩放后的大小，用矩形框表示大小
		auto rect = this->hero_player_->getBoundingBox();
		
        // 获取敌机的位置
        auto point = enemy->getPosition();
        
		//判断敌机的位置是否在战斗机的碰撞矩形区域中，即判断战斗机和敌机是否相撞
		if (rect.containsPoint(point))
		{
            //音效4：添加战斗机和敌机相撞的音效
            SimpleAudioEngine::getInstance()->playEffect("hero_down.mp3");
            //战斗机和敌机相撞，则战斗机死亡
			hero_death(plane_type_);
		}
    }

	// 支援物品
	if (plane_support_ != NULL)
	{
		//获取战斗机缩放后的大小，用矩形框表示大小
		auto rect = hero_player_->getBoundingBox();
		
        //获取支援物品的位置
		auto point = plane_support_->getPosition();
		
        //判断支援物品的位置是否在战斗机的碰撞矩形区域中，若战斗机和支援物品相碰，则表示战斗机接到了支援物品
		if (rect.containsPoint(point))
		{
			//void Node::schedule(SEL_SCHEDULE selector, float interval, unsigned int repeat, float delay)
            //每0.5秒0延迟（没有时间延迟）的重复调用增加支援的子弹，50次，
		    this->schedule(SEL_SCHEDULE(&MainGame::add_support_bullet), 0.5f, 50, 0);
            
			//每一帧停止调用一次add_bullet函数，即停止增加原来的子弹
			//this->unschedule(SEL_SCHEDULE(&MainGame::add_bullet));
			
            //每0.1秒并且延迟5.0秒重复调用增加原来子弹的函数
			//this->schedule(SEL_SCHEDULE(&MainGame::add_bullet), 0.1f, -1, 5.0f);
			//设置支援物品不可见
            plane_support_->setVisible(false);
			plane_support_ = NULL;
		}
		//支援物品落出屏幕时移除支援物品
		if (plane_support_ != NULL && point.y < -plane_support_->getContentSize().height / 2)
		{
			plane_support_->removeFromParent();
			plane_support_ = NULL;
		}
	}
}

/********十五、退出游戏场景时，停止更新背景，并删除ManamgerBase单例，以备下次游戏时重新开始***************/
void MainGame::onExit()
{
    unscheduleUpdate();
    ManagerBase::getInstance()->deleteInstance();
    Layer::onExit();
}