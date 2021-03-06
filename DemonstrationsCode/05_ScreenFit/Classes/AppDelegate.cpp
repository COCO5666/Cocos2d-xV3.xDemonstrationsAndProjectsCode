#include "AppDelegate.h"
#include "HelloWorldScene.h"
using namespace std;

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

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
    // initialize directorf
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("ScreenFit");
        director->setOpenGLView(glview);
    }
    //1. 资源分辨率->设计分辨率
    //2. 设计分辨率->屏幕分辨率
    /*选择屏幕分辨率为480*320，图像fishBg.png的分辨率为800*480，
     setDesignResolutionSize（设计分辨率）为800*480      
     要想让图像显示到屏幕上，必须对对象缩小图像，
     按宽缩放的比例为800/480=5/3=1.667,宽度缩放比例大
     按高缩放的比例为480/320=3/2=1.5,按哪个缩放都存在一定问题。高度缩放比例小
     1.设计分辨率选择为FIXED_WIDTH，先照顾宽度，高度可能出现黑边，也可能被拉伸。
        针对这里的图像，按1.667缩小，宽度缩小后800/1.667=800/(5/3)=480，正好；
        高度缩小为480/1.667=480/(5/3)=288，288<320,即缩小的太多了，这会导致上下有黑边。
     2.把设计分辨率选择为FIXED_HEIGHT，先照顾高度，宽度可能出现黑边，也可能被拉伸。针对这里的图像，按1.5缩小，高度缩小为480/1.5=480/(3/2)=320，刚好；宽度缩小后800/1.5=800/(3/2)=534，533>480,即宽度缩小的不够多，这就需要左右两边都cut一部分才能显示到屏幕上。
     3.设计分辨率选择为ExactFit，宽高要各按自己需要的比例进行缩放，则会导致图像被拉伸，缩放过多的那边要拉伸。针对这里的图像，让图片宽高都全部正常显示，则应把高度的288拉伸到320，这就导致图像高度上被拉伸。
     4.设计分辨率选择为SHOW_ALL时，即选择较大的缩放比例，缩放过多的那边让它出现黑边。针对当前这幅图是width正常显示，height有黑边。如果换成高度的缩放比例较大的图像的话，就会导致左右有黑边。
     5.设计分辨率选择为NO_BORDER时，即选择较小的缩放比例，就要cut裁剪一部分图像。针对当前这幅图是height正常显示，width需要cut裁剪。如果换成高度的缩放比例较大的图像的话，就会导致width正常显示，height需要cut裁剪。
     
     */
    
    glview->setDesignResolutionSize(800, 480, ResolutionPolicy::FIXED_WIDTH);
    
    director->setContentScaleFactor(1.0f); //必须设置设计分辨率
#pragma mark 按路径去查找不同的资源 但会引起程序包过大
//   
//    auto fu = FileUtils::getInstance();
//    
//    if (glview->getFrameSize().width >480) {
//        vector<string> v;
//        v.push_back(string("Retina"));
//        fu->setSearchPaths(v);//设置搜索路径
//    }else{
//        vector<string> v;
//        v.push_back(string("NoRetina"));
//        fu->setSearchPaths(v);
//    }
    director->setDisplayStats(true);
    director->setAnimationInterval(1.0 / 60);
    auto scene = HelloWorld::createScene();
    director->runWithScene(scene);
    
    //获得设计分辨率大小 -- 做程序时以哪一个分辨率作为设计标准
    Size winSize = director->getWinSize();
    log("设计分辨率:(%f,%f)",winSize.width,winSize.height);
    
    Size frameSize=glview->getFrameSize();
    log("屏幕分辨率（设备分辨率）:(%f,%f)",frameSize.width,frameSize.height);
    //cocos2d: 屏幕分辨率（设备分辨率）:(960.000000,640.000000)
    
    Size visibelSize = director->getVisibleSize();
    log("可见区域大小:(%f,%f)",visibelSize.width,visibelSize.height);
    
    Vec2 visibleOrigin = director->getVisibleOrigin();
    log("可见区域起点: (%f,%f)",visibleOrigin.x,visibleOrigin.y);
    
    
    /*针对这里的图像fishBg.png，
     1.当为NO_BORDER时，选择较小的缩放比例3/2,
     cocos2d: 设计分辨率:(800.000000,480.000000)
     cocos2d: 可见区域大小:(720.000000,480.000000) //480*(3/2)=720
     cocos2d: 可见区域起点: (40.000000,0.000000)  (800-720)/2=40
     2.当为EXACT_FIT时，宽缩放比例5/3=1.667,高缩放比例3/2,
     cocos2d: 设计分辨率:(800.000000,480.000000)
     cocos2d: 可见区域大小:(800.000000,480.000000)
     cocos2d: 可见区域起点: (0.000000,0.000000)
     3.当为FIXED_WIDTH时，缩放比例800/480=5/3=1.667,
     cocos2d: 设计分辨率:(800.000000,534.000000)   //320*(5/3)=534
     cocos2d: 可见区域大小:(800.000000,534.000000)  // (534-480)/2=27为上下两边看到的黑边
     cocos2d: 可见区域起点: (0.000000,0.000000)
     4.当为FIXED_HEIGHT时，缩放比例为480/320=3/2=1.5,
      cocos2d: 设计分辨率:(720.000000,480.000000)  //480*(3/2)=720,
      cocos2d: 可见区域大小:(720.000000,480.000000)
      cocos2d: 可见区域起点: (0.000000,0.000000)
     5.当为SHOW_ALL时，缩放比例为800/480=5/3=1.667,
     cocos2d: 设计分辨率:(800.000000,480.000000)
     cocos2d: 可见区域大小:(800.000000,480.000000)
     cocos2d: 可见区域起点: (0.000000,0.000000)
     */
    return true;
}
void AppDelegate::applicationDidEnterBackground()
{
    Director::getInstance()->stopAnimation();
}

void AppDelegate::applicationWillEnterForeground()
{
    Director::getInstance()->startAnimation();
}
