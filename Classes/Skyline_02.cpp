#pragma execution_character_set("utf-8")
#include "StartScene.h"
#include "EnterScene.h"
#include "Skyline_02.h"
#include "GameMenu.h"
#include "AudioEngine.h"
#include "ui/CocosGUI.h"
#include "ui/UIButton.h"

USING_NS_CC;
using namespace ui;
using namespace std;

#define GR_LEN 95   //方格边长

/********** 坐标线位置 **********/
// 地图大小为 12 * 8 个方格
constexpr int mapX[13] = { 0, 95, 190, 285, 380, 475, 570, 665, 760, 855, 950, 1045, 1140 };
constexpr int mapY[9] = { 0, 95, 190, 285, 380, 475, 570, 665, 760 };
/********************************/

/* 创建场景 */
Scene* Map_1_02::create_Scene()
{
    return Map_1_02::create();
}

/* 初始化场景 */
bool Map_1_02::init()
{
    if (!Scene::init())
        return false;

    const Vec2 origin = Vec2(240, 100); //地图坐标起点
    auto visibleSize = Director::getInstance()->getVisibleSize();   //(1620,960)

    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Levels/1-02/1_02.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Levels/Barriers/Barriers.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Levels/Carrot/Carrot.plist");

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

    /* 创建文本的闭包函数 */
    //lambda表达式
    //int num/string text：     文本数字/文本内容
    //ttf：      字体文件名
    //size：     字体大小
    //pos：      坐标
    //layer：    放置层数
    //color:     颜色分类：
    //                    0 - 白色
    //                    1 - 土黄
    auto lb_create1 = [&](const int num, const string& ttf, const int size, const Vec2& pos, int layer = 0, int color = 0) {
        string text = to_string(num);
        auto myLabel = Label::createWithTTF(text, ttf, size);
        myLabel->setPosition(pos);
        myLabel->enableBold();
        if (color == 1)
            myLabel->setColor(Color3B(255, 246, 143));
        this->addChild(myLabel, layer);
        return myLabel;
        };

    auto lb_create2 = [&](const string text, const string& ttf, const int size, const Vec2& pos, int layer = 0, int color = 0) {
        auto myLabel = Label::createWithTTF(text, ttf, size);
        myLabel->setPosition(pos);
        myLabel->enableBold();
        if (color == 1)
            myLabel->setColor(Color3B(255, 246, 143));
        this->addChild(myLabel, layer);
        return myLabel;
        };


    /************     参数     ************/

    constexpr int topY = 814;               //顶部高度
    constexpr float btn_scale = 1.4f;       //按钮放大倍率
    constexpr float map_scale = 1.5f;       //地图放大倍率
    constexpr float word_scale = 2.0f;      //文字放大倍率
    const Vec2 bg(visibleSize / 2);         //地图位置
    const Vec2 topbg(810, topY);            //顶部位置
    const Vec2 gmmenu(1270, topY);          //菜单位置
    const Vec2 gmpause(1180, topY);         //暂停位置
    const Vec2 spd(1070, topY);             //倍速位置
    const Vec2 po_bg_waves(740, topY + 10);  //waves框位置
    const Vec2 po_waves_left(715, topY + 10);  //waves_left位置
    const Vec2 po_waves_right(765, topY + 10);  //waves_right位置
    const Vec2 po_chp_bg(origin.x + mapX[8]+30, origin.y + mapY[2]-10);   //萝卜血条底图位置
    const Vec2 po_chp_num(origin.x + mapX[8]+45, origin.y + mapY[2]-10);  //萝卜血条数字位置
    const Vec2 po_lb_total_waves(880, topY + 10);           //共几波位置
    const Vec2 crt(origin.x+mapX[7]+(mapX[1])/2.0f, origin.y + mapY[2]);             //萝卜位置
    const Vec2 born(origin.x + mapX[9]/2.0f, origin.y + (mapY[5]+mapY[6])/2.0f); //怪物出生点
    /* 障碍物位置 */
    const Vec2 planet_1(origin.x + (mapX[4] + mapX[3]) / 2.0f, origin.y + (mapY[4] + mapY[1]) / 2.0f);
    const Vec2 planet_2(origin.x + (mapX[8] + mapX[9]) / 2.0f, origin.y + (mapY[4] + mapY[5]) / 2.0f);
    const Vec2 planet_3(origin.x + (mapX[11]+mapX[10])/2.0f , origin.y + (mapY[6] + mapY[5]) / 2.0f);
    const Vec2 planet_4(origin.x + (mapX[4] + mapX[5]) / 2.0f, origin.y + (mapY[4] + mapY[5]) / 2.0f);
    const Vec2 balloon(origin.x + mapX[11], origin.y + mapY[4]);
    const Vec2 trees(origin.x + mapX[5] / 2.0f, origin.y + (mapY[6] + mapY[5]) / 2.0f);
    const Vec2 cloud_1(origin.x + (mapX[7] + mapX[6]) / 2.0f, origin.y + (mapY[4] + mapY[5]) / 2.0f);
    const Vec2 cloud_2(origin.x + (mapX[5] + mapX[6]) / 2.0f, origin.y + mapY[5] / 2.0f);
    const Vec2 rainbow(origin.x + (mapX[2]) / 2.0f, origin.y + (mapY[4] + mapY[1]) / 2.0f);

    /**************************************/

    /*********** 创建精灵 **********/
    /* 创建背景 */
    auto map_bg_02 = sp_create("1_02_bg.png", bg, map_scale, -2);

    /* 创建萝卜 */
    auto carrot_02 = sp_create("HP_MAX.PNG", crt, map_scale, 0);

    /* 创建萝卜血条底图 */
    auto chp_bg = sp_create("Hp.png", po_chp_bg, map_scale, 0);

    /* 创建顶部状态栏 */
    auto top_bg_02 = sp_create("top_bg02.png", topbg, map_scale, -1);

    /* 创建暂停中显示 */
   // auto pausing_02 = sp_create("paused_02.png", topbg, word_scale, 0);

    /* 创建怪物出生点 */
    auto start_point_02 = sp_create("start_point02.png", born, map_scale, 0);

    /* 创建倍速键 */
    auto spd_shift_02 = sp_create("game_speed_1_02.png", spd, map_scale, 0);
    spd_shift_02->setName("spd_shift_02");

    /* 创建障碍物 */
    auto planet1 = sp_create("Barrier_One_1.png", planet_1, map_scale, 0);
    auto planet2 = sp_create("Barrier_One_1.png", planet_2, map_scale, 0);
    auto planet3 = sp_create("Barrier_One_1.png", planet_3, map_scale, 0);
    auto planet4 = sp_create("Barrier_One_1.png", planet_4, map_scale, 0);
    auto _balloon = sp_create("Barrier_Four_1.png", balloon, map_scale, 0);
    auto _trees = sp_create("Barrier_Four_2.png", trees, map_scale, 0);
    auto _cloud1 = sp_create("Barrier_One_2.png", cloud_1, map_scale, 0);
    auto _cloud2 = sp_create("Barrier_One_2.png", cloud_2, map_scale, 0);
    auto _rainbow = sp_create("Barrier_Two_1.png", rainbow, map_scale, 0);

    /* waves框 */
    auto bg_waves = sp_create("game)waves02.png", po_bg_waves, map_scale, 0);

    /*********** 创建标签 ***********/
    /* 创建萝卜血条数字 */
    auto chp_num = lb_create1(c_hp, "fonts/HPSimplified_Bd.ttf", 27, po_chp_num, 1);

    /* 创建total_waves */
    auto lb_total_waves = lb_create2("/20波怪物", "fonts/方正粗黑宋简体.ttf", 34, po_lb_total_waves, 2);

    /* 创建waves十位 */
    auto waves_left = lb_create1(waves / 10, "fonts/方正粗黑宋简体.ttf", 34, po_waves_left, 2, 1);

    /* 创建waves个位 */
    auto waves_right = lb_create1(waves % 10, "fonts/方正粗黑宋简体.ttf", 34, po_waves_right, 2, 1);




    /*********** 创建按钮 **********/
     /* 创建菜单 */
    auto game_menu = btn_create(
        "Levels/btn/gamemenu_btn_normal.png",
        "Levels/btn/gamemenu_btn_pressed.png",
        gmmenu, btn_scale, 0);
    game_menu->setName("Menu");
    game_menu->addTouchEventListener([this, v_size = visibleSize](Ref* sender, Widget::TouchEventType type) {
        auto menu_layer = PauseMenu::create_Layer();    //创建弹出菜单
        auto menu = (Button*)(this->getChildByName("Menu"));
        /* 创建调暗层 */
        auto dimlayer = LayerColor::create(Color4B(0, 0, 0, 128), v_size.width, v_size.height);
        dimlayer->setName("dimmer");
        switch (type)
        {
        case ui::Widget::TouchEventType::BEGAN:
            break;
        case ui::Widget::TouchEventType::ENDED:
            this->addChild(menu_layer, 10);
            this->addChild(dimlayer, 9);
            /* 暂停主场景的监听事件 */
            //此处会循环暂停所有child结点的监听事件
            this->getEventDispatcher()->pauseEventListenersForTarget(this, true);
            /* 恢复弹窗层的监听事件 */
            this->getEventDispatcher()->resumeEventListenersForTarget(menu_layer, true);
            break;
        default:
            break;
        }
        });

    /* 创建暂停键 */
    auto game_pause = btn_create(
        "Levels/btn/game_pause.png",
        "Levels/btn/game_pause.png",
        gmpause, btn_scale, 0);
    game_pause->setName("game_pause");
    game_pause->addTouchEventListener([this, v_size = visibleSize](Ref* sender, Widget::TouchEventType type) {
        auto btn = (Button*)(this->getChildByName("game_pause"));
        switch (type)
        {
        case ui::Widget::TouchEventType::BEGAN:
            break;
        case ui::Widget::TouchEventType::ENDED:
            if (is_pause == 0) {
                btn->loadTextures("Levels/btn/game_continue_normal.png",
                    "Levels/btn/game_continue_pressed.png",
                    "Levels/btn/game_continue_normal.png");
                is_pause = 1;
                //todo:暂停状态
            }
            else {
                btn->loadTextures("Levels/btn/game_pause.png",
                    "Levels/btn/game_pause.png",
                    "Levels/btn/game_pause.png");
                is_pause = 0;
                //todo:开始状态
            }
            break;
        default:
            break;
        }
        });


    /* 创建事件 */
    /* spd */
    auto spd_click_listener = EventListenerTouchOneByOne::create();
    spd_click_listener->onTouchBegan = [&](Touch* touch, Event* event) {
        auto pos = touch->getLocation();
        auto sp = (Sprite*)(this->getChildByName("spd_shift_02"));
        if (sp->getBoundingBox().containsPoint(pos))
            return true;
        return false;
        };
    spd_click_listener->onTouchMoved = [](Touch* touch, Event* event) {};
    spd_click_listener->onTouchEnded = [&](Touch* touch, Event* event) {
        auto sp = (Sprite*)(this->getChildByName("spd_shift_02"));
        if (speed == 1) {
            sp->setSpriteFrame("game_speed_2_02.png");
            speed = 2;
        }
        else {
            sp->setSpriteFrame("game_speed_1_02.png");
            speed = 1;
        }
        };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(spd_click_listener, this);















    /* 创建倒计时 */
  /*  auto count = CountDown::create_Layer();
    this->addChild(count, 10);*/



    return true;
}