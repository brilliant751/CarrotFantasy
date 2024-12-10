
#include "AppDelegate.h"
#include "StartScene.h"
#include "EnterScene.h"

// #define USE_AUDIO_ENGINE 1
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;

USING_NS_CC;

//�ɹ�ѡ�����Ļ�ֱ���
static Size small_s = Size(480, 320);
static Size medium_s = Size(1024, 768);
static Size large_s = Size(2048, 1536);
//static Size design_s = Size(1960, 1080);
static Size design_s = Size(2050, 1200);

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
    AudioEngine::end();
}

/* �����ı���ʽ������Ķ� */
void AppDelegate::initGLContextAttrs()
{
    // set OpenGL context attributes: red,green,blue,alpha,depth,stencil,multisamplesCount
    GLContextAttrs glContextAttrs = { 8, 8, 8, 8, 24, 8, 0 };

    GLView::setGLContextAttrs(glContextAttrs);
}

//���ڰ�װ�����
//����Ķ�
static int register_all_packages()
{
    return 0; //flag for packages manager
}

/* ��ɳ�ʼ�� */
bool AppDelegate::applicationDidFinishLaunching() {
    // ��ʼ������
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if (!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect("demo", cocos2d::Rect(0, 0, design_s.width, design_s.height));
#else
        glview = GLViewImpl::create("demo");
#endif
        director->setOpenGLView(glview);
    }

    //FPS��ʾ����
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0f / 60);

    // Set the design resolution
    glview->setDesignResolutionSize(design_s.width, design_s.height, ResolutionPolicy::NO_BORDER);
    auto frameSize = glview->getFrameSize();
    // if the frame's height is larger than the height of medium size.
    if (frameSize.height > medium_s.height)
    {
        director->setContentScaleFactor(MIN(large_s.height / design_s.height, large_s.width / design_s.width));
    }
    // if the frame's height is larger than the height of small size.
    else if (frameSize.height > small_s.height)
    {
        director->setContentScaleFactor(MIN(medium_s.height / design_s.height, medium_s.width / design_s.width));
    }
    // if the frame's height is smaller than the height of medium size.
    else
    {
        director->setContentScaleFactor(MIN(small_s.height / design_s.height, small_s.width / design_s.width));
    }

    register_all_packages();

    // ����һ������
    auto scene = StartScene::create_Scene();

    // ����
    director->runWithScene(scene);

    return true;
}

/* Ӧ�ý����̨��֮�� */
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

#if USE_AUDIO_ENGINE
    AudioEngine::pauseAll();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    SimpleAudioEngine::getInstance()->pauseAllEffects();
#endif
}

/* Ӧ�ý���ǰ̨��֮ǰ�� */
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

#if USE_AUDIO_ENGINE
    AudioEngine::resumeAll();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    SimpleAudioEngine::getInstance()->resumeAllEffects();
#endif
}

