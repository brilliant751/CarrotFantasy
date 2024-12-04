
#include "EnterScene.h"
#include "MapChoose.h"
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
    auto btn_create = [&](const string& normal_name, const string& pressed_name, const string& locked_name,
        const Vec2& pos, int btn_type, const float& scale = 1.1f, int layer = 0) {
            auto temp_btn = Button::create(normal_name, pressed_name, locked_name);
            temp_btn->setPosition(pos);
            temp_btn->setScale(scale);

            temp_btn->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
                switch (type)
                {
                    case ui::Widget::TouchEventType::BEGAN:
                        break;
                    case ui::Widget::TouchEventType::ENDED:
                        switch (btn_type) {
                            case 1:
                                //回到EnterScene
                                break;
                            case 2:
                                //到HelpScene
                                break;
                            case 3:
                                //开始游戏
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
    constexpr float btn_scale = 1.1f;      //按钮放大倍率
    constexpr float map_scale = 1.5f;      //地图放大倍率
    const Vec2 po_bg_left(495, 185);       //左下背景位置
    const Vec2 po_bg_right(1482, 183);     //右下背景位置
    const Vec2 po_btn_back(330, 953);      //返回按钮位置
    const Vec2 po_btn_help(1628, 953);     //帮助按钮位置
    const Vec2 po_btn_start(980, 150);     //开始按钮位置

    /**************************************/

    /* 创建背景 */
    auto bg = sp_create("bg.png", po_bg, map_scale, -1);
    auto bg_left = sp_create("bg_left.png", po_bg_left, map_scale, 0);
    auto bg_right = sp_create("bg_right.png", po_bg_right, map_scale, 0);

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
    auto btn_start = btn_create(
        "MapChoose/contents/btn_start_normal.png",
        "MapChoose/contents/btn_start_pressed.png",
        "MapChoose/contents/btn_start_normal.png",
        po_btn_start, 3);

    return true;
}