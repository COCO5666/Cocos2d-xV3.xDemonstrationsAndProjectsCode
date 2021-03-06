#include "AppDelegate.h"
#include "MainScene.h"
#include "GameScene.h"

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms 
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("ContraGame");
		glview->setFrameSize(512,480);
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    //director->setAnimationInterval(1.0 / 120);

    // create a scene. it's an autorelease object
    auto scene = MainScene::createScene();

    // run
    //director->runWithScene(scene);
	Director::getInstance()->replaceScene(TransitionMoveInR::create(3.0, MainScene::createScene()));

	//Preload sound
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("sound/backgroundMusic.mp3");
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("sound/title.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/gun.mp3");
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
