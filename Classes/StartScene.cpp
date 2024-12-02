
#include "StartScene.h"
#include "EnterScene.h"
#include "AudioEngine.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;
using namespace std;



Scene* StartScene::create_Scene()
{
	return StartScene::create();
}

static void enterCall(Ref* eSender)
{
    auto next = Enter::create_Scene();
    Director::getInstance()->replaceScene(next);
}

/* 如果文件无法打开，打印报错信息 */
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

//static Sprite* sp_create(const string& pctname, const Vec2& pos, const float& scale = 1.0f, int layer = 0, Scene* it)
//{
//    Sprite* newsp = Sprite::create();
//}

/* 初始化程序 */
bool StartScene::init()
{
    // 先使用基类的初始化方法
    if (!Scene::init())
        return false;

    auto visibleSize = Director::getInstance()->getVisibleSize();   //(1960,1080)
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    /************     参数     ************/

    constexpr int btnY = 180;           //按钮高度
    constexpr float btn_scale = 1.1f;   //按钮放大倍率
    constexpr float map_scale = 1.5f;   //地图放大倍率
    const Vec2 bg(visibleSize / 2);     //地图位置
    const Vec2 crt(980, 600);           //萝卜位置
    const Vec2 lf1(900, 715);           //叶子1
    const Vec2 lf2(990, 745);           //叶子2
    const Vec2 lf3(1080, 715);          //叶子3
    const Vec2 tm(960, 450);            //商标位置
    const Vec2 ad_btn(600, btnY);       //冒险模式
    const Vec2 boss_btn(970, btnY);     //boss模式
    const Vec2 nest_btn(1340, btnY);    //怪物窝


    /**************************************/

    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("StartScene/StartScene.plist");

    /* 创建精灵的闭包函数 */
    //lambda表达式
    //pctname：  图集中的名称
    //pos：      坐标
    //scale：    放大倍率
    //layer：    放置层数
    auto sp_create = [&](const string& pctname, const Vec2& pos, const float& scale = 1.0f, int layer = 0) {
        Sprite* newsp = Sprite::create();
        newsp->initWithSpriteFrameName(pctname);
        newsp->setPosition(pos);
        newsp->setScale(scale);
        this->addChild(newsp, layer);
        return newsp;
        };

    /* 创建 冒险模式 按钮 */
    auto advenBtn = Button::create(
        "StartScene/contents/btn_adventure_normal.png",
        "StartScene/contents/btn_adventure_pressed.png",
        "StartScene/contents/btn_adventure_normal.png");
    advenBtn->setPosition(ad_btn);
    advenBtn->setScale(btn_scale);

    advenBtn->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
        switch (type)
        {
            case Widget::TouchEventType::BEGAN:
                break;
            case Widget::TouchEventType::ENDED:
                enterCall(this);
                break;
            default:
                break;
        }
        });

    addChild(advenBtn);

    /* 创建 boss模式 按钮 */
    auto bossBtn = Button::create(
        "StartScene/contents/btn_boss_normal.png",
        "StartScene/contents/btn_boss_pressed.png",
        "StartScene/contents/btn_boss_normal.png");

    bossBtn->setPosition(boss_btn);
    bossBtn->setScale(btn_scale);
    addChild(bossBtn);

    /* 创建 怪物窝 按钮 */
    auto nestBtn = Button::create(
        "StartScene/contents/btn_nest_normal.png",
        "StartScene/contents/btn_nest_pressed.png",
        "StartScene/contents/btn_nest_normal.png");

    nestBtn->setPosition(nest_btn);
    nestBtn->setScale(btn_scale);
    addChild(nestBtn);

    /* 创建背景 */
    auto mainbg = sp_create("mainbg.png", bg, map_scale, -1);

    /* 创建萝卜 */
    auto carrot = sp_create("carrot.png", crt, map_scale, 3);
    
    /* 创建三个叶子 */
    auto leaf1 = sp_create("leaf-1.png", lf1, map_scale, 1);
    auto leaf2 = sp_create("leaf-2.png", lf2, map_scale, 2);
    auto leaf3 = sp_create("leaf-3.png", lf3, map_scale, 1);

    /* 创建商标 */
    auto gameTM = sp_create("gameTM.png", tm, map_scale, 4);


    return true;
}

/* 关闭界面，退出程序 */
void StartScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}

