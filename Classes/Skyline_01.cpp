
#include "StartScene.h"
#include "EnterScene.h"
#include "Skyline_01.h"
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
Scene* Map_1_01::create_Scene()
{
	return Map_1_01::create();
}

/* 初始化场景 */
bool Map_1_01::init()
{
	if (!Scene::init())
		return false;

	const Vec2 origin = Vec2(240, 100); //地图坐标起点
	auto visibleSize = Director::getInstance()->getVisibleSize();   //(1620,960)

    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Levels/1-01/1-01.plist");
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

    const Vec2 crt(1250, origin.y + mapY[6]);             //萝卜位置
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

    /**************************************/

    /*********** 创建精灵 **********/
    /* 创建背景 */
    auto map_bg = sp_create("1-01_bg.png", bg, map_scale, -2);

    /* 创建萝卜 */
    auto carrot = sp_create("HP_MAX.PNG", crt, map_scale, 0);

    /* 创建顶部状态栏 */
    auto top_bg = sp_create("top_bg.png", topbg, map_scale, -1);

    /* 创建暂停中显示 */
    auto pausing = sp_create("paused.png", topbg, word_scale, 0);

    /* 创建怪物出生点 */
    auto start_point = sp_create("start_point.png", born, map_scale, 0);

    /* 创建倍速键 */
    auto spd_shift = sp_create("game_speed_1.png", spd, map_scale, 0);

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
    game_pause->setName("pause");


	return true;
}