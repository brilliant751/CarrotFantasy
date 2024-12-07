
#include "StartScene.h"
#include "EnterScene.h"
#include "MapChoose.h"
#include "HelpScene_1.h"
#include "HelpScene_2.h"
#include "HelpScene_3.h"
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
Scene* HelpScene_3::create_Scene()
{
    return HelpScene_3::create();
}

/* 左键按钮切换上一张picture */
void HelpScene_3::left_onButtonClicked(Ref* sender) {
    if (page > 1) {
        --page;
        picture->setSpriteFrame(picture_url[page]);
        page_left->setSpriteFrame(num_url[page]);
    }
}

/* 右键按钮切换下一张picture */
void HelpScene_3::right_onButtonClicked(Ref* sender) {
    if (page < 10) {
        ++page;
        picture->setSpriteFrame(picture_url[page]);       
        page_left->setSpriteFrame(num_url[page]);
    }
}

/* 返回按钮切换至StartScene */
void HelpScene_3::back_onButtonClicked(Ref* sender) {
    auto next = StartScene::create_Scene();
    Director::getInstance()->popScene();
}

/* 场景初始化 */
bool HelpScene_3::init()
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
    //                         1 - left
    //                         2 - right
    //                         3 - home
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
                                left_onButtonClicked(this);
                                break;
                            case 2:
                                right_onButtonClicked(this);
                                break;
                            case 3:
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
    const Vec2 po_btn_back(360, 920);      //home按钮位置
    const Vec2 po_help(750, 922);          //column_help位置
    const Vec2 po_monster(980, 920);       //column monster位置
    const Vec2 po_tower(1190, 923);        //column_tower位置
    const Vec2 po_page_left(955, 150);     //页数左位置
    const Vec2 po_page_middle(980, 150);   //页数中位置
    const Vec2 po_page_right(1005, 150);   //页数右位置
    const Vec2 po_btn_left(450, 540);      //左移按钮位置
    const Vec2 po_btn_right(1510, 540);    //右移按钮位置

    /**************************************/

    /********** 创建精灵 **********/
    /* 创建背景 */
    auto bg = sp_create("help_bg.png", po_bg, map_scale, -1);
    auto bg_bottom = sp_create("bg_bottom.png", po_bg_bottom, map_scale, 0);
    /* 创建动态图案 */
    picture = sp_create(picture_url[page], po_bg, map_scale, 0);
    page_left = sp_create(num_url[page], po_page_left, 1.9, 1);
    /* 创建可点击对象 */
    auto help = sp_create("column_help_normal.png", po_help, 2.3, 0);
    help->setName("help");
    auto monster = sp_create("column_monster_normal.png", po_monster, 2.3, 0);
    monster->setName("monster");
    auto tower = sp_create("column_tower_pressed.png", po_tower,map_scale, 0);
    /* 创建页码 */
    auto page_middle = sp_create(num_url[0], po_page_middle, 1.9, 1);
    auto page_right = sp_create(num_url[10], po_page_right, 1.9, 1);


    /********** 创建按钮 **********/
    /* 左移 */
    auto btn_left = btn_create(
        "HelpScene/contents/btn_help_left_normal.png",
        "HelpScene/contents/btn_help_left_pressed.png",
        "HelpScene/contents/btn_help_left_normal.png",
        po_btn_left, 1, 0.7);
    /* 右移 */
    auto btn_right = btn_create(
        "HelpScene/contents/btn_help_right_normal.png",
        "HelpScene/contents/btn_help_right_pressed.png",
        "HelpScene/contents/btn_help_right_normal.png",
        po_btn_right, 2, 0.7);
    /* 返回 */
    auto btn_back = btn_create(
        "HelpScene/contents/btn_back_normal.png",
        "HelpScene/contents/btn_back_pressed.png",
        "HelpScene/contents/btn_back_normal.png",
        po_btn_back, 3);

    /********** 创建事件 **********/
    /* help */
    auto help_click_listener = EventListenerTouchOneByOne::create();
    help_click_listener->onTouchBegan = [&](Touch* touch, Event* event) {
        auto pos = touch->getLocation();    //获取点击位置
        auto sp = (Sprite*)(this->getChildByName("help"));    //从场景中抓取名为help的精灵
        if (sp->getBoundingBox().containsPoint(pos))
            return true;    //点击位置在精灵范围内
        return false;   //返回false，中止执行事件响应
        };
    help_click_listener->onTouchMoved = [](Touch* touch, Event* event) {};
    help_click_listener->onTouchEnded = [&](Touch* touch, Event* event) {
        auto next = HelpScene_1::create_Scene();
        if (next == nullptr)
            return false;   //确保next非空
        Director::getInstance()->replaceScene(next);
        return true;
        };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(help_click_listener, this);
    
    /* monster */
    auto monster_click_listener = EventListenerTouchOneByOne::create();
    monster_click_listener->onTouchBegan = [&](Touch* touch, Event* event) {
        auto pos = touch->getLocation();    //获取点击位置
        auto sp = (Sprite*)(this->getChildByName("monster"));    //从场景中抓取名为monster的精灵
        if (sp->getBoundingBox().containsPoint(pos))
            return true;    //点击位置在精灵范围内
        return false;   //返回false，中止执行事件响应
        };
    monster_click_listener->onTouchMoved = [](Touch* touch, Event* event) {};
    monster_click_listener->onTouchEnded = [&](Touch* touch, Event* event) {
        auto next = HelpScene_2::create_Scene();
        if (next == nullptr)
            return false;   //确保next非空
        Director::getInstance()->replaceScene(next);
        return true;
        };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(monster_click_listener, this);

    

    return true;
}