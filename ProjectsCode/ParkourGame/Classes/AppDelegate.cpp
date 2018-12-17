#include "AppDelegate.h"
#include "LoadingScene.h"

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
    if(!glview) 
	{
        glview = GLViewImpl::create("My Parkour Game");
		glview->setFrameSize(800,480); //������Ļ�ߴ�
        director->setOpenGLView(glview);
    }

	glview->setDesignResolutionSize(800,480,ResolutionPolicy::EXACT_FIT); //���÷ֱ������䣬�������õ�����Ʒֱ���
    
	//����Ĭ��·���������Ͳ���ʹ��images/bird.png�����ķ�Ŀ¼�ˣ�ֱ����bird.png���е�
	std::vector<std::string> resPaths;
	resPaths.push_back("fonts");
	resPaths.push_back("images");
	resPaths.push_back("sounds");
	FileUtils::getInstance()->setSearchResolutionsOrder(resPaths);
	
	// turn off display FPS
    director->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
	auto scene=LoadingScene::create(); //����ʹ�õ���Ĭ�ϵ�create����

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
