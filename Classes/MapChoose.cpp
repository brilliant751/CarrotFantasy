
#include "EnterScene.h"
#include "Skyline_01.h"
#include "MapChoose.h"
#include "HelpScene_1.h"
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

Scene* MapChoose::create_Scene()
{
    return MapChoose::create();
}

/* 左键按钮切换上一张map */
void MapChoose::left_onButtonClicked(Ref* sender) {
    if (level > 0) {
        cur_map->setSpriteFrame(all_map[--level].map_url);
        towers->setSpriteFrame(all_map[level].towers_url);
        waves->setSpriteFrame(all_map[level].waves_url);
        if (is_open[level]) {
            map_lock->setZOrder(-1);            
            btn_start->setEnabled(true);   

        }
        else {
            map_lock->setZOrder(1);            
            btn_start->setEnabled(false);
        }
    }
}

/* 右键按钮切换下一张map */
void MapChoose::right_onButtonClicked(Ref* sender) {
    if (level < 2) {
        cur_map->setSpriteFrame(all_map[++level].map_url);    
        towers->setSpriteFrame(all_map[level].towers_url);
        waves->setSpriteFrame(all_map[level].waves_url);
        if (is_open[level]) {
            map_lock->setZOrder(-1);          
            btn_start->setEnabled(true);
        }
        else {
            map_lock->setZOrder(1);           
            btn_start->setEnabled(false);
        }
    }
}

/* 帮助按钮切换至HelpScene_1 */
void MapChoose::help_onButtonClicked(Ref* sender) {
    auto next = HelpScene_1::create_Scene();
    Director::getInstance()->pushScene(next);
}

/* 返回按钮返回到EnterScene */
void MapChoose::back_onButtonClicked(Ref* sender) {
    Director::getInstance()->popScene();
}

/* 开始按钮进入到第一关 */
void MapChoose::start_onButtonClicked(Ref* sender) {
    auto next = Map_1_01::create_Scene();
    Director::getInstance()->pushScene(next);
}

bool MapChoose::init()
{
    if (!Scene::init())
        return false;
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("MapChoose/MapChoose.plist");

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
    //                         1 - back
    //                         2 - help
    //                         3 - start
    //                         4 - left
    //                         5 - right
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
                                back_onButtonClicked(this);     //回到EnterScene
                                break;
                            case 2: 
                                help_onButtonClicked(this);     //进入help
                                break;
                            case 3:
                                start_onButtonClicked(this);    //开始游戏
                                break;
                            case 4:
                                left_onButtonClicked(this);     //左移
                                break;
                            case 5:
                                right_onButtonClicked(this);    //右移
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

    const Vec2 po_bg(visibleSize / 2);      //底图位置
    const Vec2 po_map(visibleSize / 2);     //地图位置
    const Vec2 po_towers(810, 217);        //可用防御塔位置
    const Vec2 po_waves(980, 720);         //波次位置
    constexpr float btn_scale = 1.2f;       //按钮放大倍率
    constexpr float map_scale = 1.5f;       //地图放大倍率
    const Vec2 po_bg_left(408, 190);        //左下背景位置
    const Vec2 po_bg_right(1225, 190);      //右下背景位置
    const Vec2 po_btn_back(275, 820);      //返回按钮位置
    const Vec2 po_btn_help(1345, 820);     //帮助按钮位置
    const Vec2 po_btn_start(810, 150);     //开始按钮位置
    const Vec2 po_btn_left(300, 480);       //左移按钮位置
    const Vec2 po_btn_right(1320, 480);     //右移按钮位置
    const Vec2 po_lock(990, 380);


    /**************************************/

    /* 创建背景 */
    auto bg = sp_create("bg.png", po_bg, map_scale, -1);
    auto bg_left = sp_create("bg_left.png", po_bg_left, map_scale, 0);
    auto bg_right = sp_create("bg_right.png", po_bg_right, map_scale, 0);

    

    /* 定义cur_map towers waves lock*/
    cur_map = sp_create(all_map[level].map_url, po_map, 1.7, 0);
    cur_map->setName("map");
    towers = sp_create(all_map[level].towers_url, po_towers, map_scale, 0);
    waves = sp_create(all_map[level].waves_url, po_waves, map_scale, 0);
    map_lock = sp_create("map_lock.png", po_lock, map_scale, -1);

    /* 创建按钮 */
    //返回
    auto btn_back = btn_create(
        "MapChoose/contents/btn_back_normal.png",
        "MapChoose/contents/btn_back_pressed.png",
        "MapChoose/contents/btn_back_normal.png",
        po_btn_back, 1, 1.2);
    //帮助
    auto btn_help = btn_create(
        "MapChoose/contents/btn_help_normal.png",
        "MapChoose/contents/btn_help_pressed.png",
        "MapChoose/contents/btn_help_normal.png",
        po_btn_help, 2, 1.2);
    //开始
    btn_start = btn_create(
        "MapChoose/contents/btn_start_normal.png",
        "MapChoose/contents/btn_start_pressed.png",
        "MapChoose/contents/btn_start_locked.png",
        po_btn_start, 3);
    //左移
    auto btn_left = btn_create(
        "MapChoose/contents/btn_left_normal.png",
        "MapChoose/contents/btn_left_pressed.png",
        "MapChoose/contents/btn_left_normal.png",
        po_btn_left, 4);
    //右移
    auto btn_right = btn_create(
        "MapChoose/contents/btn_right_normal.png",
        "MapChoose/contents/btn_right_pressed.png",
        "MapChoose/contents/btn_right_normal.png",
        po_btn_right, 5);

    /* 创建事件 */
    auto map_click_listener = EventListenerTouchOneByOne::create();
    map_click_listener->onTouchBegan = [&](Touch* touch, Event* event) {
        if (!is_open[level])
            return false;
        auto pos = touch->getLocation();
        auto sp = (Sprite*)(this->getChildByName("map"));
        if (sp->getBoundingBox().containsPoint(pos))
            return true;
        return false;
        };
    map_click_listener->onTouchMoved = [](Touch* touch, Event* event) {};
    map_click_listener->onTouchEnded = [&](Touch* touch, Event* event) {
        this->start_onButtonClicked(this);
        };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(map_click_listener, this);
    
   


    return true;
}