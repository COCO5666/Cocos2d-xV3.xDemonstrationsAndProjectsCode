#include "sceneGraphPriority.h"
sceneGraphPriority::sceneGraphPriority(void)
{
}


sceneGraphPriority::~sceneGraphPriority(void)
{
}

Scene* sceneGraphPriority::createScene()
{
    // ����һ���������󣬸ö��󽫻����Զ��ͷųع����ڴ���ͷ�
    auto scene = Scene::create();
    
    // ��������󣬸ö��󽫻����Զ��ͷųع����ڴ���ͷ�
    auto layer = sceneGraphPriority::create();
    
    // ��HelloWorld����Ϊ�ӽڵ���ӵ�����
    scene->addChild(layer);
    
    // ���س�������
    return scene;
}

// on "init" you need to initialize your instance
bool sceneGraphPriority::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    // ����豸֧�ֵĿɼ�OpenGL��ͼ��С�������ڴ�С����
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // �رղ˵�
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(sceneGraphPriority::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

   
    // �ٴ������㴥�������ߣ�������һ�����㴥���¼������������������¼��߼�
    auto listener1 = EventListenerTouchOneByOne::create();
    // �����Ƿ����´��ݴ���,��Ϊtrueʱ������Ľ������ɵ������ܽ��յ������¼������������´��ݣ���Ϊfalseʱ�������ɣ��������´��ݡ�
    listener1->setSwallowTouches(true);

	// ɾ������������ removeEventListenersForType��_eventDispatcher��ΪNode���ȫ�ֱ�������ֱ��ʹ�á�
    auto removeAllTouchItem = MenuItemFont::create("Delete all the TouchListeners",[=](Ref* sender){auto senderItem = static_cast<MenuItemFont*>(sender);
	 senderItem->setString("TouchListenerDeletedSucceedd");
	 senderItem->setFontSize(15);
	 _eventDispatcher->removeEventListener(listener1); //ɾ��ָ���ļ�����listener1������ɾ���˶�����ɫlayer�ļ���
	 //ɾ�����еĵ��㴥���¼�������������ͬ�˵��Ĺرհ�ť�ĵ����¼�Ҳ��ɾ��
	 //_eventDispatcher->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);
      });
    removeAllTouchItem->setPosition(visibleSize.width/2, visibleSize.height*0.2);
    // �����˵�
    auto menu = Menu::create(removeAllTouchItem,closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);
    // �����ǩ
    auto title = Label::createWithSystemFont("SingleClicked touchTest--SceneGraphPriority", "", 20);
    title->setPosition(visibleSize.width/2, visibleSize.height*0.9);
    this->addChild(title);
    
    // ��ʾ��ǩ 
    auto subtitle = Label::createWithSystemFont("Please click or drag Slider", "", 12);
    subtitle->setPosition(visibleSize.width/2, visibleSize.height*0.8);
    this->addChild(subtitle);
    
    // ��������������� 
    auto sprite1 = Sprite::create("CyanSquare.png");
    sprite1->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2) + Vec2(-80, 80));
    addChild(sprite1, 2);
    
    auto sprite2 = Sprite::create("MagentaSquare.png");
    sprite2->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    addChild(sprite2, 3);
    
    auto sprite3 = Sprite::create("YellowSquare.png");
    sprite3->setPosition(Vec2(0, 0));
    sprite2->addChild(sprite3, 1);
   
    //�� ͨ�� lambda ���ʽֱ��ʵ�ֲ��󶨴����¼�����Ӧ����
    listener1->onTouchBegan = [](Touch* touch, Event* event){
        // ��õ�ǰ�¼�������Ŀ�����
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        // ��õ�ǰ�Ĵ�����
        Point locationInNode = target->convertToNodeSpace(touch->getLocation());
        // ��ô��������ContentSize
        Size s = target->getContentSize();
        // ���λ�þ���
        Rect rect = Rect(0, 0, s.width, s.height);
        // ���λ�þ��ΰ���������
        if (rect.containsPoint(locationInNode))
        {
            log("onTouchBegan... x = %f, y = %f", locationInNode.x, locationInNode.y);
            // ����͸����
            target->setOpacity(180);
            // �����û������¼��Ѿ�������������onTouchMoved��onTouchEnded��onTouchCancelled�������Ӧ�������¼��������򲻻���ȥ���м������δ����¼���
            return true;
        }
        return false;
    };
    
    listener1->onTouchMoved = [](Touch* touch, Event* event){
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        // �ƶ������ľ���
        target->setPosition(target->getPosition() + touch->getDelta());
		
		//�޷���ʽ����this������Ϊ��δָ��Ĭ�ϲ���ģʽ
		/*auto position=touch->getLocation();
		auto position1=this->convertToNodeSpace(position);
		target->setPosition (position1);
		*/
    };
    
    listener1->onTouchEnded = [=](Touch* touch, Event* event){
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        // ����͸����
        target->setOpacity(255);
        std::string name;
        if (target == sprite2) //sprite2Ϊ���ɫ
        {
            name = "MagentaSquare.png";
            sprite1->setZOrder(100);//�޸�����ɫ��z��˳��Ϊ100���ŵ����ϲ�
           //�޸��б����ı�����
			subtitle->setString("MagentaSquare responses event,CyanSquare's ZOrderis modified to 100");
		}
        else if(target == sprite1)//sprite1Ϊ����ɫ
        {
            name = "CyanSquare.png";
            sprite1->setZOrder(0);   //�޸�����ɫ��z��˳��Ϊ0���ŵ����
             //�޸��б����ı�����
			subtitle->setString("CyanSquare responses event,CyanSquare's ZOrderis modified to 100");
        }else{
            name = "YellowSquare.png";
        }
        log("onTouchEnded.. What you touched is %s",name.c_str());
    };
    
    /*�۽���������ӵ��¼��ַ���dispatcher�С�����ӳ��������¼���������
	ֱ��ʹ��Node���Դ���ȫ������_eventDispatcher��������listener1->setSwallowTouches(false)ʱ��
	���ܿ���SceneGraphPriority��Ч����
	*/
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, sprite1);
	/*ע�⣺��ʹ��addEventListenerWithSceneGraphPriority����addEventListenerWithFixedPriority����ʱ��
	          ��Ե�ǰʹ�õ��¼����������һ����ע��ı�ǣ���ʹ�������ܹ�����Ӷ�Ρ�
			  ���Ե������ٴ�ʹ��listener1��ʱ����Ҫʹ��clone()��������һ���µĿ�¡��*/
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), sprite2);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), sprite3);
    
  return true;
}

void sceneGraphPriority::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}