﻿#pragma execution_character_set("utf-8")
#include <cmath>
#include <iostream>
#include "StartScene.h"
#include "EnterScene.h"
#include "Skyline_01.h"
#include "GameMenu.h"
#include "AudioEngine.h"
#include "ui/CocosGUI.h"
#include "ui/UIButton.h"
#include "monsters.h"
#include "Monster_info.h"
#include "Towers_info.h"
#include "Towers.h"
#include "tools.h"

USING_NS_CC;
using namespace ui;
using namespace std;

#define GR_LEN 95   //方格边长
int map_clicked_1 = 0;//状态 0 之前还未点击 1 之前已经点击了一个可建造的位置 2 之前已经点击了一个防御塔
int tag1_1;
int tag1_2;

/********** 坐标线位置 **********/
// 地图大小为 12 * 8 个方格
constexpr int mapX[13] = { 0, 95, 190, 285, 380, 475, 570, 665, 760, 855, 950, 1045, 1140 };
constexpr int mapY[9] = { 0, 95, 190, 285, 380, 475, 570, 665, 760 };
/********************************/

bool is_stop = false;   //标记游戏是否暂停（菜单用）
int speed;      //游戏倍速

// 记录地图位置占用情况
//-1无响应 0可建造位置 1不可建造位置 2障碍物 3防御塔 
int occupy_1[8][12] = {
    -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
    0,0,0,2,2,2,2,2,2,0,0,0,
    0,1,0,2,2,2,2,2,2,0,1,1,
    0,1,0,0,2,0,0,2,0,0,1,0,
    0,1,2,0,1,1,1,1,0,2,1,0,
    0,1,1,1,1,2,2,1,1,1,1,0,
    0,0,0,0,0,0,0,0,0,0,0,0,
    1,1,0,0,0,0,0,0,0,0,1,1
};

// 怪物行走路线
const Vec2 path[] = {
        Vec2(origin.x + (mapX[1] + mapX[2]) / 2.0f, origin.y + (mapY[5] + mapY[6]) / 2.0f),
        Vec2(origin.x + (mapX[1] + mapX[2]) / 2.0f, origin.y + (mapY[2] + mapY[3]) / 2.0f),
        Vec2(origin.x + (mapX[4] + mapX[5]) / 2.0f, origin.y + (mapY[2] + mapY[3]) / 2.0f),
        Vec2(origin.x + (mapX[4] + mapX[5]) / 2.0f, origin.y + (mapY[3] + mapY[4]) / 2.0f),
        Vec2(origin.x + (mapX[7] + mapX[8]) / 2.0f, origin.y + (mapY[3] + mapY[4]) / 2.0f),
        Vec2(origin.x + (mapX[7] + mapX[8]) / 2.0f, origin.y + (mapY[2] + mapY[3]) / 2.0f),
        Vec2(origin.x + (mapX[10] + mapX[11]) / 2.0f, origin.y + (mapY[2] + mapY[3]) / 2.0f),
        Vec2(origin.x + (mapX[10] + mapX[11]) / 2.0f, origin.y + (mapY[5] + mapY[6]) / 2.0f),
        };
const int top = 8; //栈顶位置

/* 生成怪物 */
void Map_1_01::create_monster(float dt)
{
    if (get_tag_waves(mons_tag) != waves)
        update_tag(mons_tag, waves);
    if (mons_tag % 100 > 5)
        return;
    auto mon1 = Monster::create_Monster(PUPIL_1);
    mon1->setSpriteFrame(mons_url[waves]);
    mon1->setPosition(path[0]);
    mon1->setScale(mons_scale);
    mon1->setAnchorPoint(Vec2(0.5, 0));
    mon1->setTag(mons_tag++);
    mon1->set_route(path, top);
    addChild(mon1, 2);
    mon1->scheduleUpdate(); //实现按路径移动
}


//type 0 bottle
//     1 shit
//     2 fan
void Map_1_01::create_tower(int type, Vec2 po, int line, int row) {
    auto tower = Tower::create();
    tower->setType(towers[type]);

}

