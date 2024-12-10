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
//创建弹窗层
class PopupLayer : public cocos2d::Layer {
public:
    static PopupLayer* createlayer();
    virtual bool init();
    CREATE_FUNC(PopupLayer);
};

PopupLayer* PopupLayer::createlayer() {
    auto layer = PopupLayer::createlayer();
    return layer;
}

bool PopupLayer::init() {
    if (!Layer::init()) {
        return false;
    }
    // 创建一个全屏的灰暗层作为背景
    auto dimLayer = LayerColor::create(Color4B(0, 0, 0, 128), Director::getInstance()->getVisibleSize().width,
        Director::getInstance()->getVisibleSize().height);
    this->addChild(dimLayer);
    // 添加弹窗内容，如文本、按钮等
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

    const Vec2 reset_yes_btn(540, 440);          //确认按钮
    const Vec2 reset_no_btn(980, 440);        //取消按钮
    constexpr float btn_scale = 1.5f;       //按钮放大倍率
    /**************************************/

       /* 创建 重置游戏确定 按钮 */
    auto reset2 = btn_create(
        "OptionScene/contents/reset_yes_normal.png",
        "OptionScene/contents/reset_yes_pressed.png",
        reset_yes_btn, btn_scale);
    /* 创建 重置游戏取消 按钮 */
    auto reset3 = btn_create(
        "OptionScene/contents/reset_no_normal.png",
        "OptionScene/contents/reset_no_pressed.png",
        reset_no_btn, btn_scale);

    reset3->addClickEventListener([](Ref* sender) {
        // 如果是层（Layer），从父节点移除自身
        if (auto layer = dynamic_cast<Layer*>(sender)) {
            layer->removeFromParent();
        }
        });
    this->addChild(reset3);
    return true;
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
    constexpr float btn_scale = 1.5f;       //按钮放大倍率
    constexpr float map_scale = 1.5f;      //地图放大倍率
    const Vec2 options_btn(540, btnY1);          //选项按钮
    const Vec2 statistics_btn(980, btnY1);        //数据统计按钮
    const Vec2 producer_btn(1400, btnY1);       //制作方按钮
    const Vec2 sound_btn(850, 700);          //音效按钮
    const Vec2 BGM_btn(1250, 700);        //背景音乐按钮
    const Vec2 reset_btn(1025, 500);       //重置游戏按钮
    const Vec2 po_btn_home(440, 960);      //home按钮位置
    const Vec2 po_sound_effect(840, 800);     //音效 字幕位置 
    const Vec2 po_BGM(1240, 800);     //BGM 字幕位置
    const Vec2 po_bg(visibleSize / 2);     //地图位置
    const Vec2 po_bg_bottom(1000, 150);    //bg_bottom位置
    const Vec2 po_options(750, 922);          //column_options位置
    const Vec2 po_statistics(980, 920);       //column_statistics位置
    const Vec2 po_producer(1190, 925);        //column_producer位置


    /**************************************/

       /* 创建字幕 */
    auto word_sound_effect = sp_create("word_sound_effect.png", po_sound_effect, map_scale, 1);
    auto word_BGM = sp_create("word_BGM.png", po_BGM , map_scale, 1);

    /* 创建 选项 按钮 */
    auto Options_btn = btn_create(
        "OptionScene/contents/options_normal.png",
        "OptionScene/contents/options_pressed.png",
        options_btn, btn_scale);
    /* 创建 数据统计 按钮 */
    auto Statistics_btn = btn_create(
        "OptionScene/contents/statistics_normal.png",
        "OptionScene/contents/statistics_pressed.png",
        statistics_btn, btn_scale);
    /* 创建 制作方 按钮 */
    auto Producer_btn= btn_create(
        "OptionScene/contents/producer_normal.png",
        "OptionScene/contents/producer_pressed.png",
        producer_btn, btn_scale);
    /* 创建 开启音效 按钮 */
    auto sound_effect_btn = btn_create(
        "OptionScene/contents/sound_effect_open.png",
        "OptionScene/contents/sound_effect_close.png",
        sound_btn, btn_scale);
    /* 创建 开启背景音乐 按钮 */
    auto btn_BGM = btn_create(
        "OptionScene/contents/BGM_open.png",
        "OptionScene/contents/BGM_close.png",
        BGM_btn, btn_scale);
    /* 创建 重置游戏 按钮 */
    auto reset1_btn = btn_create(
        "OptionScene/contents/reset_normal.png",
        "OptionScene/contents/reset_pressed.png",
        reset_btn, btn_scale);
    /* 返回 */
    auto btn_back = btn_create(
        "OptionScene/contents/option_1_back_normal.png",
        "OptionScene/contents/option_1_back_pressed.png",
        po_btn_home, 1.5);


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
    auto reset1 = sp_create("reset_normal.png", reset_btn, 2.2, 0);
    reset1->setName("reset1");


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
    /* reset1 */
    auto reset1_click_listener = EventListenerTouchOneByOne::create();
    reset1_click_listener->onTouchBegan = [&](Touch* touch, Event* event) {
        auto pos = touch->getLocation();    //获取点击位置
        auto sp = (Sprite*)(this->getChildByName("reset1"));    //从场景中抓取名为reset1的精灵
        if (sp->getBoundingBox().containsPoint(pos))
            return true;    //点击位置在精灵范围内
        return false;   //返回false，中止执行事件响应
        };
    statistics_click_listener->onTouchMoved = [](Touch* touch, Event* event) {};
    statistics_click_listener->onTouchEnded = [&](Touch* touch, Event* event) {
        auto resetpopupLayer = PopupLayer::create();
        if (auto scene = Director::getInstance()->getRunningScene()) {
            scene->addChild(resetpopupLayer);
        }
        };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(reset1_click_listener, this);


    return true;
}