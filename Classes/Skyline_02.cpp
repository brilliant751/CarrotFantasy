#pragma execution_character_set("utf-8")
#include "StartScene.h"
#include "EnterScene.h"
#include "Skyline_02.h"
#include "GameMenu.h"
#include "MapChoose.h"
#include "Carrot.h"
#include "ui/CocosGUI.h"
#include "ui/UIButton.h"
#include "Monsters.h"
#include "Towers.h"
#include "tools.h"
#include "audio/include/AudioEngine.h"
USING_NS_CC;
using namespace ui;
using namespace std;
using namespace experimental;

#define MAX_WAVE 15     //最大波次

// 地图数据
extern int LEVEL;
extern each_map all_map[3];
extern bool is_open[3];
extern string stars_url[3];
// 游戏
extern bool is_stop;   //标记游戏是否暂停（菜单用）
extern bool is_paused;  //标记游戏是否暂停
extern int speed;      //游戏倍速
extern clock_t timer;  //计时器
extern int waves;      //游戏波次
extern int money;		//金钱
extern Monster* cur_mons[20];   //当前所有怪物
extern int lives;      //栈顶指针，当前场上怪物数量
extern Target* target; //锁定对象

/********** 坐标线位置 **********/
// 地图大小为 12 * 8 个方格
constexpr int mapX[13] = { 0, 95, 190, 285, 380, 475, 570, 665, 760, 855, 950, 1045, 1140 };
constexpr int mapY[9] = { 0, 95, 190, 285, 380, 475, 570, 665, 760 };

// 怪物行走路线
static const Vec2 path[] = {
        Vec2(origin.x + (mapX[1] + mapX[2]) / 2.0f, origin.y + (mapY[5] + mapY[6]) / 2.0f),
        Vec2(origin.x + (mapX[1] + mapX[2]) / 2.0f, origin.y + (mapY[2] + mapY[3]) / 2.0f),
        Vec2(origin.x + (mapX[4] + mapX[5]) / 2.0f, origin.y + (mapY[2] + mapY[3]) / 2.0f),
        Vec2(origin.x + (mapX[4] + mapX[5]) / 2.0f, origin.y + (mapY[3] + mapY[4]) / 2.0f),
        Vec2(origin.x + (mapX[7] + mapX[8]) / 2.0f, origin.y + (mapY[3] + mapY[4]) / 2.0f),
        Vec2(origin.x + (mapX[7] + mapX[8]) / 2.0f, origin.y + (mapY[2] + mapY[3]) / 2.0f),
        Vec2(origin.x + (mapX[10] + mapX[11]) / 2.0f, origin.y + (mapY[2] + mapY[3]) / 2.0f),
        Vec2(origin.x + (mapX[10] + mapX[11]) / 2.0f, origin.y + (mapY[5] + mapY[6]) / 2.0f),
};
static constexpr int top = 8; //栈顶位置


/* 更新波次 */
void Map_1_02::update_waves()
{
    ++waves;    //进入下一波
    lives = 0;
    update_tag(mons_tag, waves);    //更新当前怪物标签
    update_tag(least, waves);       //更新起始怪物标签
    auto left = getChildByName<Label*>("wavesleft");
    auto right = getChildByName<Label*>("wavesright");
    int yu = waves % 10;
    right->setString(to_string(yu));
    if (yu == 0)
        left->setString(to_string(waves / 10));
}

