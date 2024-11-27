
#include "StartScene.h"
#include "EnterScene.h"
#include "AudioEngine.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;

Scene* StartScene::create_Scene()
{
	return StartScene::create();
}

static void enterCall(Ref* eSender)
{
    auto next = Enter::create_Scene();
    Director::getInstance()->replaceScene(next);
}

/* 如果文件无法打开，打印报错信息 */
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

/* 初始化程序 */
bool StartScene::init()
{
    // 先使用基类的初始化方法
    if (!Scene::init())
        return false;

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 创建关闭按钮
    auto closeItem = MenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
        CC_CALLBACK_1(StartScene::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
        float y = origin.y + closeItem->getContentSize().height / 2;
        closeItem->setPosition(Vec2(x, y));
    }

    // 创建进入游戏按钮
    auto enterBtn = Button::create(
        "StartScene/front_btn_start_normal.png",
        "StartScene/front_btn_start_pressed.png",
        "StartScene/front_btn_start_pressed.png");
    enterBtn->setPosition(Vec2(504, 456));

    enterBtn->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
                enterCall(this);
                break;
            default:
                break;
        }
        });

    addChild(enterBtn);

    // 创建菜单
    //auto menu = Menu::create(enterBtn, NULL);
    //menu->setPosition(Vec2(500, 500));
    //this->addChild(menu, 1);

    /* 创建背景 */
    auto background = Sprite::create("StartScene/front_bg.png");
    if (background == nullptr)
        problemLoading("'StartScene/front_bg.png'");
    else
    {
        //设置位置
        background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        //添加到子代
        addChild(background, -1);
    }

    return true;
}

/* 关闭界面，退出程序 */
void StartScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}

