
#include "EnterScene.h"
#include "StartScene.h"
#include "AudioEngine.h"
#include "ui/CocosGUI.h"
#include "MapChoose.h"

USING_NS_CC;
using namespace ui;
using namespace std;

/* 如果文件无法打开，打印报错信息 */
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

Scene* Enter::create_Scene()
{
	return Enter::create();
}

/* 进入地图选择界面 */
void chooseCall(Ref* pSender)
{
    auto map_choose = MapChoose::create_Scene();
    Director::getInstance()->replaceScene(map_choose);

}

bool Enter::init()
{
	if (!Scene::init())
		return false;

    const Vec2 visibleSize = Vec2(Director::getInstance()->getVisibleSize());
    const Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 预加载精灵图集
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("EnterScene/EnterScene.plist");
    static const auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("theme_desert.png");

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

    constexpr float bg_scale = 1.5f;        //背景放大倍率
    constexpr float stage_scale = 1.0f;     //章节放大倍率
    constexpr float btn_scale = 1.1f;       //按钮放大倍率
    const float btnY = visibleSize.y / 2;   //按钮高度
    const Vec2 bg(visibleSize / 2);         //章节位置
    const Vec2 btn_left(400, btnY);         //左移位置
    const Vec2 btn_right(1560, btnY);       //右移位置

    /**************************************/

    /* 创建事件 */
    auto click_listener = EventListenerTouchOneByOne::create();
    click_listener->onTouchBegan = [&](Touch* touch, Event* event) { 
        auto pos = touch->getLocation();
        auto sp = (Sprite*)(this->getChildByName("skyline"));
        if (sp->getBoundingBox().containsPoint(pos))
            return true;
        return false;
        };
    click_listener->onTouchMoved = [](Touch* touch, Event* event) {};
    click_listener->onTouchEnded = [&](Touch* touch, Event* event) {
        auto next = MapChoose::create_Scene();
        if (next == nullptr)
            return false;
        
        Director::getInstance()->replaceScene(next);
        return true;
        };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(click_listener, this);

    /* 创建背景 */
    auto background = sp_create("bg.png", bg, bg_scale, -1);

    /* 创建章节 */
    auto skyline = sp_create("theme_skyline.png", bg, stage_scale, 1);
    //skyline->initWithSpriteFrameName("theme_desert.png");
    skyline->setName("skyline");
    //skyline->setSpriteFrame(frame);


    /******* 创建按钮 *******/
    /* 按钮——左移 */
    auto goleft = btn_create(
        "EnterScene/contents/left_normal.png",
        "EnterScene/contents/left_pressed.png",
        btn_left, btn_scale);

    
    /* 按钮——右移 */
    auto goright = btn_create(
        "EnterScene/contents/right_normal.png",
        "EnterScene/contents/right_pressed.png",
        btn_right, btn_scale);
    //ToDo
    auto func = [&](Ref* eSender, Widget::TouchEventType type) {
        auto sp = (Sprite*)(this->getChildByName("skyline"));
        switch (type)
        {
            case Widget::TouchEventType::BEGAN:
                break;
            case Widget::TouchEventType::ENDED:
                //skyline->setSpriteFrame(frame);
                sp->setTexture("EnterScene/contents/theme_jungle.png");
                break;
            default:
                break;
        }
        };
    goright->addTouchEventListener(func);


    return true;
}