/* 生成怪物 */
void Map_1_02::create_monster(float dt)
{
    if (get_tag_waves(mons_tag) != waves)
    {
        update_tag(mons_tag, waves);
    }
    if (mons_tag % 100 > MONS_NUM)  //怪物已全部刷新
    {
        int temp = least;
        for (int i = 0; i < MONS_NUM; ++i)
            if (this->getChildByTag(temp++))
                return;     //如果场上存在怪物则返回
        // 如果已到最大波次则结束刷新
        if (waves >= MAX_WAVE)
        {
            auto win_layer = Popwin::create_Layer();    //创建成功弹窗
            /* 创建调暗层 */
            auto dimlayer = LayerColor::create(Color4B(0, 0, 0, 128), 1620, 960);
            dimlayer->setName("dimmer");
            auto scene = Director::getInstance()->getRunningScene();
            scene->addChild(win_layer, 20);
            scene->addChild(dimlayer, 9);
            /* 暂停主场景的活动 */
            // 此处会循环暂停所有child结点的监听事件
            scene->getEventDispatcher()->pauseEventListenersForTarget(scene, true);
            // 暂停所有刷新和动作
            scene->pauseSchedulerAndActions();
            /* 恢复弹窗层的监听事件 */
            win_layer->getEventDispatcher()->resumeEventListenersForTarget(win_layer, true);

            return;
        }
        // 不存在则进入下一波
        update_waves();
        return;
    }
    auto mon1 = Monster::create_Monster(PUPIL_1, path, top);
    mon1->setSpriteFrame(mons_url[waves]);
    mon1->setTag(mons_tag++);
    addChild(mon1, 2);
    //mons_tag++;
    cur_mons[lives++] = mon1;
    timer = clock();    //记录最后一次刷怪时间
}

/* 建造防御塔按钮刷新 */
void Map_1_02::update_create(float dt) {
    auto sp1 = this->getChildByName<Sprite*>("create_bottle");
    auto sp2 = this->getChildByName<Sprite*>("create_shit");
    auto sp3 = this->getChildByName<Sprite*>("create_fan");
    if (money >= 100)
        sp1->setSpriteFrame("bottle_yes_create.png");
    else
        sp1->setSpriteFrame("bottle_no_create.png");
    if (money >= 120)
        sp2->setSpriteFrame("shit_yes_create.png");
    else
        sp2->setSpriteFrame("shit_no_create.png");
    if(money>=160)
        sp3->setSpriteFrame("fan_yes_create.png");
    else
        sp3->setSpriteFrame("fan_no_create.png");

}

