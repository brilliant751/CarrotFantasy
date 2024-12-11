
#include "GameMenu.h"
#include "Skyline_01.h"
#include "ui/CocosGUI.h"
#include "ui/UIButton.h"

USING_NS_CC;
using namespace ui;
using namespace std;


/* 创建Layer */
Layer* PauseMenu::create_Layer()
{
    return PauseMenu::create();
}

/* 初始化 */
bool PauseMenu::init()
{
    if (!Layer::init())
        return false;

    auto visibleSize = Director::getInstance()->getVisibleSize();   //(2050，1200)

    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Levels/GameMenu/GameMenu.plist");

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
    constexpr float btn_scale = 1.5f;       //按钮放大倍率
    constexpr float map_scale = 1.5f;       //地图放大倍率
    constexpr float word_scale = 2.0f;      //文字放大倍率
    const Vec2 bg(visibleSize / 2);         //窗口位置
    const Vec2 ctn(1010, 760);

    /**************************************/

    /*********** 创建精灵 **********/
    /* 创建窗口背景 */
    auto menu_bg = sp_create("options_bg.png", bg, map_scale, -1);


    /*********** 创建按钮 **********/
    /* 创建 继续游戏 按钮 */
    auto resume = btn_create(
        "Levels/btn/continue_normal.png",
        "Levels/btn/continue_pressed.png",
        ctn, btn_scale, 1);
    resume->setTag(100);
    resume->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type) {
        auto main_scene = Director::getInstance()->getRunningScene();
        //auto dimlayer = (LayerColor*)(main_scene->getChildByName("dimmer"));
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
                main_scene->removeChildByName("dimmer");
                main_scene->removeChild(this);
                ((Button*)(main_scene->getChildByName("Menu")))->setEnabled(true);
                main_scene->getEventDispatcher()->setEnabled(true);
                break;
            default:
                break;
        }
        });

    /* 创建 重新开始 按钮 */
    
    
    /* 创建 选择关卡 按钮 */



    return true;
}