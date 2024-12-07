
#include "StartScene.h"
#include "EnterScene.h"
#include "HelpScene_1.h"
#include "AudioEngine.h"
#include "ui/CocosGUI.h"
#include "ui/UIButton.h"

USING_NS_CC;
using namespace ui;
using namespace std;


/* 创建场景 */
Scene* StartScene::create_Scene()
{
	return StartScene::create();
}

/* 进入章节选择 */
static void enterCall(Ref* eSender)
{
    auto next = Enter::create_Scene();
    Director::getInstance()->pushScene(next);
}

/* 进入帮助 */
static void helpCall(Ref* eSender)
{
    auto next = HelpScene_1::create_Scene();
    Director::getInstance()->pushScene(next);
}

/* 如果文件无法打开，打印报错信息 */
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

/* 初始化程序 */
bool StartScene::init()
{
    // 先使用基类的初始化方法
    if (!Scene::init())
        return false;

    auto visibleSize = Director::getInstance()->getVisibleSize();   //(1960,1080)
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 预加载精灵图集
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

    /* 创建按钮的闭包函数 */
    //lambda表达式
    //normal：   正常状态显示
    //pressed：  点击状态显示
    //pos：      坐标
    //scale：    放大倍率
    //layer：    放置层数
    auto btn_create = [&](const string& normal, const string& pressed,
        const Vec2& pos, const float& scale = 1.0f, int layer = 1)
        {
            auto btn = Button::create();
            btn->loadTextures(normal, pressed, normal);
            btn->setPosition(pos);
            btn->setScale(scale);
            this->addChild(btn, layer);
            return btn;
        };

    /************     参数     ************/

    constexpr int btnY1 = 180;              //大按钮高度
    constexpr int btnY2 = 400;              //小按钮高度
    constexpr int locks = 220;              //锁高度
    constexpr float btn_scale = 1.5f;       //按钮放大倍率
    constexpr float map_scale = 1.5f;       //地图放大倍率
    const Vec2 bg(visibleSize / 2);         //地图位置
    const Vec2 crt(980, 600);               //萝卜位置
    const Vec2 lf1(900, 715);               //叶子1
    const Vec2 lf2(990, 645);               //叶子2
    const Vec2 lf3(989, 637);               //叶子3
    const Vec2 tm(960, 450);                //商标位置
    const Vec2 ad_btn(540, btnY1);          //冒险模式
    const Vec2 boss_btn(980, btnY1);        //boss模式
    const Vec2 nest_btn(1400, btnY1);       //怪物窝
    const Vec2 setting_btn(570, btnY2);     //设置按钮
    const Vec2 help_btn(1400, btnY2);       //帮助按钮
    const Vec2 rgup(1526, 897);             //右上角
    const Vec2 gugu(560, 735);              //小鸟
    const Vec2 lock1(1145, locks);          //boss锁
    const Vec2 lock2(1565, locks);          //nest锁

    /**************************************/

    /* 创建 冒险模式 按钮 */
    auto adventure = btn_create(
        "StartScene/btn/btn_adventure_normal.png",
        "StartScene/btn/btn_adventure_pressed.png",
        ad_btn, btn_scale);
    // 切换场景
    adventure->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
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

    /* 创建 设置 按钮 */
    auto settings = btn_create(
        "StartScene/btn/btn_setting_normal.png",
        "StartScene/btn/btn_setting_pressed.png",
        setting_btn, btn_scale, 1);

    /* 创建 帮助 按钮 */
    auto help = btn_create(
        "StartScene/btn/btn_help_normal.png",
        "StartScene/btn/btn_help_pressed.png",
        help_btn, btn_scale, 1);
    // 切换场景
    help->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
        switch (type)
        {
            case Widget::TouchEventType::BEGAN:
                break;
            case Widget::TouchEventType::ENDED:
                helpCall(this);
                break;
            default:
                break;
        }
        });

    /* 创建 boss模式 按钮 */
    auto boss = sp_create("btn_boss_normal.png", boss_btn, btn_scale, 1);

    /* 创建 怪物窝 按钮 */
    auto nest = sp_create("btn_nest_normal.png", nest_btn, btn_scale, 1);

    /* 创建背景 */
    auto mainbg = sp_create("mainbg.png", bg, map_scale, -1);

    /* 创建萝卜 */
    auto carrot = sp_create("carrot.png", crt, map_scale, 3);
    
    /* 创建三个叶子 */
    auto leaf1 = sp_create("leaf-1.png", lf1, map_scale, 1);
    auto leaf2 = sp_create("leaf-2.png", lf2, map_scale, 2);
    leaf2->setAnchorPoint(Vec2(0.5, 0));
    auto leaf3 = sp_create("leaf-3.png", lf3, map_scale, 1);
    leaf3->setAnchorPoint(Vec2(0, 0));
    // 叶子抖动
    auto shake = Sequence::create(RotateBy::create(0.1f, 15.0f), RotateBy::create(0.1f, -15.0f), nullptr);
    auto once = Repeat::create(shake, 2);
    auto delay = DelayTime::create(2.0f);
    auto seq1 = Sequence::create(delay, once, delay, delay, nullptr);
    auto seq2 = Sequence::create(delay, delay, once, delay, nullptr);
    leaf2->runAction(RepeatForever::create(seq1));
    leaf3->runAction(RepeatForever::create(seq2));

    /* 创建商标 */
    auto gameTM = sp_create("gameTM.png", tm, map_scale, 4);

    /* 创建角标 */
    auto corner = sp_create("rgup_corner.png", rgup, map_scale, 4);

    /* 创建小鸟 */
    auto bird = sp_create("bird.png", gugu, map_scale, 4);
    // 小鸟飞飞
    auto move_up = MoveBy::create(2, Vec2(0, 50));
    auto move_down = MoveBy::create(2, Vec2(0, -50));
    auto seq = Sequence::create(move_up, move_down, nullptr);
    bird->runAction(RepeatForever::create(seq));

    /* 创建锁 */
    auto lock_boss = sp_create("locked.png", lock1, 1.1f, 5);
    auto lock_nest = sp_create("locked.png", lock2, 1.1f, 5);
    
    return true;
}

/* 关闭界面，退出程序 */
void StartScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}

