#include "AppDelegate.h"
#include "sceneGraphPriority.h"
#include "ContentLayer.h"
#include "fiveStepSingleTouch.h"
#include "fixedPriority.h"
#include "touchesTest.h"
#include "mouseEvent.h"
USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
		glview = GLViewImpl::create("My Game");
		//glview->setFrameSize(480,320);
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(true);
	glview->setDesignResolutionSize(480,320,ResolutionPolicy::EXACT_FIT);
    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
	/*1:通过fiveStepSingleTouch类以5个步骤简单地实现单点触摸,
	并演示了touch事件的调用顺序。
	onExit-> onTouchBegan->onTouchMoved->onTouchEnded->onTouchCancelled->onEnter*/
   // auto scene=fiveStepSingleTouch::createScene();
	//2：通过HelloWorld类以3步骤实现单点触摸和场景事件优先的触摸测试，
    //auto scene = sceneGraphPriority::createScene(); 
	//3:通过fixedPriority和封装有监听事件的类spritePriotiry以3步骤实现单点触摸和固定值优先的触摸测试，
	 //auto scene = fixedPriority::createScene();
	//4：通过ContentLayer类的单点触摸和move回调实现滑动屏幕选择菜单效果
      auto scene = ContentLayer::createScene();
	//5：通过touchesTest类以5个步骤简单地实现多点触摸
	//auto scene=touchesTest::createScene();
	//6:通过mouseEvent类测试鼠标事件
	//auto scene=mouseEvent::createScene();
    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