/* 建造防御塔按钮刷新 */
void Map_1_01::update_create(float dt) {
    auto sp1 = this->getChildByName<Sprite*>("create_bottle");
    auto sp2 = this->getChildByName<Sprite*>("create_shit");
    if (money >= 100)
        sp1->setSpriteFrame("bottle_yes_create.png");
    else
        sp1->setSpriteFrame("bottle_no_create.png");
    if (money >= 120)
        sp2->setSpriteFrame("shit_yes_create.png");
    else
        sp2->setSpriteFrame("shit_no_create.png");
}

/* 金币数量刷新 */
void Map_1_01::update_money(float dt) {
    auto label = this->getChildByName<Label*>("lb_money");
    string num = to_string(money);
    label->setString(num);
}


/* 创建场景 */
Scene* Map_1_01::create_Scene()
{
	return Map_1_01::create();
}

/* 初始化场景 */
bool Map_1_01::init()
{
	if (!Scene::init())
		return false;

    /* 初始化全局变量 */
    is_stop = false;
    //rt = 1;
    speed = 1;

    /* 初始化句柄 */
    //引入图集
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Levels/Barriers/Barriers.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Levels/Carrot/Carrot.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Levels/tower_click/tower_click.plist");

    //设置60帧
    Director::getInstance()->setAnimationInterval(1.0f / 60.0f);

    /* 初始化局部变量 */
	auto visibleSize = Director::getInstance()->getVisibleSize();   //(1620,960)

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
    //                    2 - 深褐色
    auto lb_create1 = [&](const int num, const string& ttf, const int size, const Vec2& pos, int layer = 0, int color = 0) {
        string text = to_string(num);
        auto myLabel = Label::createWithTTF(text, ttf, size);
        myLabel->setPosition(pos);
        myLabel->enableBold();
        if (color == 1)
            myLabel->setColor(Color3B(255, 246, 143));
        else if (color == 2)
            myLabel->setColor(Color3B(157, 99, 13));

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
    const Vec2 crt(1250, origin.y + mapY[6]);              //萝卜位置
    const Vec2 po_chp_bg(1330, origin.y + mapY[6] - 10);   //萝卜血条底图位置
    const Vec2 po_chp_num(1343, origin.y + mapY[6] - 10);  //萝卜血条数字位置
    const Vec2 po_lb_total_waves(880, topY + 10);           //共几波位置
    const Vec2 po_lb_money(390, topY + 10);           //金币位置
    const Vec2 born(origin.x + (mapX[1] + mapX[2]) / 2.0f, origin.y + mapY[6]); //怪物出生点
    /* 障碍物位置 */
    const Vec2 brr1_1(origin.x + (mapX[4] + mapX[5]) / 2.0f, origin.y + (mapY[4] + mapY[5]) / 2.0f);
    const Vec2 brr1_2(origin.x + (mapX[7] + mapX[8]) / 2.0f, origin.y + (mapY[4] + mapY[5]) / 2.0f);
    const Vec2 brr1_3(origin.x + (mapX[2] + mapX[3]) / 2.0f, origin.y + (mapY[3] + mapY[4]) / 2.0f);
    const Vec2 brr1_4(origin.x + (mapX[9] + mapX[10]) / 2.0f, origin.y + (mapY[3] + mapY[4]) / 2.0f);
    const Vec2 brr2_1(origin.x + mapX[6], origin.y + (mapY[2] + mapY[3]) / 2.0f);
    const Vec2 brr4_1(origin.x + mapX[6], origin.y + mapY[6]);
    const Vec2 brr4_2(origin.x + mapX[4], origin.y + mapY[6]);
    const Vec2 brr4_3(origin.x + mapX[8], origin.y + mapY[6]);
    /* 怪物位置 */
    
   

    /**************************************/

    
    
    

    /*********** 创建精灵 **********/
    /* 创建背景 */
    auto map_bg = sp_create("1-01_bg.png", bg, map_scale, -2);

    /* 创建萝卜 */
    auto carrot = sp_create("HP_MAX.PNG", crt, map_scale, 0);

    /* 创建萝卜血条底图 */
    auto chp_bg = sp_create("Hp.png", po_chp_bg, map_scale, 0);

    /* 创建顶部状态栏 */
    auto top_bg = sp_create("top_bg.png", topbg, map_scale, -1);

    /* 创建暂停中显示 */
    auto pausing = sp_create("paused.png", topbg, word_scale, -2);
    pausing->setName("pausing");

    /* 创建怪物出生点 */
    auto start_point = sp_create("start_point.png", born, map_scale, 0);

    /* 创建倍速键 */
    auto spd_shift = sp_create("game_speed_1.png", spd, map_scale, 0);
    spd_shift->setName("spd_shift");

    /* waves框 */
    auto bg_waves = sp_create("game)waves.png", po_bg_waves, map_scale, 0);
    bg_waves->setName("bgwaves");

    /* 创建点击格子 + 不可点击格子 */
    for (int i = 1; i < 8; i++)
        for (int j = 0; j < 12; j++) {
            Vec2 po = get_po(i, j);
            if (occupy_1[i][j] == 0) {
                auto sp1 = sp_create("start_sprite.png", po, map_scale, -10);
                sp1->setTag(i * 12 + j);
                auto sp2 = sp_create("grid.png", po, map_scale, -10);
                sp2->setTag(96 + i * 12 + j);
            }
            else if (occupy_1[i][j] == 1) {
                auto sp = sp_create("cant_build.png", po, map_scale, 2);
                sp->setTag(192 + i * 12 + j);
                sp->setOpacity(0);
            }
        }

    /* 创建 建造bottle 精灵 */
    auto create_bottle = sp_create("bottle_no_create.png", bg, map_scale, -10);
    create_bottle->setName("create_bottle");

    /* 创建 建造shit 精灵 */
    auto create_shit = sp_create("shit_no_create.png", bg, map_scale, -10);
    create_shit->setName("create_shit");

    /* 创建 攻击范围 精灵 */
    auto atk_range = sp_create("range.png", bg, 2, -10);//自身一倍是1.5个格子
    atk_range->setName("atk_range");

    /* 创建 升级 精灵 */
    auto up_level = sp_create("no_up.png", bg, map_scale, -10);
    up_level->setName("up_level");

    /* 创建 出售 精灵 */
    auto sell = sp_create("sell.png", bg, map_scale, -10);
    sell->setName("sell");

    this->schedule(schedule_selector(Map_1_01::update_create), 0.1f);
    this->schedule(schedule_selector(Map_1_01::update_money), 0.1f);



    /*********** 创建标签 ***********/
    /* 创建萝卜血条数字 */
    auto chp_num = lb_create1(c_hp, "fonts/HPSimplified_Bd.ttf", 27, po_chp_num, 1);

    /* 创建total_waves */
    auto lb_total_waves = lb_create2("/15波怪物", "fonts/方正粗黑宋简体.ttf", 34, po_lb_total_waves, 2);
    lb_total_waves->setName("totalwaves");

    /* 创建waves十位 */
    auto waves_left = lb_create1(waves / 10, "fonts/方正粗黑宋简体.ttf", 34, po_waves_left, 2, 1);
    waves_left->setName("wavesleft");

    /* 创建waves个位 */
    auto waves_right = lb_create1(waves % 10, "fonts/方正粗黑宋简体.ttf", 34, po_waves_right, 2, 1);
    waves_right->setName("wavesright");

    /* 创建金币数量 */
    auto lb_money = lb_create1(money, "fonts/HPSimplified_Bd.ttf", 35, po_lb_money, 1);
    lb_money->setName("lb_money");

    /* 创建升级金币 */
    auto lb_up_money = lb_create1(100, "fonts/HPSimplified_Bd.ttf", 25, bg, -10, 2);
    lb_up_money->setName("lb_up_money");

    /* 创建出售金币 */
    auto lb_sell_money = lb_create1(200, "fonts/HPSimplified_Bd.ttf", 25, bg, -10, 2);
    lb_sell_money->setName("lb_sell_money");

    /* 创建障碍物 */
    auto _1brr1 = sp_create("Barrier_One_1.png", brr1_1, map_scale, 0);
    auto _1brr2 = sp_create("Barrier_One_1.png", brr1_2, map_scale, 0);
    auto _1brr3 = sp_create("Barrier_One_2.png", brr1_3, map_scale, 0);
    auto _1brr4 = sp_create("Barrier_One_2.png", brr1_4, map_scale, 0);
    auto _2brr1 = sp_create("Barrier_Two_1.png", brr2_1, map_scale, 0);
    auto _4brr1 = sp_create("Barrier_Four_1.png", brr4_1, map_scale, 0);
    auto _4brr2 = sp_create("Barrier_Four_3.png", brr4_2, map_scale, 0);
    auto _4brr3 = sp_create("Barrier_Four_3.png", brr4_3, map_scale, 0);

    /*********** 创建按钮 **********/
    /* 创建菜单 */
    auto game_menu = btn_create(
        "Levels/btn/gamemenu_btn_normal.png",
        "Levels/btn/gamemenu_btn_pressed.png",
        gmmenu, btn_scale, 0);
    game_menu->setName("Menu");
    game_menu->addTouchEventListener([this, v_size=visibleSize](Ref* sender, Widget::TouchEventType type) {
        auto menu_layer = PauseMenu::create_Layer();    //创建弹出菜单
        auto menu = this->getChildByName<Button*>("Menu");
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
                is_stop = true;
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
        //auto mons = this->getChildByTag<Monster*>(0);
        auto scene = Director::getInstance()->getRunningScene();
        auto btn = this->getChildByName<Button*>("game_pause");
        auto pausing = this->getChildByName<Sprite*>("pausing");
        auto bg_waves = this->getChildByName<Sprite*>("bgwaves");
        auto total_waves = this->getChildByName<Sprite*>("totalwaves");
        auto waves_left = this->getChildByName<Sprite*>("wavesleft");
        auto waves_right = this->getChildByName<Sprite*>("wavesright");
        // 抓取当前场景所有怪物
        Monster* mons[20];
        int cur_tag = this->mons_tag;
        int least = 10101, co = 0;
        update_tag(least, this->waves);
        for (;cur_tag > least;)
            mons[co++] = scene->getChildByTag<Monster*>(--cur_tag);
        switch (type)
        {
            case Widget::TouchEventType::BEGAN:
                break;
            case Widget::TouchEventType::ENDED:
                if (is_pause == 0) {
                    btn->loadTextures("Levels/btn/game_continue_normal.png",
                        "Levels/btn/game_continue_pressed.png",
                        "Levels/btn/game_continue_normal.png");
                    is_pause = 1;
                    for (int i = 0; i < co; ++i)
                        mons[i]->unscheduleUpdate();   //怪物停止移动
                    /* 标签切换 */
                    bg_waves->setZOrder(-3);
                    total_waves->setZOrder(-3);
                    waves_left->setZOrder(-3);
                    waves_right->setZOrder(-3);
                    pausing->setZOrder(3);
                    //todo:进入暂停状态
                }
                else {
                    btn->loadTextures("Levels/btn/game_pause.png",
                        "Levels/btn/game_pause.png",
                        "Levels/btn/game_pause.png");
                    is_pause = 0;
                    for (int i = 0; i < co; ++i)
                        mons[i]->scheduleUpdate();   //怪物停止移动
                    /* 标签切换 */
                    bg_waves->setZOrder(2);
                    total_waves->setZOrder(2);
                    waves_left->setZOrder(2);
                    waves_right->setZOrder(2);
                    pausing->setZOrder(-3);
                    //todo:进入开始状态
                }
                break;
            default:
                break;
        }
        });
    
    /*********** 创建事件 **********/
    /* 改变速度 */
    auto spd_click_listener = EventListenerTouchOneByOne::create();
    spd_click_listener->onTouchBegan = [&](Touch* touch, Event* event) {
        auto pos = touch->getLocation();
        auto sp = this->getChildByName<Sprite*>("spd_shift");
        if (sp->getBoundingBox().containsPoint(pos))
            return true;
        return false;
        };
    spd_click_listener->onTouchMoved = [](Touch* touch, Event* event) {};
    spd_click_listener->onTouchEnded = [&](Touch* touch, Event* event) {      
        auto sp = this->getChildByName<Sprite*>("spd_shift");
        if (speed == 1) {
            sp->setSpriteFrame("game_speed_2.png");
            speed = 2;
        }
        else {
            sp->setSpriteFrame("game_speed_1.png");
            speed = 1;
        }
        };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(spd_click_listener, this);

    /* 点击地图 */
    //int map_clicked = 0;//状态

    auto map_click_listener= EventListenerTouchOneByOne::create();
    map_click_listener->onTouchBegan = [&](Touch* touch, Event* event) {
        auto pos = touch->getLocation();
        if (pos.y >= 765)
            return false;
        if (map_clicked_1 == 0) {
            cur_line = get_line(pos.y);
            cur_row = get_row(pos.x);
            cur_pos = get_po(cur_line, cur_row);
        }
        
        return true;
        };
    map_click_listener->onTouchMoved = [](Touch* touch, Event* event) {};
    map_click_listener->onTouchEnded = [&](Touch* touch, Event* event) {
        auto pos = touch->getLocation();
        /*int line = get_line(pos.y);
        int row = get_row(pos.x);*/
        auto create1 = this->getChildByName<Sprite*>("create_bottle");
        auto create2 = this->getChildByName<Sprite*>("create_shit");
        auto grid1 = this->getChildByTag<Sprite*>(tag1_1);//之前的
        auto grid2 = this->getChildByTag<Sprite*>(tag1_2);//之前的
        int state = occupy_1[cur_line][cur_row];
        int up_po = cur_line < 4 ? -1 : 1;
        int right = 0;
        if (cur_row == 0)
            right = 1;
        else if (cur_row == 11)
            right = -1;
        Vec2 po = get_po(cur_line, cur_row);
        Vec2 po1(po.x + (right - 1) * 55, po.y + 95 * up_po);
        Vec2 po2(po.x + (right + 1) * 55, po.y + 95 * up_po);

        auto range = this->getChildByName<Sprite*>("atk_range");
        auto up = this->getChildByName<Sprite*>("up_level");
        auto _sell = this->getChildByName<Sprite*>("sell");
        auto up_money = this->getChildByName<Label*>("lb_up_money");
        auto sell_money = this->getChildByName<Label*>("lb_sell_money");

        if (map_clicked_1 == 1) {//之前已经点击了一个可建造炮塔的位置
            if (create1->getBoundingBox().containsPoint(pos)) {//点击建造bottom
                if (money >= 100) {
                    auto tower = Tower::create_Tower(0, cur_line, cur_row, this);
                    /* 2 0x yy */
                    //2开头表示防御塔 0无意义 x为cur_line yy为cur_row
                    tower->setTag(2 * 10000 + cur_line * 100 + cur_row);

                    occupy_1[cur_line][cur_row] = 3;
                    create1->setZOrder(-10);
                    create2->setZOrder(-10);
                    grid1->setZOrder(-10);
                    grid2->setZOrder(-10);
                    map_clicked_1 = 0;

                    money -= 100;
                }
            }
            else if (create2->getBoundingBox().containsPoint(pos)) {//点击建造shit
                if (money >= 120) {
                    auto tower = Tower::create_Tower(1, cur_line, cur_row, this);
                    /* 2 0x yy */
                    //2开头表示防御塔 0无意义 x为cur_line yy为cur_row
                    tower->setTag(2 * 10000 + cur_line * 100 + cur_row);

                    occupy_1[cur_line][cur_row] = 3;
                    create1->setZOrder(-10);
                    create2->setZOrder(-10);
                    grid1->setZOrder(-10);
                    grid2->setZOrder(-10);
                    map_clicked_1 = 0;

                    money -= 120;
                }
            }
            else {//点其他任何位置                              
                create1->setZOrder(-10);
                create2->setZOrder(-10);
                grid1->setZOrder(-10);
                grid2->setZOrder(-10);
                map_clicked_1 = 0;
            }
        }
        else if (map_clicked_1 == 2) {//之前已经点击了一个防御塔
            //现在有两个按钮要按 升级or sell
            auto tower = this->getChildByTag<Tower*>(2 * 10000 + cur_line * 100 + cur_row);           
            int tower_level = tower->get_level();
            int um = tower->get_up_money();
            int sm = tower->get_sell_money();
            if (up->getBoundingBox().containsPoint(pos)) {
                if (money >= um && tower_level < 2) {
                    tower->up_level();//可加动画
                    money -= um;
                }
            }
            else if (_sell->getBoundingBox().containsPoint(pos)) {
                tower->remove();
                //tower->
                money += sm;
                occupy_1[cur_line][cur_row] = 0;
            }
            /* ZOrder */
            range->setZOrder(-10);
            up->setZOrder(-10);
            _sell->setZOrder(-10);
            up_money->setZOrder(-10);
            sell_money->setZOrder(-10);

            range->setPosition(Vec2(500,500));

            map_clicked_1 = 0;
        }
        else {//之前还未点击一个可以建造炮塔的位置
            if (state == 1) {//现在点击了一个不可点击的位置
                auto ban = this->getChildByTag<Sprite*>(192 + cur_line * 12 + cur_row);
                ban->setOpacity(255);
                auto fadeout = FadeOut::create(1.0f);
                ban->runAction(fadeout);
            }
            else if (state == 0) {//现在点击了一个可以建造炮塔的位置
                tag1_1 = cur_line * 12 + cur_row;
                tag1_2 = 96 + tag1_1;
                grid1 = this->getChildByTag<Sprite*>(tag1_1);
                grid2 = this->getChildByTag<Sprite*>(tag1_2);
                create1->setPosition(po1);
                create2->setPosition(po2);
                create1->setZOrder(4);
                create2->setZOrder(4);
                grid1->setZOrder(4);
                grid2->setZOrder(4);
                map_clicked_1 = 1;
            }
            else if (state == 3) {//现在点击了一个防御塔
                auto tower = this->getChildByTag<Tower*>(2 * 10000 + cur_line * 100 + cur_row);                
                int tower_level = tower->get_level();
                float range_scale = tower->get_scale();
                Vec2 up_pos;
                Vec2 sell_pos;
                Vec2 up_money_pos;
                Vec2 sell_money_pos;
                if (cur_line > 1 && cur_line < 7) {//在中间 升级在上 出售在下 
                    up_pos = Vec2(cur_pos.x, cur_pos.y + 95);
                    sell_pos = Vec2(cur_pos.x, cur_pos.y - 95);
                }
                else {
                    if (cur_line == 1) {//在最上面
                        int right = cur_row == 11 ? -1 : 1;
                        sell_pos = Vec2(cur_pos.x, cur_pos.y - 95);//出售在下
                        up_pos = Vec2(cur_pos.x + 95 * right, cur_pos.y);//升级：第11列在左 其余在右
                    }
                    else {//cur_line==7 在最下面
                        int left = cur_row == 0 ? 1 : -1;
                        sell_pos = Vec2(cur_pos.x + 95 * left, cur_pos.y);//出售：第0列在右 其余在左
                        up_pos = Vec2(cur_pos.x, cur_pos.y + 95);//升级在上
                    }
                }
                up_money_pos = Vec2(up_pos.x + 12, up_pos.y - 30);
                sell_money_pos = Vec2(sell_pos.x + 12, sell_pos.y - 30);                

                /* 攻击范围大小 */
                range->setScale(range_scale);

                /* 位置 */
                range->setPosition(cur_pos);
                up->setPosition(up_pos);
                _sell->setPosition(sell_pos);
                up_money->setPosition(up_money_pos);
                sell_money->setPosition(sell_money_pos);

                /* 渲染 */
                /* up+up_money */
                if (tower_level == 2)
                    up->setSpriteFrame("top_level.png");
                else {
                    int um = tower->get_up_money();
                    string text = to_string(um);
                    if (money >= um)
                        up->setSpriteFrame("yes_up.png");
                    else
                        up->setSpriteFrame("no_up.png");
                    up_money->setString(text);
                }
                /* sell_money */
                int sm = tower->get_sell_money();
                string text = to_string(sm);
                sell_money->setString(text);

                /* ZOrder */
                range->setZOrder(1);
                up->setZOrder(3);
                _sell->setZOrder(3);
                if (tower_level < 2)
                    up_money->setZOrder(4);
                sell_money->setZOrder(4);

                map_clicked_1 = 2;
            }
        }
        };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(map_click_listener, this);

    /*********** 创建怪物 **********/
    // 待量产
    //auto mon1 = Monster::create_Monster(PUPIL_1);
    //mon1->setPosition(born);
    //mon1->setScale(map_scale);
    //mon1->setTexture("Monsters/Monsters01-22.png");
    //mon1->setAnchorPoint(Vec2(0.5, 0));
    //mon1->setTag(0);
    //mon1->set_route(path, top);
    //addChild(mon1, 2);
    //mon1->scheduleUpdate(); //实现按路径移动

    this->schedule(schedule_selector(Map_1_01::create_monster), 1.0f / speed);
    




    /* 创建倒计时 */
    auto count = CountDown::create_Layer();
    this->addChild(count, 10);

    


	return true;
}