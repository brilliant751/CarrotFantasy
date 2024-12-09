
#include "StartScene.h"
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
Scene* OptionScene_2::create_Scene()
{
    return OptionScene_2::create();
}

/* 返回按钮切换至StartScene */
void OptionScene_2::back_onButtonClicked(Ref* sender) {
    auto next = StartScene::create_Scene();
    Director::getInstance()->popScene();
}

/* 场景初始化 */
bool OptionScene_2::init()
{
    if (!Scene::init())
        return false;

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

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
    //                         1 - home
    auto btn_create = [&](const string& normal_name, const string& pressed_name, const string& locked_name,
        const Vec2& pos, int btn_type, const float& scale = 1.1f, int layer = 0) {
            auto temp_btn = Button::create(normal_name, pressed_name, locked_name);
            temp_btn->setPosition(pos);
            temp_btn->setScale(scale);

            temp_btn->addTouchEventListener([=](Ref* sender, Widget::TouchEventType type) {
                switch (type)
                {
                case ui::Widget::TouchEventType::BEGAN:
                    break;
                case ui::Widget::TouchEventType::ENDED:
                    switch (btn_type) {
                    case 1:
                        back_onButtonClicked(this);
                        break;
                    default:
                        break;
                    };
                    break;
                default:
                    break;
                }
                });
            addChild(temp_btn, layer);

            return temp_btn;
        };

    /************     参数     ************/

    const Vec2 po_bg(visibleSize / 2);     //地图位置
    const Vec2 po_bg_bottom(1000, 150);    //bg_bottom位置
    constexpr float btn_scale = 1.1f;      //按钮放大倍率
    constexpr float map_scale = 1.5f;      //地图放大倍率
    const Vec2 po_btn_home(360, 920);      //home按钮位置
    const Vec2 po_options(750, 922);          //column_options位置
    const Vec2 po_statistics(980, 920);       //column_statistics位置
    const Vec2 po_producer(1190, 925);        //column_producer位置
    const Vec2 po_adventure_mode(550, 480);     //音效 字幕位置 
    const Vec2 po_hide_levels(980, 480);     //BGM 字幕位置
    const Vec2 po_boss_mode(1400, 480);    //BOSS模式 字幕位置 
    const Vec2 po_all_items(757, 412);       //摧毁道具 字幕位置 
    const Vec2 po_all_money(550, 480);     //总钱数 字幕位置 
    const Vec2 po_all_monsters(980, 480);     //打败怪物数目 字幕位置
    const Vec2 po_all_bosses(1400, 480);    //打败BOSS数目 字幕位置 
    const Vec2 po_all_items(757, 412);       //摧毁道具 字幕位置 
    const Vec2 po_map_1(757, 350);       //冒险地图数目 字幕位置 
    const Vec2 po_map_2(1177, 412);      //隐藏地图数目 字幕位置 
    const Vec2 po_map_3(1177, 350);      //BOSS地图数目 字幕位置 

    /**************************************/

    /********** 创建精灵 **********/
    /* 创建背景 */
    auto bg = sp_create("optionBG2.png", po_bg, map_scale, -1);
    /* 创建可点击对象 */
    auto options = sp_create("statistics_pressed.png", po_options, map_scale, 0);
    options->setName("options");
    auto statistics = sp_create("statistics_normal.png", po_statistics, 2.3, 0);
    auto producer = sp_create("producer_normal.png", po_producer, 2.2, 0);
    producer->setName("producer");
    /* 创建字幕 */
    auto adventure_mode = sp_create("adventure_mode.png", po_adventure_mode, map_scale, 1);
    auto hide_levels = sp_create("hide_levels.png", po_hide_levels, map_scale, 1);
    auto boss_mode = sp_create("boss_mode.png", po_boss_mode, map_scale, 1);
    auto all_money = sp_create("all_money.png", po_all_money, map_scale, 1);
    auto all_monsters = sp_create("all_monsters.png", po_all_monsters, map_scale, 1);
    auto all_bosses = sp_create("all_bosses.png", po_all_bosses, map_scale, 1);
    auto all_items = sp_create("all_items.png", po_all_items, map_scale, 1);
    auto map_1 = sp_create("option_map.png", po_map_1, map_scale, 1);
    auto map_2 = sp_create("option_map.png", po_map_2, map_scale, 1);
    auto map_3 = sp_create("option_map.png", po_map_3, map_scale, 1);

    /********** 创建按钮 **********/
    /* 返回 */
    auto btn_back = btn_create(
        "OptionScene_1/contents/option_1_back_normal.png",
        "OptionScene_1/contents/option_1_back_pressed.png",
        "OptionScene_1/contents/option_1_back_normal.png",
        po_btn_home, 3);

    /********** 创建事件 **********/
    /* options */
    auto options_click_listener = EventListenerTouchOneByOne::create();
    options_click_listener->onTouchBegan = [&](Touch* touch, Event* event) {
        auto pos = touch->getLocation();    //获取点击位置
        auto sp = (Sprite*)(this->getChildByName("options"));    //从场景中抓取名为help的精灵
        if (sp->getBoundingBox().containsPoint(pos))
            return true;    //点击位置在精灵范围内
        return false;   //返回false，中止执行事件响应
        };
    options_click_listener->onTouchMoved = [](Touch* touch, Event* event) {};
    options_click_listener->onTouchEnded = [&](Touch* touch, Event* event) {
        auto next = OptionScene_1::create_Scene();
        if (next == nullptr)
            return false;   //确保next非空
        Director::getInstance()->replaceScene(next);
        return true;
        };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(options_click_listener, this);

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

    return true;
}