
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
Scene* OptionScene_3::create_Scene()
{
    return OptionScene_3::create();
}

/* 返回按钮切换至StartScene */
void OptionScene_3::back_onButtonClicked(Ref* sender) {
    auto next = StartScene::create_Scene();
    Director::getInstance()->popScene();
}

/* 场景初始化 */
bool OptionScene_3::init()
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


    constexpr int btnY1 = 800;              //大按钮高度
    constexpr int btnY2 = 280;              //小按钮高度
    constexpr float btn_scale = 1.5f;       //按钮放大倍率
    constexpr float map_scale = 1.5f;      //地图放大倍率
    const Vec2 po_btn_home(400, 750);      //home按钮位置
    const Vec2 po_bg(visibleSize / 2);     //地图位置
    const Vec2 po_options(600, btnY1);          //column_options位置
    const Vec2 po_statistics(820, btnY1);       //column_statistics位置
    const Vec2 po_producer(1040, btnY1);        //column_producer位置

    /**************************************/

    /********** 创建精灵 **********/
    /* 创建背景 */
    auto bg = sp_create("optionBG3.png", po_bg, map_scale, -1);
    /* 创建可点击对象 */
    auto options = sp_create("options_normal.png", po_options, 2.3, 0);
    options->setName("options");
    auto statistics = sp_create("statistics_normal.png", po_statistics, 2.3, 0);
    statistics->setName("statistics");
    auto producer = sp_create("producer_pressed.png", po_producer, map_scale, 0);

    /********** 创建按钮 **********/
    /* 返回 */
    auto btn_back = btn_create(
        "OptionScene/contents/option_1_back_normal.png",
        "OptionScene/contents/option_1_back_pressed.png",
        "OptionScene/contents/option_1_back_normal.png",
        po_btn_home, 1);

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

    return true;
}