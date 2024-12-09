#include "EnterScene.h"
#include "MapChoose.h"
#include "OptionScene_1.h"
#include "OptionScene_2.h"
#include "OptionScene_3.h"
#include "AudioEngine.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;
using namespace std;


/* 如果文件无法打开，打印报错信息 */
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

/* 创建场景 */
Scene* OptionScene_1::create_Scene()
{
    return OptionScene_1::create();
}


/* 返回按钮切换至StartScene */
void OptionScene_1::back_onButtonClicked(Ref* sender) {
    Director::getInstance()->popScene();
}

/* 场景初始化 */
bool OptionScene_1::init()
{
    if (!Scene::init())
        return false;

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("OptionScene/OptionScene_1.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("OptionScene/OptionScene_2.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("OptionScene/OptionScene_3.plist");

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
    //normal_name：   正常状态在图集中的名字
    //pressed_name：  选择状态在图集中的名字
    //locked_name：   不可点击状态在图集中的名字 
    //pos：           坐标
    //scale：         放大倍率
    //layer：         放置层数
    //btn_type:       按钮类别：
    //                         1 - 选项
    //                         2 - 数据统计
    //                         3 - 制作方
    //                         4 - Home
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
    constexpr int btnY2 = 440;              //小按钮高度
    constexpr int locks = 220;              //锁高度
    constexpr float btn_scale = 1.5f;       //按钮放大倍率
    constexpr float map_scale = 1.5f;      //地图放大倍率
    const Vec2 options_btn(540, btnY1);          //选项按钮
    const Vec2 statistics_btn(980, btnY1);        //数据统计按钮
    const Vec2 producer_btn(1400, btnY1);       //制作方按钮
    const Vec2 sound_btn(540, btnY2);          //音效按钮
    const Vec2 BGM_btn(980, btnY2);        //背景音乐按钮
    const Vec2 reset_btn(1400, btnY2);       //重置游戏按钮
    const Vec2 reset_yes_btn(540, btnY2);          //确认按钮
    const Vec2 reset_no_btn(980, btnY2);        //取消按钮
    const Vec2 po_btn_home(360, 920);      //home按钮位置
    const Vec2 po_sound_effect(550, 800);     //音效 字幕位置 
    const Vec2 po_BGM(980, 800);     //BGM 字幕位置

    /**************************************/

       /* 创建字幕 */
    auto word_sound_effect = sp_create("word_sound_effect.png", po_sound_effect, map_scale, 1);
    auto word_BGM = sp_create("word_BGM.png", po_BGM , map_scale, 1);

    /* 创建 选项 按钮 */
    auto Options = btn_create(
        "OptionScene_1/contents/options_normal.png",
        "OptionScene_1/contents/options_pressed.png",
        options_btn, btn_scale);
    /* 创建 数据统计 按钮 */
    auto Statistics = btn_create(
        "OptionScene_1/contents/statistics_normal.png",
        "OptionScene_1/contents/statistics_pressed.png",
        statistics_btn, btn_scale);
    /* 创建 制作方 按钮 */
    auto Producer= btn_create(
        "OptionScene_1/contents/producer_normal.png",
        "OptionScene_1/contents/producer_pressed.png",
        producer_btn, btn_scale);
    /* 创建 开启音效 按钮 */
    auto sound_effect = btn_create(
        "OptionScene_1/contents/sound_effect_open.png",
        "OptionScene_1/contents/sound_effect_close.png",
        sound_btn, btn_scale);
    /* 创建 开启背景音乐 按钮 */
    auto BGM = btn_create(
        "OptionScene_1/contents/BGM_open.png",
        "OptionScene_1/contents/BGM_close.png",
        BGM_btn, btn_scale);
    /* 创建 重置游戏 按钮 */
    auto reset = btn_create(
        "OptionScene_1/contents/reset_normal.png",
        "OptionScene_1/contents/reset_pressed.png",
        reset_btn, btn_scale);
    /* 创建 重置游戏确定 按钮 */
    auto reset = btn_create(
        "OptionScene_1/contents/reset_yes_normal.png",
        "OptionScene_1/contents/reset_yes_pressed.png",
        reset_yes_btn, btn_scale);
    /* 创建 重置游戏取消 按钮 */
    auto reset = btn_create(
        "OptionScene_1/contents/reset_no_normal.png",
        "OptionScene_1/contents/reset_no_pressed.png",
        reset_no_btn, btn_scale);
    /* 返回 */
    auto btn_back = btn_create(
        "OptionScene_1/contents/option_1_back_normal.png",
        "OptionScene_1/contents/option_1_back_pressed.png",
        po_btn_home, 3);

    /************     参数     ************/

    const Vec2 po_bg(visibleSize / 2);     //地图位置
    const Vec2 po_bg_bottom(1000, 150);    //bg_bottom位置
    constexpr float btn_scale = 1.1f;      //按钮放大倍率
    constexpr float map_scale = 1.5f;      //地图放大倍率
    const Vec2 po_btn_back(360, 920);      //home按钮位置
    const Vec2 po_options(750, 922);          //column_options位置
    const Vec2 po_statistics(980, 920);       //column_statistics位置
    const Vec2 po_producer(1190, 925);        //column_producer位置

    /**************************************/

    /********** 创建精灵 **********/
    /* 创建背景 */
    auto bg = sp_create("optionBG1.png", po_bg, map_scale, -1);

    /* 创建可点击对象 */
    auto options = sp_create("statistics_pressed.png", po_options, map_scale, 0);
    auto statistics = sp_create("statistics_normal.png", po_statistics, 2.3, 0);
    statistics->setName("statistics");
    auto producer = sp_create("producer_normal.png", po_producer, 2.2, 0);
    producer->setName("producer");

    /********** 创建事件 **********/
    /* statistics */
    auto statistics_click_listener = EventListenerTouchOneByOne::create();
    statistics_click_listener->onTouchBegan = [&](Touch* touch, Event* event) {
        auto pos = touch->getLocation();    //获取点击位置
        auto sp = (Sprite*)(this->getChildByName("statistics"));    //从场景中抓取名为statistics的精灵
        if (sp->getBoundingBox().containsPoint(pos))
            return true;    //点击位置在精灵范围内
        return false;   //返回false，中止执行事件响应
        };
    statistics_click_listener->onTouchMoved = [](Touch* touch, Event* event) {};
    statistics_click_listener->onTouchEnded = [&](Touch* touch, Event* event) {
        auto next = OptionScene_2::create_Scene();
        if (next == nullptr)
            return false;   //确保next非空
        Director::getInstance()->replaceScene(next);
        return true;
        };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(statistics_click_listener, this);

    /* producer */
    auto producer_click_listener = EventListenerTouchOneByOne::create();
    producer_click_listener->onTouchBegan = [&](Touch* touch, Event* event) {
        auto pos = touch->getLocation();    //获取点击位置
        auto sp = (Sprite*)(this->getChildByName("producer"));    //从场景中抓取名为producer的精灵
        if (sp->getBoundingBox().containsPoint(pos))
            return true;    //点击位置在精灵范围内 and 当前为第一个主题
        return false;   //返回false，中止执行事件响应
        };
    producer_click_listener->onTouchMoved = [](Touch* touch, Event* event) {};
    producer_click_listener->onTouchEnded = [&](Touch* touch, Event* event) {
        auto next = OptionScene_3::create_Scene();
        if (next == nullptr)
            return false;   //确保next非空
        Director::getInstance()->replaceScene(next);
        return true;
        };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(producer_click_listener, this);

    /* sound_effect */
    auto sound_effect_click_listener = EventListenerTouchOneByOne::create();
    sound_effect_click_listener->onTouchBegan = [&](Touch* touch, Event* event) {
        auto pos = touch->getLocation();    //获取点击位置
        auto sp = (Sprite*)(this->getChildByName("sound_effect"));    //从场景中抓取名为sound_effect的精灵
        if (sp->getBoundingBox().containsPoint(pos))
            return true;    //点击位置在精灵范围内 and 当前为第一个主题
        return false;   //返回false，中止执行事件响应
        };
    sound_effect_click_listener->onTouchMoved = [](Touch* touch, Event* event) {};
    sound_effect_click_listener->onTouchEnded = [&](Touch* touch, Event* event) {
        auto next = OptionScene_3::create_Scene();
        if (next == nullptr)
            return false;   //确保next非空
        Director::getInstance()->replaceScene(next);
        return true;
        };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(sound_effect_click_listener, this);

    /* BGM */
    auto BGM_click_listener = EventListenerTouchOneByOne::create();
    BGM_click_listener->onTouchBegan = [&](Touch* touch, Event* event) {
        auto pos = touch->getLocation();    //获取点击位置
        auto sp = (Sprite*)(this->getChildByName("BGM"));    //从场景中抓取名为BGM的精灵
        if (sp->getBoundingBox().containsPoint(pos))
            return true;    //点击位置在精灵范围内 and 当前为第一个主题
        return false;   //返回false，中止执行事件响应
        };
    BGM_click_listener->onTouchMoved = [](Touch* touch, Event* event) {};
    BGM_click_listener->onTouchEnded = [&](Touch* touch, Event* event) {
        auto next = OptionScene_3::create_Scene();
        if (next == nullptr)
            return false;   //确保next非空
        Director::getInstance()->replaceScene(next);
        return true;
        };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(BGM_click_listener, this);

    return true;
}