/* 金币数量刷新 */
void Map_1_02::update_money(float dt) {
    auto label = this->getChildByName<Label*>("lb_money");
    string num = to_string(money);
    label->setString(num);
}

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

    auto visibleSize = Director::getInstance()->getVisibleSize();   //(1620,960)

    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Levels/1-02/1_02.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Levels/Barriers/Barriers.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Levels/Carrot/Carrot.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Levels/tower_click/tower_click.plist");

    /* 初始化全局变量 */
    is_stop = false;
    is_paused = false;
    waves = 1;      //波数为1
    speed = 1;      //倍速为1
    LEVEL = 1;      //关卡序号1
    lives = 0;      //怪物数量0


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
    const Vec2 po_lb_money(390, topY + 10);           //金币位置
    const Vec2 crt(origin.x+mapX[7]+(mapX[1])/2.0f, origin.y + mapY[2]);             //萝卜位置
    const Vec2 born(origin.x + mapX[9]/2.0f, origin.y + (mapY[5]+mapY[6])/2.0f); //怪物出生点
    /* 障碍物位置 */
    const Vec2 planet_1(origin.x + (mapX[4] + mapX[3]) / 2.0f, origin.y + (mapY[4] + mapY[1]) / 2.0f);
    const Vec2 planet_2(origin.x + (mapX[8] + mapX[9]) / 2.0f, origin.y + (mapY[4] + mapY[5]) / 2.0f);
    const Vec2 planet_3(origin.x + (mapX[10] + mapX[11]) / 2.0f, origin.y + (mapY[6] + mapY[5]) / 2.0f);
    const Vec2 planet_4(origin.x + (mapX[4] + mapX[5]) / 2.0f, origin.y + (mapY[4] + mapY[5]) / 2.0f);
    const Vec2 balloon(origin.x + mapX[11], origin.y + mapY[4]);
    const Vec2 trees(origin.x + mapX[2], origin.y + mapY[6]);
    const Vec2 cloud_1(origin.x + (mapX[7] + mapX[6]) / 2.0f, origin.y + (mapY[4] + mapY[5]) / 2.0f);
    const Vec2 cloud_2(origin.x + (mapX[5] + mapX[6]) / 2.0f, origin.y + mapY[5] / 2.0f);
    const Vec2 rainbow_1(origin.x + mapX[1], origin.y + (mapY[4] + mapY[1]) / 2.0f);
    const Vec2 rainbow_2(origin.x + mapX[9], origin.y + (mapY[4] + mapY[1]) / 2.0f);

    /**************************************/

    /*********** 创建精灵 **********/
    /* 创建背景 */
    auto map_bg = sp_create("1_02_bg.png", bg, map_scale, -2);

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
    auto start_point_02 = sp_create("start_point02.png", born, map_scale, 0);

    /* 创建倍速键 */
    auto spd_shift = sp_create("game_speed_1.png", spd, map_scale, 0);
    spd_shift->setName("spd_shift");

    /* waves框 */
    auto bg_waves = sp_create("game)waves.png", po_bg_waves, map_scale, 0);
    bg_waves->setName("bgwaves");

    /* 创建障碍物 */
    auto planet1 = sp_create("Barrier_One_1.png", planet_1, map_scale, 0);
    auto planet2 = sp_create("Barrier_One_1.png", planet_2, map_scale, 0);
    auto planet3 = sp_create("Barrier_One_1.png", planet_3, map_scale, 0);
    auto planet4 = sp_create("Barrier_One_1.png", planet_4, map_scale, 0);
    auto _balloon = sp_create("Barrier_Four_1.png", balloon, map_scale, 0);
    auto _trees = sp_create("Barrier_Four_2.png", trees, map_scale, 0);
    auto _cloud1 = sp_create("Barrier_One_2.png", cloud_1, map_scale, 0);
    auto _cloud2 = sp_create("Barrier_One_2.png", cloud_2, map_scale, 0);
    auto _rainbow1 = sp_create("Barrier_Two_1.png", rainbow_1, map_scale, 0);
    auto _rainbow2 = sp_create("Barrier_Two_1.png", rainbow_2, map_scale, 0);


    /* 创建点击格子 + 不可点击格子 */
    for (int i = 1; i < 8; i++)
        for (int j = 0; j < 12; j++) {
            Vec2 po = get_po(i, j);
            if (occupy_2[i][j] == 0) {
                auto sp1 = sp_create("start_sprite02.png", po, map_scale, -10);
                sp1->setTag(i * 12 + j);
                auto sp2 = sp_create("grid_02.png", po, map_scale, -10);
                sp2->setTag(96 + i * 12 + j);
            }
            else if (occupy_2[i][j] == 1) {
                auto sp = sp_create("cant_build02.png", po, map_scale, 2);
                sp->setTag(192 + i * 12 + j);
                sp->setOpacity(0);
            }
        }
    /* 创建建造bottle精灵 */
    auto create_bottle = sp_create("bottle_no_create.png", bg, map_scale, -10);
    create_bottle->setName("create_bottle");

    /* 创建建造shit精灵 */
    auto create_shit = sp_create("shit_no_create.png", bg, map_scale, -10);
    create_shit->setName("create_shit");

    /* 创建建造fan精灵 */
    auto create_fan = sp_create("fan_no_create.png", bg, map_scale, -10);
    create_fan->setName("create_fan");

    /* 创建 攻击范围 精灵 */
    auto atk_range = sp_create("range.png", bg, 2, -10);//自身一倍是1.5个格子
    atk_range->setName("atk_range");

    /* 创建 升级 精灵 */
    auto up_level = sp_create("no_up.png", bg, map_scale, -10);
    up_level->setName("up_level");

    /* 创建 出售 精灵 */
    auto sell = sp_create("sell.png", bg, map_scale, -10);
    sell->setName("sell");

    // 刷新建造防御塔按钮
    this->schedule(schedule_selector(Map_1_02::update_create), 0.1f);
    // 刷新金币数量
    this->schedule(schedule_selector(Map_1_02::update_money), 0.1f);


    /*********** 创建标签 ***********/
    /* 创建萝卜血条数字 */
    auto chp_num = lb_create1(c_hp, "fonts/HPSimplified_Bd.ttf", 27, po_chp_num, 1);

    /* 创建total_waves */
    auto lb_total_waves = lb_create2("/20波怪物", "fonts/方正粗黑宋简体.ttf", 34, po_lb_total_waves, 2);
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
    auto lb_up_money = lb_create(this, 100, "fonts/HPSimplified_Bd.ttf", 25, bg, -10, 2);
    lb_up_money->setName("lb_up_money");

    /* 创建出售金币 */
    auto lb_sell_money = lb_create(this, 200, "fonts/HPSimplified_Bd.ttf", 25, bg, -10, 2);
    lb_sell_money->setName("lb_sell_money");

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
        auto btn = this->getChildByName<Button*>("game_pause");
        //auto mons = this->getChildByTag<Monster*>(0);
        auto pausing = this->getChildByName<Sprite*>("pausing");
        auto bg_waves = this->getChildByName<Sprite*>("bgwaves");
        auto total_waves = this->getChildByName<Sprite*>("totalwaves");
        auto waves_left = this->getChildByName<Sprite*>("wavesleft");
        auto waves_right = this->getChildByName<Sprite*>("wavesright");
        switch (type)
        {
            case Widget::TouchEventType::BEGAN:
                break;
            case Widget::TouchEventType::ENDED:
                if (is_paused == 0) {
                    btn->loadTextures("Levels/btn/game_continue_normal.png",
                        "Levels/btn/game_continue_pressed.png",
                        "Levels/btn/game_continue_normal.png");
                    is_paused = 1;
                    //mons->unscheduleUpdate();   //怪物停止移动
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
                    is_paused = 0;
                    //mons->scheduleUpdate();     //怪物开始移动
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
    /* 切换倍速 */
    auto spd_click_listener = EventListenerTouchOneByOne::create();
    spd_click_listener->onTouchBegan = [&](Touch* touch, Event* event) {
        auto pos = touch->getLocation();
        auto sp = (Sprite*)(this->getChildByName("spd_shift"));
        if (sp->getBoundingBox().containsPoint(pos))
            return true;
        return false;
        };
    spd_click_listener->onTouchMoved = [](Touch* touch, Event* event) {};
    spd_click_listener->onTouchEnded = [&](Touch* touch, Event* event) {
        auto sp = (Sprite*)(this->getChildByName("spd_shift"));
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
    auto map_click_listener = EventListenerTouchOneByOne::create();
    map_click_listener->onTouchBegan = [&](Touch* touch, Event* event) {
        auto pos = touch->getLocation();
        if (pos.y >= 765 || pos.y <= 100 || pos.x >= 1380 || pos.x <= 240)
            return false;   //点击地图外位置无效
        // 之前未点击
        if (map_clicked_2 == 0)
        {   // 之前未点击
            cur_line = get_line(pos.y);            //获取当前行
            cur_row = get_row(pos.x);              //获取当前列
            cur_pos = get_po(cur_line, cur_row);   //获取格子中心坐标
            tag2_1 = cur_line * 12 + cur_row;      //虚线tag
            tag2_2 = 96 + tag2_1;                  //实线tag
        }
        return true;
        };
    map_click_listener->onTouchMoved = [](Touch* touch, Event* event) {};
    map_click_listener->onTouchEnded = [&](Touch* touch, Event* event) {
        auto pos = touch->getLocation();
        // 抓取按键精灵
        auto create1 = this->getChildByName<Sprite*>("create_bottle");
        auto create2 = this->getChildByName<Sprite*>("create_shit");
        auto create3 = this->getChildByName<Sprite*>("create_fan");
        // 抓取格子精灵
        auto grid1 = this->getChildByTag<Sprite*>(tag2_1);
        auto grid2 = this->getChildByTag<Sprite*>(tag2_2);
        // 获取当前格的状态
        int state = occupy_2[cur_line][cur_row];
        // 调整按键位置，防止超出地图
        int up_po = cur_line < 4 ? -1 : 1;
            int right = 0;
            if (cur_row == 0)
                right = 2;
            else if (cur_row == 1)
                right = 1;
            else if (cur_row == 11)
                right = -2;
            else if (cur_row == 10)
                right = -1;
        
        // 设定位置
        Vec2 po = get_po(cur_line, cur_row);
        Vec2 po1(po.x + (right - 2) * 55, po.y + 95 * up_po);
        Vec2 po2(po.x + right * 55, po.y + 95 * up_po);
        Vec2 po3(po.x + (right + 2) * 55, po.y + 95 * up_po);
        // 抓取一些精灵
        auto range = this->getChildByName<Sprite*>("atk_range");          //攻击范围精灵
        auto up = this->getChildByName<Sprite*>("up_level");              //升级精灵
        auto _sell = this->getChildByName<Sprite*>("sell");               //出售精灵
        // 抓取一些标签
        auto up_money = this->getChildByName<Label*>("lb_up_money");      //升级需要的钱
        auto sell_money = this->getChildByName<Label*>("lb_sell_money");  //出售可得的钱

        /* 按格子状态对应不同功能 */
        if (map_clicked_2 == 1) //之前已经点击了一个可建造炮塔的位置
        {
            if (create1->getBoundingBox().containsPoint(pos)) {//点击建造bottle
                if (money >= 100) {
                    auto tower = Tower::create_Tower(0, cur_line, cur_row, this);
                    /* 2 0x yy */
                    //2开头表示防御塔 0无意义 x为cur_line yy为cur_row
                    tower->setTag(2 * 10000 + cur_line * 100 + cur_row);
                    // 更新格子状态
                    occupy_2[cur_line][cur_row] = 3;
                    //把不显示的精灵放在下面
                    create1->setZOrder(-10);
                    create2->setZOrder(-10);
                    create3->setZOrder(-10);
                    grid1->setZOrder(-10);
                    grid2->setZOrder(-10);
                    //更新格子状态
                    map_clicked_2 = 0;
                    //更新钱
                    money -= 100;
                    auto audio = AudioEngine::play2d("sound/build_tower.mp3", false);
                }
            }
            else if (create2->getBoundingBox().containsPoint(pos)) {//点击建造shit
                if (money >= 120) {
                    auto tower = Tower::create_Tower(1, cur_line, cur_row, this);
                    /* 2 0x yy */
                    //2开头表示防御塔 0无意义 x为cur_line yy为cur_row
                    tower->setTag(2 * 10000 + cur_line * 100 + cur_row);
                    // 更新格子状态
                    occupy_2[cur_line][cur_row] = 3;
                    //把不显示的精灵放在下面
                    create1->setZOrder(-10);
                    create2->setZOrder(-10);
                    create3->setZOrder(-10);
                    grid1->setZOrder(-10);
                    grid2->setZOrder(-10);
                    //更新格子状态
                    map_clicked_2 = 0;
                    //更新钱
                    money -= 120;
                    auto audio = AudioEngine::play2d("sound/build_tower.mp3", false);
                }

            }
            else if (create3->getBoundingBox().containsPoint(pos)) {//点击建造fan
                if (money >= 160) {//试一下电风扇
                    auto tower = Tower::create_Tower(2, cur_line, cur_row, this);
                    tower->schedule(schedule_selector(Tower::shoot_3), 2.0f);
                    /* 2 0x yy */
                    //2开头表示防御塔 0无意义 x为cur_line yy为cur_row
                    tower->setTag(2 * 10000 + cur_line * 100 + cur_row);
                    occupy_2[cur_line][cur_row] = 3;
                    create1->setZOrder(-10);
                    create2->setZOrder(-10);
                    create3->setZOrder(-10);
                    grid1->setZOrder(-10);
                    grid2->setZOrder(-10);
                    map_clicked_2 = 0;
                    money -= 120;
                    auto audio = AudioEngine::play2d("sound/build_tower.mp3", false);

            }
            }
            else {//点其他任何位置 即取消选中    
                //把不显示的精灵放在下面
                create1->setZOrder(-10);
                create2->setZOrder(-10);
                create3->setZOrder(-10);
                grid1->setZOrder(-10);
                grid2->setZOrder(-10);
                //更新格子状态
                map_clicked_2 = 0;
            }
        }
        else if (map_clicked_2 == 2)//之前已经点击了一个防御塔
        {   // 有两个按钮可按 升级 or sell
            auto tower = this->getChildByTag<Tower*>(2 * 10000 + cur_line * 100 + cur_row);    //获取防御塔       
            int tower_level = tower->get_level();  //获取防御塔等级
            int um = tower->get_up_money();     //升级所需的钱
            int sm = tower->get_sell_money();   //卖出所给的钱

            if (up->getBoundingBox().containsPoint(pos)) {//按升级精灵
                if (money >= um && tower_level < 2) {//可以升级
                    tower->up_level();          //升级 todo：可加动画
                    money -= um;                //更新钱
                    auto audio = AudioEngine::play2d("sound/uplevel_tower.mp3", false);
                }
            }
            else if (_sell->getBoundingBox().containsPoint(pos)) {//按出售精灵
                tower->remove();    //清除
                money += sm;        //获得卖出的钱
                occupy_2[cur_line][cur_row] = 0;    //更新格子状态
                auto audio = AudioEngine::play2d("sound/sell_tower.mp3", false);
            }
            //把不显示的精灵放在下面
            /* ZOrder */
            range->setZOrder(-10);
            up->setZOrder(-10);
            _sell->setZOrder(-10);
            up_money->setZOrder(-10);
            sell_money->setZOrder(-10);
            //为防止range超出范围 放在靠中间的位置
            range->setPosition(Vec2(500, 500));
            //更新格子状态
            map_clicked_2 = 0;
        }
        else {//之前还未点击一个可以建造炮塔的位置
            if (state == 1) {//现在点击了一个不可点击的位置
                auto ban = this->getChildByTag<Sprite*>(192 + cur_line * 12 + cur_row);//获取ban精灵
                ban->setOpacity(255);                    //恢复透明度为100%
                auto fadeout = FadeOut::create(1.0f);    //逐渐淡去
                ban->runAction(fadeout);                 //执行动作
            }
            else if (state == 0) {//现在点击了一个可以建造炮塔的位置
                grid1 = this->getChildByTag<Sprite*>(tag2_1);//获取虚线框
                grid2 = this->getChildByTag<Sprite*>(tag2_2);//获取实线框
                //更新精灵位置及ZOrder
                create1->setPosition(po1);
                create2->setPosition(po2);
                create3->setPosition(po3);
                create1->setZOrder(4);
                create2->setZOrder(4);
                create3->setZOrder(4);
                grid1->setZOrder(4);
                grid2->setZOrder(4);
                //更新格子状态
                map_clicked_2 = 1;
            }
            else if (state == 3) {//现在点击了一个防御塔
                auto tower = this->getChildByTag<Tower*>(2 * 10000 + cur_line * 100 + cur_row);  //获取防御塔              
                int tower_level = tower->get_level();
                float range_scale = tower->get_scale();
                /* 计算各个精灵 标签位置 */
                Vec2 up_pos;
                Vec2 sell_pos;
                Vec2 up_money_pos;
                Vec2 sell_money_pos;
                if (cur_line > 1 && cur_line < 7) {//防御塔在中间 升级在上 出售在下 
                    up_pos = Vec2(cur_pos.x, cur_pos.y + 95);
                    sell_pos = Vec2(cur_pos.x, cur_pos.y - 95);
                }
                else {
                    if (cur_line == 1) {//防御塔在最上面
                        int right = cur_row == 11 ? -1 : 1;
                        sell_pos = Vec2(cur_pos.x, cur_pos.y - 95);//出售在下
                        up_pos = Vec2(cur_pos.x + 95 * right, cur_pos.y);//升级：第11列在左 其余在右
                    }
                    else {//cur_line==7 防御塔在最下面
                        int left = cur_row == 0 ? 1 : -1;
                        sell_pos = Vec2(cur_pos.x + 95 * left, cur_pos.y);//出售：第0列在右 其余在左
                        up_pos = Vec2(cur_pos.x, cur_pos.y + 95);//升级在上
                    }
                }
                //根据精灵计算标签位置
                up_money_pos = Vec2(up_pos.x + 12, up_pos.y - 30);
                sell_money_pos = Vec2(sell_pos.x + 12, sell_pos.y - 30);

                /* 设置攻击范围大小 */
                range->setScale(range_scale);

                /* 设置位置 */
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
                    //根据money和升级money的关系渲染
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
                //更新格子状态
                map_clicked_2 = 2;
            }
        }
        };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(map_click_listener, this);


    /*********** 创建怪物 **********/
    this->schedule(schedule_selector(Map_1_02::create_monster), 1.0f / speed);









    /* 创建倒计时 */
    auto count = CountDown::create_Layer();
    this->addChild(count, 10);



    return true;
}