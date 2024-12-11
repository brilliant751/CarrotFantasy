
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

	const Vec2 origin = Vec2(305, 120); //地图坐标起点
	auto visibleSize = Director::getInstance()->getVisibleSize();   //(2050，1200)

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

    constexpr int btnY1 = 180;              //大按钮高度
    constexpr int btnY2 = 440;              //小按钮高度
    constexpr int locks = 220;              //锁高度
    constexpr float btn_scale = 1.4f;       //按钮放大倍率
    constexpr float map_scale = 1.5f;       //地图放大倍率
    constexpr float word_scale = 2.0f;      //文字放大倍率
    const Vec2 bg(visibleSize / 2);         //地图位置
    const Vec2 crt(1000, 1000);             //萝卜位置
    const Vec2 topbg(1024, 1022);           //顶部位置
    const Vec2 gmmenu(1630, 1022);          //菜单位置
    const Vec2 gmpause(1520, 1022);       //暂停位置

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

	return true;
}